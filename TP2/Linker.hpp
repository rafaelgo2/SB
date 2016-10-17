#ifndef Linker_hpp
#define Linker_hpp

#include "Module.hpp"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Linker{

private:
    char *fileName;
    int size;
    int capacity;
    vector<Module> module;
    map<string, int> publicMap;
public:
	void makeInstance(char *fileName, int capacity);
	void createModules(int argc, char *argv[]);

private
	static Linker* instance;
public
	static Linker &getInstance();

};

Linker *Linker::instance = NULL;

#endif /* Linker_hpp */
