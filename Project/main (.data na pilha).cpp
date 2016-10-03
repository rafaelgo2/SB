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

void newInstruction(int &pc, int n, ofstream &fout){
	fout << hex << uppercase << setfill('0') << setw(2) << pc << " : "
		 << bitset<8>(n) << ";" << endl;
	pc++;
}

void lastInstructions(int pc, int memEnd, ofstream &fout){
	fout << "[" << hex << uppercase << setfill('0') << setw(2) << pc
		 << ".." << hex << uppercase << setfill('0') << setw(2) << memEnd
		 << "]: " << bitset<8>(0) << ";" << endl;
}


int main(int argc, char *argv[]){
	int opTypeMap[27] = {0, 1, 1, 2, 2, 2, 2, 4, 1, 1, 2, 2, 2, 1, 1, 4, 3, 4, 1, 1, 0, 4, 4, 1, 3, 3, 1}, pc=0, memEnd = 254;
	map<string, int> labelMap, opCodeMap, opIdMap;
	map<int, int> memMap;
	fillOpCodeMap(opCodeMap);
	fillOpIdMap(opIdMap);
	ifstream fin(argv[1]);
    string aux, s;
	stringstream ssaux, ss;
	while (getline(fin, aux)){
		ssaux.str(aux);
		getline(ssaux, aux, ';');
		ssaux.str(aux);
		getline(ssaux, s, ':');
		ss.str(s);
		string tmp;
		ss >> tmp;
        if (tmp.size() > 0){
			string op;
			ssaux >> op;
			if(op == ".data"){
				int numBytes, initialValue;
				ssaux >> numBytes >> initialValue;
				memEnd-=numBytes;
				memMap[memEnd] = initialValue;
				labelMap[tmp] = memEnd;
			}
            else if (tmp[0] == '_'){
                labelMap[tmp] = pc+1;
				cout << endl << uppercase << tmp << ' ' << pc << endl;
            }
            pc += 2;
        }
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
			if (op[0] == '_'){
                string label = op;
                ss >> op;
			}
			switch (opTypeMap[opCodeMap[op]]){
				case 1:{
					string op1, op2;
					ss >> op1 >> op2;
					newInstruction(pc, (opCodeMap[op] << 3) + opIdMap[op1], fout);
                    cout << s << endl;
                    cout << op2 << endl;
					if (memMap[0] != 0){ // RESOLVER ISSO
						newInstruction(pc, memMap[0]-1, fout); // AQUI TAMBÉM
					}
                    else if (labelMap[op2] != 0){
                        cout << pc << " " << labelMap[op2]-1 << endl;
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
					if (memMap[0] != 0){ // RESOLVER DE NOVO
						newInstruction(pc, memMap[0]-1, fout); // MAIS UMA VEZ PQ RAFAEL, WTF?
					}
                    else if (labelMap[op1] != 0){
                        cout << pc << " " << labelMap[op1]-1 << endl;
                        newInstruction(pc, labelMap[op1]-1, fout);
                    }
					else{
						int n;
						stringstream ss_(op1);
						ss_ >> n;
						newInstruction(pc, n, fout);
					}
				}break;
			}
		}
		ss.clear();
		ssaux.clear();
	}
	lastInstructions(pc, memEnd-1, fout);
	while(memEnd < 256){ // AQUI EU ASSUMO QUE TODAS AS ALOCAÇÕES DE .data RESERVAM 1 OU 2 POSIÇÕES DE MEMÓRIA
		if(memMap[memEnd+1] == 0){
			newInstruction(memEnd, memMap[memEnd] >> 8, fout);
			newInstruction(memEnd, memMap[memEnd-1], fout);
		}
		else{
			newInstruction(memEnd, memMap[memEnd], fout);
		}
	}
	end(fout);
	fin.close();
	fout.close();
	return 0;
}
