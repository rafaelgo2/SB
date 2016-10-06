#ifndef INSTRUCTIONS_H_INCLUDED
#define INSTRUCTIONS_H_INCLUDED

#include <bitset>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>

#include "maps.h"

using namespace std;

typedef struct{
	int pc, numBytes;
	long long int value;
} mem;

void newInstruction(int &pc, int n, char RAM[256]) ;

void printInstruction(int &pc, char c, ofstream &fout) ;

void printMultipleInstructions(int &pc_i, int pc_f, char c, ofstream &fout) ;

void printRAM(int pc, char RAM[256], ofstream &fout, map<string, mem> &memMap,
			  queue<string> &memQueue) ;

#endif // INSTRUCTIONS_H_INCLUDED
