#ifndef Linker_hpp
#define Linker_hpp
#include "Module.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

class Linker{

private:
    char *fileName;
    int size;
    int capacity;
    vector<Module*> module;
    map<string, int> publicMap;
	map<string, int> opCodeMap;
	void createModule(char *fineName);
    char mem[256];
	int pc;
public:
	void makeInstance(char *fileName, int capacity);
	void createModules(int argc, char *argv[]);
	int getSize() { return size; }
	map<string, int> &getPublicMap() { return publicMap; }
	void begin(ofstream &fout);
	void end(ofstream &fout);

//singleton
private:
	static Linker* instance;
public:
	static Linker &getInstance();
};

#endif /* Linker_hpp */
