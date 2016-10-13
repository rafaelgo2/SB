//
//  Linker.hpp
//  
//
//  Created by Rafael Grandsire de Oliveira on 10/13/16.
//
//

#ifndef Linker_hpp
#define Linker_hpp

#include "Module.hpp"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Linker{
public:
    static Linker &instance;
    static Linker& getInstance();
    void initialize(char *fileName, int capacity);
private:
    char *fileName;
    int size;
    int capacity;
    vector<Module> module;
    map<string, int> publicLabelMap;
    map<string, int> privateLabelMap;
    Linker(){};
};

#endif /* Linker_hpp */
