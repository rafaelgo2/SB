#include <fstream>

Linker *Linker::instance = NULL;

Linker *Linker::getInstance(){
	if (instance == NULL)
		instance = new Linker();
	return instance;
}

void startInstance(int argc, char *argv[]){
	int objModuleSize = argc-2;	
	objModule.reserve(objModuleSize);
	ObjectModule *obj;
	for (int i = 2; i < objModuleSize; i++){
		obj = new ObjectModule(argv[i]);
		objModule.push_back(obj);
	}
}
