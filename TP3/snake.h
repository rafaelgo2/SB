#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "queue.h"

typedef struct{
	int field[N][M];
	Queue q;
	int fail;
}Snake;

void set(Snake *s, Pair p) ;

int isSet(Snake *s, Pair p) ;

int isFood(Snake *s, Pair p) ;

void startSnake(Snake *s) ;

int won(Snake *s) ;

int end(Snake *s) ;

void print(Snake *s) ;

void fixPosition(Pair *position) ;

void move(Snake *s, char direction) ;

void makeFood(Snake *s, int i, int j) ;

#endif // SNAKE_H_INCLUDED
