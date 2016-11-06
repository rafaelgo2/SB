#include "ObjectModule.hpp"
#include <vector>
#include <string>
#include <map>

using namespace std;

class Linker{
private:
	char *fileName;
	int argc;
	char **argv;
	vector<ObjectModule> objModule;
	map<string, int> labelMap;
	vector<Data> dataVec;
	char mem[256];
	int pc;
public:
	/*	Linker constructor
	 * 	init data with args params and set memory and data initial values */
	Linker(int argc, char *argv[]);

	/* Resolve each dependency (in or out) from ObjectModule of this instance
 	 * then set the 'mem' array with their value */
	void resolveDependencies();

	/* init data -> set the labelMap and initial mem values */
	void initializeData();

	/* Write 'mem' char array on file 'fout'    */
	void writeMemory();
};
