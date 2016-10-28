#include <vector>
#include <string>
#include "Linker.hpp"

using namespace std;

typedef struct{
	string s;	
	int pc;
} Dependency;

typedef struct{
	int memSize;
	int labelSize;
	int dataSize;
	int dependencySize;
} ModuleHeader;

class ObjectModule{
private:
	ModuleHeader mh;
	vector<char> mem;
	vector<Dependency> dependency;
	int startPosition;
public:
	ObjectModule(int startPosition, int pc);
	unsigned long getMemorySize() { return mem.size(); }
	void fillLabelMap(map<string, Label> labelMap);
	void fillDataMap( map<string, Data> label, int pc);
};
