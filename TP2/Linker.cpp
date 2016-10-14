#include "Linker.hpp"

void Linker::makeInstance(char *fileName, int capacity){
	Linker::instance = Linker(fileName, capacity);
}

Linker::Linker(char *fileName, int capacity){
    this->fileName = fileName;
    this->capacity = capacity;
    this->module.reserve(capacity);
}

void Linker::createModules(int argc, char *argv[]){
	for (int i = 2; i <= argc; i++){
		this->createModule(argv[i]);
		this->getModule(this->getModuleSize() - 1).start();
	}
}
