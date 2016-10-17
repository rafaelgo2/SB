#include "Module.hpp"
#include "Linker.hpp"
#include <fstream>
#include <iostream>

Module::Module(char *fileName){
    this->fileName = fileName;
    fill(this->mem, this->mem+256, 0);
    this->pc = 0;
}

void Module::start(){
	cout << "!" << fileName << "!" << endl;
	ifstream fin(fileName);
	string s, saux;
	stringstream ss, ssaux;
	ifstream fin(argv[1]);
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
                    Memory mem = {numBytes, value};
					memory.push_back(mem);
					cout << "Memory: ";
				}
				else{
					privateMap[label] = pc + 1;
					pc += 2;
					cout << "Label: ";
				}
				cout << label << endl;
			}
			else pc += 2;
	}
	fin.close();
}
