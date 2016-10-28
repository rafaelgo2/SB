#include "ObjectModule.hpp"
#include <vector>
#include <string>
#include <map>

using namespace std;

class Linker{
private:
	int argc;
	char **argv;
	vector<ObjectModule*> objModule;
	map<string, Label> labelMap;
	map<string, Data> dataMap;
	char memory[256];
	int pc;
public:
	Linker(int argc, char *argv[]);
	void startModules();
	void resolveDependencies();
	void writeMemory();
};
