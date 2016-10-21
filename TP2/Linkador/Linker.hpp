#include "ObjectModule.hpp"
#include <vector>

using namespace std;

class Linker{


private:
	vector<ObjectModule*> objModule;	


private:
	static Linker *instance;
	static Linker *getInstance();
	static void startInstance(int argc, char *argv[]);
}
