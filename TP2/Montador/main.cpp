#include <iostream>
#include "Module.hpp"

using namespace std;

int main(int argc, char *argv[]){
	Module module =  Module(argv[1], argv[2]);
	module.process();
	module.write();
	return 0;
}
