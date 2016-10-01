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


void fillOpTypeMap(map<int, int> &opTypeMap){
//0: 11B
//1: 3R 8B


	opTypeMap[00] = 0; //0
	opTypeMap[01] = 1; //1
	opTypeMap[02] = 1; //2
	opTypeMap[03] = 2; //3
	opTypeMap[04] = 2; //4
	opTypeMap[05] = 2; //5
	opTypeMap[06] = 2; //6
	opTypeMap[07] = 4; //7
	opTypeMap[10] = 1; //8
	opTypeMap[11] = 1; //9
	opTypeMap[12] = 2; //10
	opTypeMap[13] = 2; //11
	opTypeMap[14] = 2; //12
	opTypeMap[15] = 5; //13
	opTypeMap[16] = 1; //14
	opTypeMap[17] = 6; //15
	opTypeMap[20] = 3; //16
	opTypeMap[21] = 4; //17
	opTypeMap[22] = 5; //18
	opTypeMap[23] = 5; //19
	opTypeMap[24] = 0; //20
	opTypeMap[25] = 6; //21
	opTypeMap[26] = 6; //22
	opTypeMap[27] = 5; //23
	opTypeMap[30] = 3; //24
	opTypeMap[31] = 3; //25
	opTypeMap[32] = 3; //26
	
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
	map<int, int> opTypeMap;
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

				}break;
			} 
			fout << ";" << endl;
			pc++;
		}
	}
	end(fout);
	return 0;
}
