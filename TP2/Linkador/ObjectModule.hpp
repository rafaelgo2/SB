#include <vector>
#include <string>
#include <map>

using namespace std;

enum Type{
	IN,
	OUT
};

typedef struct{
    string name;
    int numBytes;
    long long int value;
} Data;

typedef struct{
	string s;	
	int pc;
} Dependency;

typedef struct{
    string name;
    int pc;
} Label;


typedef struct{
	int memSize;
	unsigned long labelSize;
	unsigned long dataSize;
	unsigned long inDependencySize;
	unsigned long outDependencySize;
} ModuleHeader;

class ObjectModule{
private:
	int indice;
	ModuleHeader mh;
	int memorySize;
	vector<Dependency> inDependency;
	vector<Dependency> outDependency;
	int startPosition;
	char *fileName;
public:
	ObjectModule(char *fileName, int &pc, int index,
		map<string, int> &labelMap, vector<Data> &data, char *mem);
	void resolveDependencies(map<string, int> &labelMap, 
		char *mem, int lastModuleIndex);
	unsigned long getMemorySize() { return memorySize; }
};
