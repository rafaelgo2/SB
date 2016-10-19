#include "Linker.hpp"

Linker &Linker::getInstance(){
	if (instance == NULL){
			instance = new Linker();
	}
	return *instance;
}

void Linker::makeInstance(char *_fileName, int _capacity){
	fileName = _fileName;
	capacity = _capacity;
}

void Linker::createModules(int argc, char *argv[]){
	for (int i = 2; i <= argc; i++){
		this->createModule(argv[i]);
		this->getModule(this->getModuleSize() - 1).start();
	}
}
