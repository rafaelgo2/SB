#include <iostream>
#include "Linker.hpp"
#include "Module.hpp"

using namespace std;

int main(int argc, char *argv[]){
	Linker::makeInstance(argv[1], argc - 2);
	Linker& linker = Linker::getInstance();
	linker.createModules(argc, argv);
	return 0;
}
