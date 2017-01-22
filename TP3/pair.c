#include "pair.h"

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
