#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define M 5
#define SIZEQUEUE 26
//SIZEQUEUE = N*M+1

void fillV(int n, int v[n], int x){
	int i;
	for (i = 0; i < n; i++)
		v[i] = 0;
}

void fillM(int n, int m, int v[n][m], int x){
	int i;
	for (i = 0; i < n; i++)
		fillV(m, v[i], x);
}

typedef struct{
	int i;
	int j;
}Pair;

Pair newPair(int i, int j){
	Pair p = {i, j};
	return p;
}

Pair sumPair(Pair p1, Pair p2){
	Pair p = {p1.i + p2.i, p1.j + p2.j};
	return p;
}

int equals(Pair p1, Pair p2){
    return (p1.i == p2.i) && (p1.j == p2.j);
}

typedef struct{
	int capacity;
	int size;
	int head;
	int tail;
	Pair v[SIZEQUEUE];
} Queue;

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
	int pos = q->tail % q->capacity;
	q->tail = (q->tail + 1) % q->capacity;
	q->size--;
}

int empty(Queue *q){
	return q->size == 0;
}

typedef struct{
	int field[N][M];
	Queue q;
	int fail;
}Snake;

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
	if (isSet(s, newPosition) && !equals(newPosition, lastPosition))
		s->fail = 1;
	else{
		if (!isFood(s, newPosition)){
            pop(&(s->q));
            s->field[lastPosition.i][lastPosition.j] = 0;
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

int main(){
    while (1){
        int counter = 0;
        srand(time(NULL));
        char direction;
        Snake s;
        startSnake(&s);
        while (!end(&s)){

            print(&s);
            scanf("%c%*c", &direction);
            move(&s, direction);
            if (counter == 5){
                makeFood(&s, rand(), rand());
                counter = 0;
            }
            else
                counter++;
        }
        if (won(&s)){
            printf("VENCEU!");
        }
        else{
            printf("PERDEU!");
        }
    }
	return 0;
}
