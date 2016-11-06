#include <iostream>
#include <fstream>
#include "ObjectModule.hpp"
#include <vector>
#include <map>

using namespace std;

void readModuleHeader(ifstream &fin, ModuleHeader &moduleHeader){
	/* get data from file and put on moduleHeader passed */
	fin >> moduleHeader.memSize
		>> moduleHeader.labelSize
		>> moduleHeader.dataSize
		>> moduleHeader.inDependencySize
		>> moduleHeader.outDependencySize;
}

void readLabel(ifstream &fin, Label &label, int startPosition, int index){
	/* get label from file 'fin' */
	fin >> label.name
		>> label.pc;
	label.pc += startPosition + 1;
	label.name += "_" + to_string(index);
}

void readData(ifstream &fin, Data &data, int index){
	/* get data from file 'fin' */
	fin >> data.name
		>> data.numBytes
		>> data.value;
	data.name += "_" + to_string(index);
}

void readDependency(ifstream &fin, Dependency &dependency, int startPosition){
	/* get dependency from file 'fin' */
	fin >> dependency.s
		>> dependency.pc;
	dependency.pc += startPosition;
}

void mergeMemory(ifstream &fin, int memSize, int &pc, char *mem){
	int maxPc = pc + memSize;
	int x;
	for (; pc < maxPc; pc++){
		fin >> x;
		/* sets 'mem' array with value from 'fin'
 		 * on key = pc      */
		mem[pc] = x;
	}
}

ObjectModule::ObjectModule(char *fileName, int &pc, int index,
		map<string, int> &labelMap, vector<Data> &data, char *mem){
	/* arg[i] will come as *fileName. Then, i'll set it */
	this->fileName = fileName;
	startPosition = pc;

	/* set a ifstream for the file */
	ifstream fin(fileName);

	/* set a moduleHeader and */
	ModuleHeader moduleHeader;
	/* get data from file 'fin' */
	readModuleHeader(fin, moduleHeader);


	/* there we go with some loops to set some Vectors */

	/* loop to fill the label Vector */
	for (int i = 0; i < moduleHeader.labelSize; i++){
		Label label_;
		readLabel(fin, label_, startPosition, index);
		labelMap[label_.name] = label_.pc;
	}
	/* loop to set data Vector */
	for (int i = 0; i < moduleHeader.dataSize; i++){
		Data data_;
		readData(fin, data_, index);
		data.push_back(data_);
	}
	/* loop to set intern dependencies Vector */
	for (int i = 0; i < moduleHeader.inDependencySize; i++){
		Dependency dependency_;
		readDependency(fin, dependency_, startPosition);
		dependency_.s += "_" + to_string(index);
		inDependency.push_back(dependency_);
	}
	/* loop to set outer dependencies Vector */
	for (int i = 0; i < moduleHeader.outDependencySize; i++){
		Dependency dependency_;
		readDependency(fin, dependency_, startPosition);
		outDependency.push_back(dependency_);
	}
	/* sets memory with fin value */
	mergeMemory(fin, moduleHeader.memSize, pc, mem);
}

void ObjectModule::resolveDependencies(map<string, int> &labelMap, 
		char *mem, int index, int lastModuleIndex){
	/* for each dependency in intern dependency vector... */
	for (int i = 0; i < inDependency.size(); i++){
		/* ...get pc dependency */
		int pc = inDependency[i].pc;
		/* and set 'mem' vector in pc key with value got from labelMap */
		int value = labelMap[inDependency[i].s] - 1;
		mem[pc] = value;
	}
	for (int i = 0; i < outDependency.size(); i++){
		int pc = outDependency[i].pc;
		int value = -1;
		/* get outer dependencies and try to get it */
		for (int j = 0; (j < lastModuleIndex) && (value == -1); j++){
			if (j != index)
				if ((labelMap[outDependency[i].s + "_" + to_string(j)]) > 0){
					/* if do, set value with it */
					value = labelMap[outDependency[i].s + "_" + to_string(j)] - 1;
				}
		}
		if (value == -1)
			/* if cant, error! can't find dependency from a outer file */
			cout << "_____ERRO!_____";
		mem[pc] = value;
	}
}
