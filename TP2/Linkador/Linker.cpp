#include <fstream>

Linker *Linker::instance = NULL;

Linker *Linker::getInstance(){
	if (instance == NULL)
		instance = new Linker();
	return instance;
}

void Linker::startInstance(int argc, char *argv[]){
	//pc = 0;

	this->argc = argc;
	this->argv = argv;
	int objModuleSize = argc-2;	
	objModule.reserve(objModuleSize);
	ObjectModule *obj;
	for (int i = 2; i < objModuleSize; i++){
		obj = new ObjectModule(argv[i], pc);
		obj->fillLabelMap(labelMap);	
		objModule.push_back(obj);
		pc += obj->getMemorySize();		
	}
	for (int i = 0; i < objModule.size(); i++){
		obj->fillDataMap(dataMap, pc);
	}
}

void Linker::resolveDependencies(){

}

void Linker::writeMemory(){
	
}
