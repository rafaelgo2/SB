#include "queue.h"

void startQueue(Queue *q){
	q->capacity = SIZEQUEUE;
	q->head = q->tail = q->size = 0;
}

void push(Queue *q, Pair x){
	int pos = q->head % q->capacity;
	q->head = (q->head + 1) % q->capacity;
	q->v[pos] = x;
	q->size++;
}

Pair front(Queue *q){
	int pos = ((q->head-1) + q->capacity) % q->capacity;
	return q->v[pos];
}

Pair back(Queue *q){
	int pos = q->tail % q->capacity;
	return q->v[pos];
}

void pop(Queue *q){
	q->tail = (q->tail + 1) % q->capacity;
	q->size--;
}