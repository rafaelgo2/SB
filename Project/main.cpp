#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <bitset>

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
	for (int i = 0; i < 255; i++)
		opIdMap["R" + i] = i;
	opIdMap["IO"] = 254;
}


void fillOpTypeMap(int *opTypeMap){
//0: 11B
//1: 3R 8B
	opTypeMap[0] = 0;
	opTypeMap[1] = 1;
	opTypeMap[2] = 1;
	opTypeMap[3] = 2;
	opTypeMap[4] = 2;
	opTypeMap[5] = 2;
	opTypeMap[6] = 2;
    opTypeMap[7] = 1;
	opTypeMap[8] = 1;
	opTypeMap[9] = 1;
	opTypeMap[10] = 2;
	opTypeMap[11] = 2;
	opTypeMap[12] = 2;
	opTypeMap[13] = 1;
	opTypeMap[14] = 1;
	opTypeMap[15] = 1;
	opTypeMap[16] = 3;
	opTypeMap[17] = 1;
	opTypeMap[18] = 1;
	opTypeMap[19] = 1;
	opTypeMap[20] = 0;
	opTypeMap[21] = 1;
	opTypeMap[22] = 1;
	opTypeMap[23] = 1;
	opTypeMap[24] = 3;
	opTypeMap[25] = 3;
	opTypeMap[26] = 1;
}

void begin(ofstream &fout){
	fout << "DEPTH = 256;" << endl
		 << "WIDTH = 8;" << endl
		 << "ADDRESS_RADIX = HEX;" << endl
		 << "DATA_RADIX = BIN" << endl
		 << "CONTENT" << endl
		 << "BEGIN" << endl << endl;
}

void end(ofstream &fout){
	fout << endl << "END;";
}

int main(int argc, char *argv[]){
	map<string, int> labelMap, opCodeMap, opIdMap, memMap;
	int opTypeMap[27];
	fillOpCodeMap(opCodeMap);
	fillOpIdMap(opIdMap);
	fillOpTypeMap(opTypeMap);
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	begin(fout);
	int pc = 0;
	string s;
	stringstream ss;
	while (getline(fin, s)){
		if (s[0] != ';'){
			ss.str(s);
			string op;
			ss >> op;
			fout << hex << pc
				 << " : "
				 << bitset<5>(opCodeMap[op]);
			switch (opTypeMap[opCodeMap[op]]){
				case 0:{
					fout << bitset<11>(0);
				}break;
				case 1:{
					string op1, op2;
					ss >> op1 >> op2;
					fout << bitset<3>(opIdMap[op1]);
					if (memMap[op2] != 0){
						fout << bitset<8>(opIdMap[op2]);
					}
					else{
						int n;
						stringstream ss_(op2);
						ss_ >> n;
						fout << bitset<8>(n);
					}
				}break;
				case 2:{
					string op1, op2;
					ss >> op1 >> op2;
					fout << bitset<3>(opIdMap[op1])
						 << bitset<3>(opIdMap[op2])
						 << bitset<5>(0);
				}break;
				case 3:{
					string op1, op2, op2;
					ss >> op1 >> op2 >>op3;
					fout << bitset<3>(opIdMap[op1])
						 << bitset<3>(opIdMap[op2])
						 << bitset<3>(opIdMap[op3])
						 << bitset<2>(0);
				}break;
			}
			fout << ";" << endl;
			pc++;
		}
	}
	end(fout);
	return 0;
}
