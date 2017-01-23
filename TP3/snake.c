#include "snake.h"

//Inicia a cobra em uma posição Pair do mapa
void set(Snake *s, Pair p){
	s->field[getI(p)][getJ(p)] = 1;
	push(&s->q, p);
}

//Retorna 1 se Snake esta ocupando aquela posição do campo
int isSet(Snake *s, Pair p){
	return s->field[getI(p)][getJ(p)] == 1;
}

// Retorna 1 se uma comida está ocupando aquela posição do campo
int isFood(Snake *s, Pair p){
	return s->field[getI(p)][getJ(p)] == 2;
}

//Construtor da Snake
void startSnake(Snake *s){
	srand(getRandon()); //getRandon retorna o seed de acordo com o horário da placa
	startQueue(&(s->q));
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			s->field[i][j] = 0;
	s->fail = 0; //Sinaliza o estado do jogo. 1 se a cobra se intersectar
	set(s, newPair(0, 0));
	makeFood(s);
}

//Se a cobra atingir a capacidade, o jogador é vitorioso
int won(Snake *s){
	return s->q.size == (s->q.capacity - 1);
}

//Termina se o jogador morreu ou ganhou
int end(Snake *s){
	return won(s) || s->fail;
}

//Função que seta os desenhos mostrados no campo
void print(Snake *s, char field[N][M+1]){
	Pair head = front(&(s->q));
	int i, j;
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
            //Para cada posição no campo...
			switch (s->field[i][j]){
				case 0:{
                    //...caso 0: Display vazio.
					field[i][j] = ' ';
				} break;
				case 1:{
					//...caso 1: Corpo da Cobra.
					if (head == newPair(i, j))
						field[i][j] = '*'; //Destaca a cabeça da cobra
					else
						field[i][j] = '+'; //O corpo da cobra
				} break;
				case 2:{
					//...caso 2: comida.
					field[i][j] = 'x';
				} break;
			}
		}
        //default 0.
		field[i][M] = 0;
	}
}

//Movimenta a cobra dependendo da sua direção
void move(Snake *s, char direction){
	Pair head = front(&(s->q)); // cabeça da cobra
	Pair newPosition; //Nova posição
	switch (direction){
		case 0:{
			newPosition = increment(newPosition, 0, -1); //movimenta para esquerda
		} break;
		case 1:{
			newPosition = increment(newPosition, 1, 0); //movimenta para direita
		} break;
		case 2:{
			newPosition = increment(newPosition, 0, 1); //movimenta baixo/cima
		} break;
		default:{
			newPosition = head; //não movimenta
		} break;
	}
	Pair lastPosition = back(&(s->q));
	if (isSet(s, newPosition) && (newPosition != lastPosition))
		s->fail = 1; // morre =/
	else{
		if (!isFood(s, newPosition)){
			//se não for uma comida, ela apensa movimenta
            pop(&(s->q));
			s->field[getI(lastPosition)][getJ(lastPosition)] = 0;
			set(s, newPosition);
		}
		else{
            //se for uma comida, ela movimenta, sem dar pop no rabo (aumenta)
			set(s, newPosition);
			if (!won(s))
                //se o jogador ainda não ganhou, gera mais comida
				makeFood(s);
		}
	}
}

//Cria a comida de maneira randomica no campo
void makeFood(Snake *s){
	int i, j;
	do{
		i = rand() % N; //Gerados aleatoriamente
		j = rand() % M;  //com a seed baseada no horário da placa
	}while(isSet(s, newPair(i, j)));
	s->field[i][j] = 2; //Seta a posição do campo com a comida
}

//Retorna o tamanho da Queue (pontos)
int points(Snake *s){
	return s->q.size;
}
