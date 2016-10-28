#include "Module.hpp"
#include <fstream>
#include <sstream>
#include <bitset>
#include <iostream>

void writeData(ofstream &fout, Data &data){
	fout << data.name << " "
		 << data.numBytes << " "
		 << data.value << " "
		 << endl;
}

void writeDependency(ofstream &fout, Dependency &dependency){
	fout << dependency.s << " "
		 << dependency.pc
		 << endl;
}

void writeLabel(ofstream &fout, Label &label){
	fout << label.name << " "
		 << label.pc
		 << endl;
}

void writeModuleHeader(ofstream &fout, ModuleHeader &moduleHeader){
	fout << moduleHeader.memSize << " "
		 << moduleHeader.labelSize << " "
		 << moduleHeader.dataSize << " "
		 << moduleHeader.inDependencySize << " "
		 << moduleHeader.outDependencySize
		 << endl;
}

void writeMem(ofstream &fout, char mem[256], int memSize){
	for (int i = 0; i < memSize; i++)
		fout << bitset<8>(mem[i]) << endl;
}

bool isANumber(string s){
	int init = 0;
	if (s[0] == '-')
		init = 1;
	for (int i = init; i < s.size(); i++){
		if ((s[i] < '0') || (s[i] > '9')){	
			return false;
		}
	}
	cout << s << " é um número! " << endl;
	return true;
}


bool isAReg(string s){
	return ((s.size() == 2) && (s[0] == 'R') && (s[1] >= '0') && (s[1] <= '9')) ;
}

char getReg(string s){
	cout << "ID Registrador: " << s[1] - '0' << endl;
	return s[1] - '0';
}

bool isIO(string s){
	if (((s.size() == 2) && (s[0] == 'I') && (s[1] == 'O')))
		cout << "É IO!" << endl;
	return ((s.size() == 2) && (s[0] == 'I') && (s[1] == 'O'));
}

char getIO(){
	return 254;
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
	opCodeMap[".data"] = 27;
	opCodeMap[".extern"] = 28; //nao sei se isso ta certo
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
	opTypeMap[27] = 99;
	opTypeMap[28] = 5;
}

void Module::newInstruction(char n){
	cout << "Nova Instrução(" << memSize << "): " << n + 0 << endl; 	
	mem[memSize] = n;
	memSize++;
}

void Module::newInstruction(string s, Type type){
	Dependency newDependency = {s, memSize};
	switch (type){
		case (IN):{	
			cout << "Criando uma dependencia INTERNA: " << s << endl;
			inDependency.push_back(newDependency);
		} break;
		case (OUT):{
			cout << "Criando uma dependencia EXTERNA: " << s << endl;
			outDependency.push_back(newDependency);
		} break;
	}
	newInstruction(0);
}

Module::Module(char *inFile, char *outFile){
	cout << "Iniciando Montador" << endl
		 << "Arquivo .a: " << inFile << endl
		 << "Arquivo Objeto: " << outFile << endl << endl;
	this->inFile = inFile;
	this->outFile = outFile;
	this->fillOpTypeMap();
	this->fillOpCodeMap();
	this->memSize = 0;
}

void Module::process(){
	ifstream fin(inFile);
	string s, saux;
	stringstream ss, ssaux;
	while (getline(fin, saux)){
		ssaux.str(saux);
		getline(ssaux, s, ';');
		cout << "Linha: " << s << endl;
		ss.str(s);

		string op;
		ss >> op;
		if (op.size() > 0){
			cout << "PC: " << memSize << endl; 
			if (op[op.size() - 1] == ':'){
				op.erase(op.size() - 1, 1);
				string labelName = op;
				cout << "Label encontrado: " << labelName << endl;
				ss >> op;
				if (op == ".data"){
					int numBytes;
                    long long int value;
					ss >> numBytes >> value;
                    Data data_ = {labelName, numBytes, value};
					data.push_back(data_);
					cout << "Bytes: " << numBytes  << " | Valor: " << value << endl;
				}
				else{
					Label label_ = {labelName, memSize};
					label.push_back(label_);
				}
			}
			cout << "Operacao: |" << op << "|" << endl;	
			cout << "Código: |" << opCodeMap[op] + 0 << "|" << endl;
			cout << "Tipo: |" << opTypeMap[opCodeMap[op]] << "|" << endl;
			switch (opTypeMap[opCodeMap[op]]){
				case 0:{
					newInstruction(opCodeMap[op] << 3);
					newInstruction(0);
				} break;
				case 1:{
					string op1, op2;
					ss >> op1 >> op2;
					cout << "Operadores: |" << op1 << "| |" << op2 << "|" << endl;
					newInstruction( (opCodeMap[op] << 3) + getReg(op1));
					if (isANumber(op2)){
						stringstream ss_(op2);
						int n;
						ss_ >> n;
						newInstruction(n);
					}
					else if (isIO(op2)){
						newInstruction(getIO());
					}	
					else{
						newInstruction(op2, IN);
					}
				} break;
				case 2:{
					string op1, op2;
					ss >> op1 >> op2;
					cout << "Operadores: |" << op1 << "| |" << op2 << "|" << endl; 
					newInstruction((opCodeMap[op] << 3) + getReg(op1));
					newInstruction(getReg(op2) << 5);
				} break;
				case 3:{
					string op1, op2, op3;
					ss >> op1 >> op2 >> op3;
					cout << "Operadores: |" << op1 << "| |" << op2 << "| |" << op3 << "|" << endl;
					newInstruction((opCodeMap[op] << 3) + getReg(op1));
					newInstruction((getReg(op2) << 5) + (getReg(op3) << 2));
				} break;
				case 4:{
					string op1;
					ss >> op1;
					cout << "Operadore: |" << op1 << "|" << endl;
					newInstruction(opCodeMap[op] << 3);
					if (isANumber(op1)){
						stringstream ss_(op1);
						int n;
						ss_ >> n;
						newInstruction(n);
					}
					else if (isIO(op1)){
						newInstruction(getIO());
					}
					else{
						newInstruction(op1, IN);
					}
				} break;
				case 5:{
					string op1;
					ss >> op1;
					cout << "Operadore: |" << op1 << "|" << endl;
					newInstruction(opCodeMap["jump"] << 3);
					newInstruction(op1, OUT);
				} break;
			}
			cout << endl;
		}
		s.clear();
		ss.clear();
		saux.clear();
		ssaux.clear();
	}
	fin.close();
}

void Module::write(){
	ofstream fout(outFile, ios::binary);
	ModuleHeader moduleHeader = {memSize, label.size(), data.size(), inDependency.size(), outDependency.size()};
	writeModuleHeader(fout, moduleHeader);
	for (int i = 0; i < label.size(); i++)
		writeLabel(fout, label[i]);
	for (int i = 0; i < data.size(); i++)
		writeData(fout, data[i]);
	for (int i = 0; i < inDependency.size(); i++)
		writeDependency(fout, inDependency[i]);
	for (int i = 0; i < outDependency.size(); i++)
		writeDependency(fout, outDependency[i]);
	writeMem(fout, mem, memSize);
}
