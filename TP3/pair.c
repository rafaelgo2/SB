#include "pair.h"

// construtor objeto Pair
Pair newPair(char i, char j){
	return i*M + j;
}

// retorna posição I
char getI(Pair p){
	return p/M;
}

// retorna posição J
char getJ(Pair p){
	return p%M;
}

//Modifica os valores do Pair (posição)
Pair increment(Pair p, char i, char j){
	char sumI = (getI(p) + i + N) % N; //Ajusta os limites da tela
	char sumJ = (getJ(p) + j + M) % M; //E movimenta um ponto
	return newPair(sumI, sumJ);
}
