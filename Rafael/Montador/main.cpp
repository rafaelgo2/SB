#include <iostream>
#include "Module.hpp"

using namespace std;

int main(int argc, char *argv[]){
	Module module(argv[1], argv[2]);
	module.start();
	module.finish();
	module.write();
	return 0;
}
