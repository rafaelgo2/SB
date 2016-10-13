#include "Linker.hpp"

Linker& Linker::getInstance(){
    return Linker::instance;
}

void Linker::initialize(char *fileName, int capacity){
    this->fileName = fileName;
    this->capacity = capacity;
    this->module.reserve(capacity);
}