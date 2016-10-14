#ifndef Module_hpp
#define Module_hpp

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Module{
public:
    Module(char *fileName);
	void start();
private:
    int pc;
    char *fileName;
    char mem[256];
    map<string, int> privateMap;
};

#endif /* Module_hpp */
