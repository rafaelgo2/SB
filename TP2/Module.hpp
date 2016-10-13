#ifndef Module_hpp
#define Module_hpp

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Module{
private:
    int pc;
    char *fileName;
    char mem[256];
    map<string, int> privateLabelMap;
private:
    Module(char *fileName);
};

#endif /* Module_hpp */
