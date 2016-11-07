#include <vector>
#include <string>
#include <map>

using namespace std;

/* consts */
enum Type{
	IN,
	OUT
};

/* .data instruction struct */
typedef struct{
	string name; // label
    int numBytes;
    long long int value;
} Data;

/* dependency struct */
typedef struct{
	string s;	
	int pc;
} Dependency;

/* label struct */
typedef struct{
    string name;
    int pc; // position that label was get
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

	/* 	Object Module Constructor */
	ObjectModule(char *fileName, int &pc, int index,
		map<string, int> &labelMap, vector<Data> &data, char *mem);

	/* Resolve each dependency (in or out)
  	 * then set the 'mem' array with their value */
	void resolveDependencies(map<string, int> &labelMap, 
		char *mem, int index, int lastModuleIndex);
};
