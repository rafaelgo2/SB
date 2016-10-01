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
	opTypeMap[000] = 0;
	opTypeMap[001] = 1;
	opTypeMap[002] = 1;
	opTypeMap[003] = 2;
	opTypeMap[004] = 2;
	opTypeMap[005] = 2;
	opTypeMap[006] = 2;
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

/*

			if (s[0] == '_'){
				string label;
				ss >> label;
				labelMap[label] = pc;
			}
*/

int main(int argc, char *argv[]){
	map<string, int> labelMap, opCodeMap, opIdMap;
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

				}break;
				case 2:{
					string op1, op2;
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
