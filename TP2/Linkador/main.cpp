#include "Linker.hpp"

using namespace std;

int main(int argc, char *argv[]){
	Linker linker = Linker(argc, argv);
	linker.initializeData();
	linker.resolveDependencies();
	linker.writeMemory();
	return 0;
}
