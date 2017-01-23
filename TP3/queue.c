#include "queue.h"

// Construtor do Struct Queue
void startQueue(Queue *q){
    // Seta os parametros default da fila
	q->capacity = SIZEQUEUE;
	q->head = q->tail = q->size = 0;
}

void push(Queue *q, Pair x){
    // Adiciona um novo par à fila
	int pos = q->head % q->capacity;
	q->head = (q->head + 1) % q->capacity;
	q->v[pos] = x;
	q->size++;
}

Pair front(Queue *q){
    // Retorna o Pair da frente
	int pos = ((q->head-1) + q->capacity) % q->capacity;
	return q->v[pos];
}

Pair back(Queue *q){
    // Retorna o Pair de trás
	int pos = q->tail % q->capacity;
	return q->v[pos];
}

void pop(Queue *q){
    // Remove da Fila
	q->tail = (q->tail + 1) % q->capacity;
	q->size--;
}
