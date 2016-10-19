#include "Module.hpp"
#include "Linker.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Module::Module(char *fileName){
    this->fileName = fileName;
	fill(this->mem, this->mem+256, 0);
	this->size = 0;
}

void Module::start(){
	int pc = 0;
	ifstream fin(fileName);
	string s, saux;
	stringstream ss, ssaux;
	for (; getline(fin, saux); ss.clear(), ssaux.clear()){
		ssaux.str(saux);
		getline(ssaux, s, ';');
		ss.str(s);
		string label;
		ss >> label;
		if (label.size() > 0)
			if (label[label.size() - 1] == ':'){
				label.erase(label.size() - 1, 1);
				string op;
				ss >> op;
				if (op == ".data"){
					int numBytes;
                    long long int value;
					ss >> numBytes >> value;
                    Memory mem = {numBytes, value, -1};
					privateMemory[label] = mem;
				}
				else{
					linker.publicMap[label] = pc + 1;
					pc += 2;
				}
			}
			else pc += 2;
	}
	size = pc;
	fin.close();
}
