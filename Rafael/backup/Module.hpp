#ifndef Module_hpp
#define Module_hpp

#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef struct{
	int numBytes;
	long long int value;
	int pc;
} Memory;

class Module{
public:	
    Module(char *fileName);
	void start();
    char mem[256];
private:
    char *fileName;
    map<string, int> privateMap;
	map<string, Memory> privateMemory;
	int size;
};

#endif /* Module_hpp */
