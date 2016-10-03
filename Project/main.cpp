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
	int numBytes;
	long long int value;
	int pc;
} mem;

void fillOpCodeMap(map<string, int> &opCodeMap){
	opCodeMap["exit"] = 0; // REDUNDANTE
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
	stringstream ss;
	string s;
	for (int i = 0; i < 8; i++){
		ss << "R" << i;
		ss >> s;
		regMap[s] = i;
		ss.clear();
	}
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

void newInstruction(int &pc, int n, char ram[256]){
	ram[pc] = n;
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

void lastInstructions(int pc, char ram[256], ofstream &fout, map<string, mem> &memMap, queue<string> &memQueue){
	while (!memQueue.empty()){
		string mems = memQueue.front();
		memQueue.pop();
		mem mem_ = memMap[mems];
        if (mem_.numBytes == 8)
            for (int i = 0; i < 8; i++)
        		newInstruction(pc, 0, ram);
        else
            while(mem_.numBytes--)
		        newInstruction(pc, mem_.value >> (8*mem_.numBytes), ram);
	}

	cout << pc;

	int cnt, cnt_;
	for(cnt = 0; cnt < pc;){
		if(ram[cnt] != ram[cnt+1])
			printInstruction(cnt, ram[cnt], fout);
		else{
			for(cnt_ = cnt; ram[cnt_] == ram[cnt_ + 1] && cnt_ < pc; cnt_++) ;
			if(cnt_ == pc && ram[cnt_ - 1] == ram[cnt_]) break;
			printMultipleInstructions(cnt, cnt_, ram[cnt], fout);
		}	
	}

	printMultipleInstructions(cnt, 255, 0, fout);
}


int main(int argc, char *argv[]){
	int opTypeMap[27] = {0, 1, 1, 2, 2, 2, 2, 4, 1, 1, 2, 2, 2, 1, 1, 4, 3, 4, 1, 1, 5, 4, 4, 1, 3, 3, 1}, pc=0;
	map<string, int> labelMap, opCodeMap, regMap;
	char ram[256];
	fill(&(ram[0]), &(ram[255])+1, 0);
	map<string, mem> memMap;
	mem io = {2, 0, 254};
	memMap["IO"] = io;
	queue<string> memQueue;
	fillOpCodeMap(opCodeMap);
	fillRegMap(regMap);
	ifstream fin(argv[1]);
	string s, saux;
	stringstream ss, ssaux;
	while (getline(fin, saux)){
		ssaux.str(saux);
		getline(ssaux, s, ';');	
		ss.str(s);
		string tmp;
		ss >> tmp;
		if (tmp.size() > 0)
			if (tmp[tmp.size() - 1] == ':'){
				tmp.erase(tmp.size() - 1, 1);
				string op;
				ss >> op;
				if (op == ".data"){
					int numBytes;
					ss >> numBytes;
                    long long int value;
                    ss >> value;
                    mem mem_ = {numBytes, value, pc};
					memMap[tmp] = mem_;
					memQueue.push(tmp);
					pc += numBytes;
				}
				else{
					labelMap[tmp] = pc + 1;
					pc += 2;
				}
			}
			else pc += 2;
		ssaux.clear();
		saux.clear();
		s.clear();
		ss.clear();
	}
	fin.clear();
	fin.seekg(0, fin.beg);
	ofstream fout(argv[2]);
	begin(fout);
	pc = 0;
	while (getline(fin, saux)){
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
					newInstruction(pc, 0, ram);
					newInstruction(pc, 0, ram);
					lastInstructions(pc, ram, fout, memMap, memQueue);
					fin.seekg(0, fin.end);
				} break;
				case 1:{
					string op1, op2;
					ss >> op1 >> op2;
					newInstruction(pc, (opCodeMap[op] << 3) + regMap[op1], ram);
					if (memMap[op2].numBytes != 0)
						newInstruction(pc, memMap[op2].pc, ram);
					else if (labelMap[op2] != 0){
						cout << "|" << op2 << "|" << bitset<8>(labelMap[op2]) <<  endl;
						newInstruction(pc, labelMap[op2]-1, ram);
					}
					else{
						int n;
						stringstream ss_(op2);
						ss_ >> n;
						newInstruction(pc, n, ram);
					}
				} break;
				case 2:{
					string op1, op2;
					ss >> op1 >> op2;
					newInstruction(pc, (opCodeMap[op] << 3) + regMap[op1], ram);
					newInstruction(pc, (regMap[op2] << 5), ram);
				} break;
				case 3:{
					string op1, op2, op3;
					ss >> op1 >> op2 >> op3;
					newInstruction(pc, (opCodeMap[op] << 3) + regMap[op1], ram);
					newInstruction(pc, (regMap[op2] << 5) + (regMap[op3] << 2), ram);
				} break;
				case 4:{
					string op1;
					ss >> op1;
					newInstruction(pc, (opCodeMap[op] << 3), ram);
					if (memMap[op1].numBytes != 0)
						newInstruction(pc, memMap[op1].pc, ram);
					else if (labelMap[op1] != 0)
						newInstruction(pc, labelMap[op1]-1, ram);
					else{
						int n;
						stringstream ss_(op1);
						ss_ >> n;
						newInstruction(pc, n, ram);
					}
				} break;
				case 5:{
					newInstruction(pc, (opCodeMap[op] << 3), ram);
					newInstruction(pc, 0, ram);
				} break;
			}
		}
		ssaux.clear();
		saux.clear();
		s.clear();
		ss.clear();
	}
	end(fout);
	fin.close();
	fout.close();
	return 0;
}
