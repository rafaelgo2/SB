#ifndef Module_hpp
#define Module_hpp

#include <map>
#include <vector>
#include <string>

using namespace std;

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
	int labelSize;
	int dataSize;
	int dependencySize;
} ModuleHeader;


class Module{
public:	
    Module(char *inFile, char *outFile);
	void start();
	void finish();
	void write();
private:
	void newInstruction(char n);
	void newInstruction(string s, char n);
	void fillOpCodeMap();
	void fillOpTypeMap();
	char *inFile, *outFile;

	map<string, int> opCodeMap;
	int opTypeMap[27];

	vector<char> mem;
	vector<Label> label;
	vector<Data> data;
	vector<Dependency> dependency;
};

#endif /* Module_hpp */
