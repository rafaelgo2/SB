#include "instructions.h"

using namespace std;

void newInstruction(int &pc, int n, char RAM[256]){
	RAM[pc] = n;
	pc++;
}

void printInstruction(int pc, char c, ofstream &fout){
	fout << hex << uppercase << setfill('0') << setw(2) << pc << " : "
		 << bitset<8>(c) << " ;" << endl;
}


void printMultipleInstructions(int pc_i, int pc_f, char c, ofstream &fout){
	fout << '[' << hex << uppercase << setfill('0') << setw(2) << pc_i << ".."
		 << hex << uppercase << setfill('0') << setw(2) << pc_f << "] : "
		 << bitset<8>(c) << " ;" << endl;
}

void printRAM(int pc, char RAM[256], ofstream &fout, map<string, mem> &memMap){
	for (int cnt = 0; cnt < 256; cnt++)
		if(RAM[cnt] != RAM[cnt+1])
			printInstruction(cnt, RAM[cnt], fout);
		else{
			int cnt_;
			for(cnt_ = cnt+2; cnt_ < 256 && RAM[cnt_] == RAM[cnt]; cnt_++);
			printMultipleInstructions(cnt, cnt_-1, RAM[cnt], fout);
			cnt = cnt_-1;			
		}
}
