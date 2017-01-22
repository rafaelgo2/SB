#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "pair.h"

typedef struct{
	int capacity;
	int size;
	int head;
	int tail;
	Pair v[SIZEQUEUE];
} Queue;

void startQueue(Queue *q) ;

void push(Queue *q, Pair x) ;

Pair front(Queue *q) ;

Pair back(Queue *q) ;

void pop(Queue *q) ;

int empty(Queue *q) ;

#endif // QUEUE_H_INCLUDED
