#include "Linker.hpp"

Linker *Linker::instance = NULL;

Linker &Linker::getInstance(){
	if (instance == NULL){
			instance = new Linker();
	}
	return *instance;
}

void Linker::makeInstance(char *fileName, int capacity){
	this->fileName = fileName;
	this->capacity = capacity;
	this->module.reserve(capacity);

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

	publicMap["R0"] = 0;
	publicMap["R1"] = 1;
	publicMap["R2"] = 2;
	publicMap["R3"] = 3;
	publicMap["R4"] = 4;
	publicMap["R5"] = 5;
	publicMap["R6"] = 6;
	publicMap["R7"] = 7;
	publicMap["IO"] = 254;
}

void Linker::createModule(char *fileName){
    fill(mem, mem+256, 0);
	module.push_back(new Module(fileName));
	cout << fileName << endl;
	module[module.size() - 1]->start();
}

void Linker::createModules(int argc, char *argv[]){
	cout << "Arquivo Saida: " << argv[1] << endl
		 << "Quantidade Arquivos Entrada: " << argc - 2 << endl;	
	for (int i = 2; i < argc; i++){
		cout << i-2 << ": " << argv[i] << endl;
		this->createModule(argv[i]);
	}
}



void Linker::begin(ofstream &fout){
	fout << "DEPTH = 256;" << endl
		 << "WIDTH = 8;" << endl
		 << "ADDRESS_RADIX = HEX;" << endl
		 << "DATA_RADIX = BIN;" << endl
		 << "CONTENT" << endl
		 << "BEGIN" << endl << endl;
}

void Linker::end(ofstream &fout){
	fout << "END;";
}

