#include <iostream>
#include "Module.hpp"
#include "Linker.hpp"

using namespace std;

int main(int argc, char *argv[]){
	Linker& linker = Linker::getInstance();
	linker.makeInstance(argv[1], argc-2);
	linker.createModules(argc, argv);
	return 0;
}
