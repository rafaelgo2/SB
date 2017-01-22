#include "snake.h"

void set(Snake *s, Pair p){
	s->field[p.i][p.j] = 1;
	push(&s->q, p);
}

int isSet(Snake *s, Pair p){
	return s->field[p.i][p.j] == 1;
}

int isFood(Snake *s, Pair p){
	return s->field[p.i][p.j] == 2;
}

void startSnake(Snake *s){
	startQueue(&(s->q));
	fillM(N, M, s->field, 0);
	s->fail = 0;
	set(s, newPair(0, 0));
	makeFood(s, rand(), rand());
}

int won(Snake *s){
	return s->q.size == (s->q.capacity - 1);
}

int end(Snake *s){
	return won(s) || s->fail;
}

void print(Snake *s){
	Pair head = front(&(s->q));
	int i, j;
	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			switch (s->field[i][j]){
				case 0:{
					printf("%c ", '-');
				} break;
				case 1:{
					if (equals(head, newPair(i, j)))
						printf("%c ", 'x');
					else
						printf("%c ", '+');
				} break;
				case 2:{
					printf("%c ", '*');
				} break;
			}
		}
		printf("\n");
	}
}

void fixPosition(Pair *position){
	position->i = (position->i + N) % N;
	position->j = (position->j + N) % N;
}

void move(Snake *s, char direction){
	Pair head = front(&(s->q));
	Pair increment;
	switch (direction){
		case 'A':{
			increment = newPair(0, -1);
		} break;
		case 'W':{
			increment = newPair(-1, 0);
		} break;
		case 'S':{
			increment = newPair(1, 0);
		} break;
		case 'D':{
			increment = newPair(0, 1);
		} break;
		default:{
			increment = newPair(0, 0);
		} break;
	}
	Pair newPosition = sumPair(head, increment);
	fixPosition(&newPosition);
	Pair lastPosition = back(&(s->q));
	if (isSet(s, newPosition) && !equals(newPosition, lastPosition)){
		s->fail = 1;
	}
	else{
		if (!isFood(s, newPosition)){
			pop(&(s->q));
			s->field[lastPosition.i][lastPosition.j] = 0;
		}
		else{
			makeFood(s, rand(), rand());
		}
		set(s, newPosition);
	}
}

void makeFood(Snake *s, int i, int j){
	i %= N;
	j %= M;
	while (isSet(s, newPair(i, j))){
		i = (i +((j+1) == M)) % N;
		j = (j+1) % M;
	}
	s->field[i][j] = 2;
}
