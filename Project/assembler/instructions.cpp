#include "instructions.h"

using namespace std;

void newInstruction(int &pc, int n, char RAM[256]){
	RAM[pc] = n;
	pc++;
}

void printInstruction(int &pc, char c, ofstream &fout){
	fout << hex << uppercase << setfill('0') << setw(2) << pc << " : "
		 << bitset<8>(c) << " ;" << endl;
	pc++;
}

void printMultipleInstructions(int &pc_i, int pc_f, char c, ofstream &fout){
	fout << '[' << hex << uppercase << setfill('0') << setw(2) << pc_i << ".."
		 << hex << uppercase << setfill('0') << setw(2) << pc_f << "] : "
		 << bitset<8>(c) << " ;" << endl;
	pc_i = pc_f + 1;
}

void printRAM(int pc, char RAM[256], ofstream &fout, map<string, mem> &memMap,
			  queue<string> &memQueue){
	for (mem mem_ = memMap[memQueue.front()]; !memQueue.empty();
			mem_ = memMap[memQueue.front()], memQueue.pop())
        if (mem_.numBytes == 8)
            for (int i = 0; i < 8; i++)
        		newInstruction(pc, 0, RAM);
        else
            while(mem_.numBytes--)
		        newInstruction(pc, mem_.value >> (8 * mem_.numBytes), RAM);

	int cnt = 0, cnt_;
	while(cnt < pc)
		if(RAM[cnt] != RAM[cnt+1])
			printInstruction(cnt, RAM[cnt], fout);
		else{
			for(cnt_ = cnt; RAM[cnt_] == RAM[cnt_ + 1] && cnt_ < pc; cnt_++) ;
			if(cnt_ != pc || RAM[cnt_ - 1] != RAM[cnt_])
				printMultipleInstructions(cnt, cnt_, RAM[cnt], fout);
			else break;
		}

	printMultipleInstructions(cnt, 255, 0, fout);
}
