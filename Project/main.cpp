#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <string>
#include <queue>

using namespace std;

typedef struct{
	int pc, numBytes;
	long long int value;
} mem;

void fillOpCodeMap(map<string, int> &opCodeMap){
	opCodeMap["exit"] = 0;
	opCodeMap["loadi"] = 1;
	opCodeMap["storei"] = 2;
	opCodeMap["add"] = 3;
	opCodeMap["subtract"] = 4;
	opCodeMap["multiply"] = 5;
	opCodeMap["divide"] = 6;
	opCodeMap["jump"] = 7;
	opCodeMap["jmpz"] = 8;
	opCodeMap["jmpn"] = 9;
	opCodeMap["move"] = 10;
	opCodeMap["load"] = 11;
	opCodeMap["store"] = 12;
	opCodeMap["loadc"] = 13;
	opCodeMap["clear"] = 14;
	opCodeMap["moveSp"] = 15;
	opCodeMap["slt"] = 16;
	opCodeMap["call"] = 17;
	opCodeMap["loadSp"] = 18;
	opCodeMap["storeSp"] = 19;
	opCodeMap["ret"] = 20;
	opCodeMap["loadRa"] = 21;
	opCodeMap["storeRa"] = 22;
	opCodeMap["addi"] = 23;
	opCodeMap["sgt"] = 24;
	opCodeMap["seq"] = 25;
	opCodeMap["jmpp"] = 26;
}

void fillRegMap(map<string, int> &regMap){
	regMap["R0"] = 0;
	regMap["R1"] = 1;
	regMap["R2"] = 2;
	regMap["R3"] = 3;
	regMap["R4"] = 4;
	regMap["R5"] = 5;
	regMap["R6"] = 6;
	regMap["R7"] = 7;
}

void begin(ofstream &fout){
	fout << "DEPTH = 256;" << endl
		 << "WIDTH = 8;" << endl
		 << "ADDRESS_RADIX = HEX;" << endl
		 << "DATA_RADIX = BIN;" << endl
		 << "CONTENT" << endl
		 << "BEGIN" << endl << endl;
}

void end(ofstream &fout){
	fout << "END;";
}

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
	while (!memQueue.empty()){
		mem mem_ = memMap[memQueue.front()];
		memQueue.pop();
        if (mem_.numBytes == 8)
            for (int i = 0; i < 8; i++)
        		newInstruction(pc, 0, RAM);
        else
            while(mem_.numBytes--)
		        newInstruction(pc, mem_.value >> (8 * mem_.numBytes), RAM);
	}

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

int main(int argc, char *argv[]){
	char RAM[256];
	int pc=0, opTypeMap[27] = {0, 1, 1, 2, 2, 2, 2, 4, 1, 1, 2, 2, 2, 1, 1, 4,
							   3, 4, 1, 1, 0, 4, 4, 1, 3, 3, 1};
	map<string, int> labelMap, opCodeMap, regMap;
	map<string, mem> memMap;
	mem IO = {254, 2, 0};
	queue<string> memQueue;
	string s, saux;
	stringstream ss, ssaux;

	fill(&(RAM[0]), &(RAM[255])+1, 0);
	fillOpCodeMap(opCodeMap);
	fillRegMap(regMap);
	memMap["IO"] = IO;

	ifstream fin(argv[1]);
	for (; getline(fin, saux); ss.clear(), ssaux.clear()){
		ssaux.str(saux);
		getline(ssaux, s, ';');
		ss.str(s);
		string label;
		ss >> label;
		if (label.size() > 0)
			if (label[label.size() - 1] == ':'){
				label.erase(label.size() - 1, 1);
				string op;
				ss >> op;
				if (op == ".data"){
					int numBytes;
                    long long int value;
					ss >> numBytes >> value;
                    mem mem_ = {pc, numBytes, value};
					memMap[label] = mem_;
					memQueue.push(label);
					pc += numBytes;
				}
				else{
					labelMap[label] = pc + 1;
					pc += 2;
				}
			}
			else pc += 2;
	}
	fin.clear();
	fin.seekg(0, fin.beg);

	ofstream fout(argv[2]);
	for (begin(fout), pc = 0; getline(fin, saux); ss.clear(), ssaux.clear()){
		ssaux.str(saux);
		getline(ssaux, s, ';');	
		ss.str(s);
		string op;
		ss >> op;
		if (op.size() > 0){
			if (op[op.size() - 1] == ':')
				ss >> op;
			switch (opTypeMap[opCodeMap[op]]){
				case 0:{
					newInstruction(pc, (opCodeMap[op] << 3), RAM);
					newInstruction(pc, 0, RAM);
					if(opCodeMap[op] == 0){
						printRAM(pc, RAM, fout, memMap, memQueue);
						fin.seekg(0, fin.end);
					}
				} break;
				case 1:{
					string op1, op2;
					ss >> op1 >> op2;
					newInstruction(pc, (opCodeMap[op] << 3) + regMap[op1], RAM);
					if (memMap[op2].numBytes != 0)
						newInstruction(pc, memMap[op2].pc, RAM);
					else if (labelMap[op2] != 0)
						newInstruction(pc, labelMap[op2]-1, RAM);
					else{
						stringstream ss_(op2);
						int n;
						ss_ >> n;
						newInstruction(pc, n, RAM);
					}
				} break;
				case 2:{
					string op1, op2;
					ss >> op1 >> op2;
					newInstruction(pc, (opCodeMap[op] << 3) + regMap[op1], RAM);
					newInstruction(pc, (regMap[op2] << 5), RAM);
				} break;
				case 3:{
					string op1, op2, op3;
					ss >> op1 >> op2 >> op3;
					newInstruction(pc, (opCodeMap[op] << 3) + regMap[op1], RAM);
					newInstruction(pc, (regMap[op2] << 5) + (regMap[op3] << 2), RAM);
				} break;
				case 4:{
					string op1;
					ss >> op1;
					newInstruction(pc, (opCodeMap[op] << 3), RAM);
					if (memMap[op1].numBytes != 0)
						newInstruction(pc, memMap[op1].pc, RAM);
					else if (labelMap[op1] != 0)
						newInstruction(pc, labelMap[op1]-1, RAM);
					else{
						stringstream ss_(op1);
						int n;
						ss_ >> n;
						newInstruction(pc, n, RAM);
					}
				} break;
			}
		}
	}
	end(fout);

	fin.close();
	fout.close();
	return 0;
}
