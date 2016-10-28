#include <fstream>

Linker::Linker(int argc, char *argv[]){
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
