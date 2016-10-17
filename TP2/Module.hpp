#ifndef Module_hpp
#define Module_hpp

#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef struct{
	int numBytes;
	long long int value;
} Memory;

class Module{
public:	
    Module(char *fileName);
	void start();
private:
    int pc;
    char *fileName;
    char mem[256];
    map<string, int> privateMap;
	vector<Memory> privateMemory;
};

#endif /* Module_hpp */
