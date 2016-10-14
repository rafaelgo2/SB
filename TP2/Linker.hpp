#ifndef Linker_hpp
#define Linker_hpp

#include "Module.hpp"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Linker{
public:
	static void makeInstance(char *fileName, int capacity);
	static Linker& instance;
	static Linker& getInstance(){
		return instance;
	};
	void createModules(int argc, char *argv[]);
	char *getFileName() { return this->fileName; };
	int getSize() { return this->size; };
	int getCapacity() { return this->capacity; };
	Module getModule(int index) { return this->module[index]; };
	int getModuleSize() { return this->module.size(); };
	void createModule(char *fileName) { this->module.push_back(Module(fileName)); };
	int getPublicMap(string s) { return this->publicMap[s]; };
private:
    Linker(char *fileName, int capacity);
    char *fileName;
    int size;
    int capacity;
    vector<Module> module;
    map<string, int> publicMap;
};


#endif /* Linker_hpp */
