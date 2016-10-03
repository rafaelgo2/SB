#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

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
	opCodeMap[".data"] = 27;
}

void fillOpIdMap(map<string, int> &opIdMap){
	stringstream ss;
	string s;
	for (int i = 0; i < 8; i++){
		ss << "R" << i;
		ss >> s;
		opIdMap[s] = i;
		ss.clear();
	}
	opIdMap["IO"] = 254;
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
	fout << endl << "END;";
}

void newInstruction(int &pc, long long int n, ofstream &fout){
	fout << hex << uppercase << setfill('0') << setw(2) << pc << " : "
		 << bitset<8>(n) << ";" << endl;
	pc++;
}

void lastInstructions(int pc, int sp, ofstream &fout){
	fout << "[" << hex << uppercase << setfill('0') << setw(2) << pc
		 << ".." << hex << uppercase << setfill('0') << setw(2) << sp
		 << "]: " << bitset<8>(0) << ";" << endl;
}


int main(int argc, char *argv[]){
	int opTypeMap[28] = {5, 1, 1, 2, 2, 2, 2, 4, 1, 1, 2, 2, 2, 1, 1, 4, 3, 4, 1, 1, 5, 4, 4, 1, 3, 3, 1, 6}, pc=0, sp = 254;
	map<string, int> labelMap, opCodeMap, opIdMap, memMap;
	fillOpCodeMap(opCodeMap);
	fillOpIdMap(opIdMap);
	ifstream fin(argv[1]);
    string aux, s;
	stringstream ssaux, ss;
	while (getline(fin, aux)){
		ssaux.str(aux);
		getline(ssaux, aux, ';');
		ssaux.clear();
		ssaux.str(aux);
		getline(ssaux, s, ':');
		ss.str(s);
		string tmp;
		ss >> tmp;
        if (tmp.size() > 0){
			string op;
			ssaux >> op;
			if (op == ".data"){
				int numBytes;
				if (numBytes > 8){
					numBytes = 8;
				}
				else if (numBytes%2){
					numBytes++;
				}
				ssaux >> numBytes;
				labelMap[tmp] = pc+1;
				pc += numBytes;
			}
            else {
				if (tmp[0] == '_'){
			        labelMap[tmp] = pc+1;
				}
				pc += 2;
			}
        }
		s.clear();
		aux.clear();
		ss.clear();
		ssaux.clear();
	}
    fin.clear();
    fin.seekg(0, fin.beg);

	labelMap["IO"] = 254;

	ofstream fout(argv[2]);
	begin(fout);
	pc = 0;
	while (getline(fin, aux)){
		ssaux.str(aux);
		getline(ssaux, s, ';');
		ss.str(s);
		string op;
		ss >> op;
		if (op.size() > 0){
			if (op[0] == '_' || opCodeMap[op] == 0){
                string label = op;
                ss >> op;
			}
			switch (opTypeMap[opCodeMap[op]]){
				case 1:{
					string op1, op2;
					ss >> op1 >> op2;
					newInstruction(pc, (opCodeMap[op] << 3) + opIdMap[op1], fout);
					if (memMap[op2] != 0){
						newInstruction(pc, memMap[op2]-1, fout);
					}
                    else if (labelMap[op2] != 0){
                        newInstruction(pc, labelMap[op2]-1, fout);
                    }
					else{
						int n;
						stringstream ss_(op2);
						ss_ >> n;
						newInstruction(pc, n, fout);
					}
				}break;
				case 2:{
					string op1, op2;
					ss >> op1 >> op2;
					newInstruction(pc, (opCodeMap[op] << 3) + opIdMap[op1], fout);
					newInstruction(pc, (opIdMap[op2] << 5), fout);
				}break;
				case 3:{
					string op1, op2, op3;
					ss >> op1 >> op2 >> op3;
					newInstruction(pc, (opCodeMap[op] << 3) + opIdMap[op1], fout);
					newInstruction(pc, (opIdMap[op2] << 5) + (opIdMap[op3] << 2), fout);
				}break;
				case 4:{
					string op1;
					ss >> op1;
					newInstruction(pc, (opCodeMap[op] << 3), fout);
					if (memMap[op1] != 0){
						newInstruction(pc, memMap[op1]-1, fout);
					}
                    else if (labelMap[op1] != 0){
                        newInstruction(pc, labelMap[op1]-1, fout);
                    }
					else{
						int n;
						stringstream ss_(op1);
						ss_ >> n;
						newInstruction(pc, n, fout);
					}
				}break;
				case 5:{
					newInstruction(pc, (opCodeMap[op] << 3), fout);
					newInstruction(pc, 0, fout);
				}break;
				case 6:{
					int numBytes;
					long long int initialValue;
					ss >> numBytes >> initialValue;
					if (numBytes > 8){ // AQUI ASSUMO QUE TODAS AS ALOCAÇÕES RESERVAM 8 OU MENOS BYTES
						numBytes = 8;
					}
					else if (numBytes%2){ // AQUI ASSUMO QUE TODAS AS ALOCAÇÕES RESERVAM MÚLTIPLOS DE 2 BYTES
						numBytes++;
					}
					for (numBytes--; numBytes >= 0; numBytes--){
						newInstruction(pc, (int) initialValue >> 8*numBytes, fout);
					}
				}break;
			}
		}
		ss.clear();
		ssaux.clear();
	}
	lastInstructions(pc, sp, fout);
	while (sp < 256){
		newInstruction(sp, 0, fout); // (???) já não sei mais nada do que tô fazendo
	}
	end(fout);
	fin.close();
	fout.close();
	return 0;
}
