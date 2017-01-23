#include "snake.h"

void set(Snake *s, Pair p){
	s->field[getI(p)][getJ(p)] = 1;
	push(&s->q, p);
}

int isSet(Snake *s, Pair p){
	return s->field[getI(p)][getJ(p)] == 1;
}

int isFood(Snake *s, Pair p){
	return s->field[getI(p)][getJ(p)] == 2;
}

void startSnake(Snake *s){
    srand(getRandon());
	startQueue(&(s->q));
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            s->field[i][j] = 0;
	s->fail = 0;
	set(s, newPair(0, 0));
	makeFood(s);
}

int won(Snake *s){
	return s->q.size == (s->q.capacity - 1);
}

int end(Snake *s){
	return won(s) || s->fail;
}

void print(Snake *s, char field[N][M+1]){
	Pair head = front(&(s->q));
	int i, j;
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			switch (s->field[i][j]){
				case 0:{
					field[i][j] = ' ';
				} break;
				case 1:{
					if (head == newPair(i, j))
                        field[i][j] = '*';
					else
                        field[i][j] = '+';
				} break;
				case 2:{
					field[i][j] = 'x';
				} break;
			}
		}
        field[i][M] = 0;
	}
}

void move(Snake *s, char direction){
	Pair head = front(&(s->q));
    Pair newPosition;
	switch (direction){
		case 0:{
            newPosition = increment(newPosition, 0, -1);
		} break;
		case 1:{
            newPosition = increment(newPosition, 1, 0);
		} break;
		case 2:{
            newPosition = increment(newPosition, 0, 1);
		} break;
        default:{
            newPosition = head;        
        } break;
	}
	Pair lastPosition = back(&(s->q));
	if (isSet(s, newPosition) && (newPosition != lastPosition)){
		s->fail = 1;
	}
	else{
		if (!isFood(s, newPosition)){
			pop(&(s->q));
			s->field[getI(lastPosition)][getJ(lastPosition)] = 0;
            set(s, newPosition);
		}
		else{
            set(s, newPosition);
            if (!won(s))
                makeFood(s);
		}
	}
}

void makeFood(Snake *s){
    int i, j;
    do{
        i = rand() % N;
        j = rand() % M;  
    }while(isSet(s, newPair(i, j)));
	s->field[i][j] = 2;
}

int points(Snake *s){
    return s->q.size;
}