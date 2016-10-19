#include "Module.hpp"
#include <fstream>
#include <sstream>
#include <bitset>
#include <iostream>

void writeData(ofstream &fout, Data &data){
	fout << "Data" << endl
		 << data.name << " "
		 << data.numBytes << " "
		 << data.value << " "
		 << endl;
}

void writeDependency(ofstream &fout, Dependency &dependency){
	fout << "Dependency" << endl
		 << dependency.s << " "
		 << dependency.pc
		 << endl;
}

void writeLabel(ofstream &fout, Label &label){
	fout << "Label" << endl
		 << label.name << " "
		 << label.pc
		 << endl;
}

void writeModuleHeader(ofstream &fout, ModuleHeader &moduleHeader){
	fout << "Module" << endl
		 << moduleHeader.memSize << " "
		 << moduleHeader.labelSize << " "
		 << moduleHeader.dataSize << " "
		 << moduleHeader.dependencySize
		 << endl;
}

void writeMem(ofstream &fout, vector<char> &mem){
	fout << "Mem" << endl;
	for (int i = 0; i < mem.size(); i++){
		fout << bitset<8>(mem[i]) << endl;
	}
}

bool isANumber(string s){
	for (int i = 0; i < s.size(); i++){
		if ((s[i] < '0') || (s[i] > '9'))
			return false;
	}
	return true;
}


bool isAReg(string s){
	return ((s.size() == 2) && (s[0] == 'R') && (s[1] >= '0') && (s[1] <= '9')) ;
}

int getReg(string s){
	return s[1] - '0';
}

void Module::fillOpCodeMap(){
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

void Module::fillOpTypeMap(){
	opTypeMap[0] = 0;
	opTypeMap[1] = 1;
	opTypeMap[2] = 1;
	opTypeMap[3] = 2;
	opTypeMap[4] = 2;
	opTypeMap[5] = 2;
	opTypeMap[6] = 2;
	opTypeMap[7] = 4;
	opTypeMap[8] = 1;
	opTypeMap[9] = 1;
	opTypeMap[10] = 2;
	opTypeMap[11] = 2;
	opTypeMap[12] = 2;
	opTypeMap[13] = 1;
	opTypeMap[14] = 1;
	opTypeMap[15] = 4;
	opTypeMap[16] = 3;
	opTypeMap[17] = 4;
	opTypeMap[18] = 1;
	opTypeMap[19] = 1;
	opTypeMap[20] = 0;
	opTypeMap[21] = 4;
	opTypeMap[22] = 4;
	opTypeMap[23] = 1;
	opTypeMap[24] = 3;
	opTypeMap[25] = 3;
	opTypeMap[26] = 1;
}

void Module::newInstruction(char n){
	mem.push_back(n);
	cout << "\t new instruction " << mem.size() << endl;
}

void Module::newInstruction(string s, char n){
	Dependency newDependency = {s, mem.size()};
	dependency.push_back(newDependency);
	cout << s << " " << mem.size() << endl;
	newInstruction(n);
}

Module::Module(char *inFile, char *outFile){
	this->inFile = inFile;
	this->outFile = outFile;
	this->fillOpTypeMap();
	this->fillOpCodeMap();
}

void Module::start(){
	int pc = 0;
	ifstream fin(inFile);
	string s, saux;
	stringstream ss, ssaux;
	for (; getline(fin, saux); ss.clear(), ssaux.clear()){
		ssaux.str(saux);
		getline(ssaux, s, ';');
		ss.str(s);
		string labelName;
		ss >> labelName;
		if (labelName.size() > 0)
			if (labelName[labelName.size() - 1] == ':'){
				labelName.erase(labelName.size() - 1, 1);
				string op;
				ss >> op;
				if (op == ".data"){
					int numBytes;
                    long long int value;
					ss >> numBytes >> value;
                    Data data_ = {labelName, numBytes, value};
					data.push_back(data_);
					cout << labelName << " " << numBytes << " " << value << endl;
				}
				else{
					Label label_ = {labelName, pc};
					label.push_back(label_);
					cout << labelName << " " << pc << endl;
					pc += 2;
				}
			}
			else pc += 2;
	}
	mem.reserve(pc);
	fin.close();
}

void Module::finish(){
	ifstream fin(inFile);
	string s, saux;
	stringstream ss, ssaux;
	int pc = 0;
	for (; getline(fin, saux); ss.clear(), ssaux.clear()){
		ssaux.str(saux);
		getline(ssaux, s, ';');	
		ss.str(s);
		string op;
		ss >> op;
		if (op.size() > 0){
			if (op[op.size() - 1] == ':')
				ss >> op;
			cout << op << " " << opCodeMap[op] << " " << opTypeMap[opCodeMap[op]] << endl;
			switch (opTypeMap[opCodeMap[op]]){
				case 0:{
					newInstruction(opCodeMap[op] << 3);
					newInstruction(0);
				} break;
				case 1:{
					string op1, op2;
					ss >> op1 >> op2;
					newInstruction((opCodeMap[op] << 3) + getReg(op1));
					if (isANumber(op2)){
						stringstream ss_(op2);
						int n = 0;
						ss_ >> n;
						newInstruction(n);
					}
					else{
						newInstruction(op2, 0);
					}
				} break;
				case 2:{
					string op1, op2;
					ss >> op1 >> op2;
					newInstruction((opCodeMap[op] << 3) + getReg(op1));
					newInstruction(getReg(op2) << 5);
				} break;
				case 3:{
					string op1, op2, op3;
					ss >> op1 >> op2 >> op3;
					newInstruction((opCodeMap[op] << 3) + getReg(op1));
					newInstruction((getReg(op2) << 5) + (getReg(op3) << 2));
				} break;
				case 4:{
					string op1;
					ss >> op1;
					newInstruction(opCodeMap[op] << 3);
					if (isANumber(op1)){
						stringstream ss_(op1);
						int n;
						ss_ >> n;
						newInstruction(n);
					}
					else{
						newInstruction(op1, 0);
					}
				} break;
			}
		}
	}
	fin.close();
}

void Module::write(){
	ofstream fout(outFile, ios::binary);
	ModuleHeader moduleHeader = {mem.size(), label.size(), data.size(), dependency.size()};
	writeModuleHeader(fout, moduleHeader);
	for (int i = 0; i < label.size(); i++)
		writeLabel(fout, label[i]);
	for (int i = 0; i < data.size(); i++)
		writeData(fout, data[i]);
	for (int i = 0; i < dependency.size(); i++)
		writeDependency(fout, dependency[i]);
	writeMem(fout, mem);
}
