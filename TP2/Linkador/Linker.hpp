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
	Linker(int argc, char *argv[]);
	void resolveDependencies();
	void initializeData();
	void writeMemory();
};
