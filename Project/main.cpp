#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <bitset>
#include <cstring>

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
    stringstream riStream;
    string riString;
	for (int i = 0; i < 8; i++){
        riStream << 'R' << i;
        riStream >> riString;
		opIdMap[riString] = i;
        riStream.clear();
	}
	opIdMap["negOne"]=44;
	opIdMap["sign"]=46;
	opIdMap["one"]=48;
	opIdMap["IO"] = 254;
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
	int opTypeMap[27] = {0, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 3, 1, 1, 1, 0, 1, 1, 1, 3, 3, 1};
	fillOpCodeMap(opCodeMap);
	fillOpIdMap(opIdMap);
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	begin(fout);
	int pc = 0;
	string s;
	stringstream ss;
	while (getline(fin, s)){
		if (s[0] != ';'){
		    while(s[0] == ' ' || s[0] == '\t') s.erase(0, 1);
		    if(s[0] == '\0') continue;
			ss.str(s);
			string op;
			ss >> op;
			fout << hex << uppercase << pc << " : "
				 << bitset<5>(opCodeMap[op]);
            pc++;
			switch (opTypeMap[opCodeMap[op]]){
				case 0:{
					fout << bitset<3>(0)
                         << ";" << endl << hex << uppercase << pc << " : "
                         << bitset<8>(0);
				}break;
				case 1:{
					string op1, op2;
					ss >> op1 >> op2;
					fout << bitset<3>(opIdMap[op1])
                         << ";" << endl << hex << uppercase << pc << " : ";
					if (memMap[op2] != 0){
						fout << bitset<8>(opIdMap[op2]);
					}
					else{
						int n;
						if(opIdMap[op2]!=NULL) n=opIdMap[op2];
						else{
                            stringstream ss_(op2);
                            ss_ >> n;
                        }
						fout << bitset<8>(n);
					}
				}break;
				case 2:{
					string op1, op2;
					ss >> op1 >> op2;
					fout << bitset<3>(opIdMap[op1])
                         << ";" << endl << hex << uppercase << pc << " : "
						 << bitset<3>(opIdMap[op2])
						 << bitset<5>(0);
				}break;
				case 3:{
					string op1, op2, op3;
					ss >> op1 >> op2 >> op3;
					fout << bitset<3>(opIdMap[op1])
                         << ";" << endl << hex << uppercase << pc << " : "
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
