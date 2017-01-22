#ifndef PAIR_H_INCLUDED
#define PAIR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define M 5
#define SIZEQUEUE 26

void fillV(int n, int v[n], int x) ;

void fillM(int n, int m, int v[n][m], int x) ;

typedef struct{
	int i;
	int j;
}Pair;

Pair newPair(int i, int j) ;

Pair sumPair(Pair p1, Pair p2) ;

int equals(Pair p1, Pair p2) ;

#endif // PAIR_H_INCLUDED
