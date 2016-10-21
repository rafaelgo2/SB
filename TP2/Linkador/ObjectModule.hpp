#include <vector>
#include <string>

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
	ObjectModule(int startPosition);
	
	int getMemorySize() { return mem.size(); }
};
