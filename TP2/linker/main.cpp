#include "Linker.hpp"

using namespace std;

/*
 * Main function from Linker lib
 *
 * Get args file names and calls the main functions to make the link
 * (more funcs info, see Linker Header file)
 * */
int main(int argc, char *argv[]){
	Linker linker = Linker(argc, argv);
	linker.initializeData();
	linker.resolveDependencies();
	linker.writeMemory();
	return 0;
}
