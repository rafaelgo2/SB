#ifndef Module_hpp
#define Module_hpp

#include <map>
#include <vector>

using namespace std;

typedef struct{
	int numBytes;
	long long int value;
	int pc;
} Memory;

typedef struct{
	int pc;
	string s;	
} Dependency;

class Module{
public:	
    Module(char *inFile, char *outFile);
	void start();
	void finish();
	void write();
private:
	void newInstruction(char n);
	void newInstruction_(char n, string s);
	void fillOpCodeMap();
	void fillOpTypeMap();
	char *inFile, *outFile;

	map<string, int> opCodeMap;
	int opTypeMap[27];

	vector<char> mem;
	map<string, int> labelMap;
	map<string, Memory> privateMemory;
	vector<Dependency> dependency;
};

#endif /* Module_hpp */
