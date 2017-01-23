#include "pair.h"

Pair newPair(char i, char j){
	return i*M + j;
}

char getI(Pair p){
	return p/M;
}

char getJ(Pair p){
	return p%M;
}

Pair increment(Pair p, char i, char j){
	char sumI = (getI(p) + i + N) % N; //Ajusta os limites da tela
	char sumJ = (getJ(p) + j + M) % M; //E movimenta um ponto
	return newPair(sumI, sumJ);
}
