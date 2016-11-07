#ifndef Module_hpp
#define Module_hpp

#include <map>
#include <vector>
#include <string>

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

class Module{
public:	
    Module(char *inFile, char *outFile);
	void process();
	void write();
private:
	void fillOpCodeMap();
	void fillOpTypeMap();

	void newInstruction(char n);
	void newInstruction(string s, Type type);
	char *inFile, *outFile;

	map<string, char> opCodeMap;
	int opTypeMap[29];

	int memSize;
	char mem[256];
	vector<Label> label;
	vector<Data> data;
	vector<Dependency> inDependency;
	vector<Dependency> outDependency;
};

#endif /* Module_hpp */
