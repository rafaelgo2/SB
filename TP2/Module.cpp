#include "Module.hpp"

Module::Module(char *fileName){
    this->fileName = fileName;
    fill(this->mem, this->mem+256, 0);
    this->pc = 0;
}