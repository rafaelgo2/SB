#include "Linker.hpp"

using namespace std;

int main(int argc, char *argv[]){
	Linker *linker = Linker::getInstance();	
	linker->startLinker(argc, argv);
	linker->resolveDependencies();
	linker->writeMemory();
	return 0;
}
