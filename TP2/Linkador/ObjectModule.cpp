#include <fstream>
#include "ObjectModule.hpp"
#include <vector>
#include <map>

using namespace std;

void readData(ifstream &fin, Data &data, int index){
	fin >> data.name
		>> data.numBytes
		>> data.value;
	data.name += index;
}

void readDependency(ifstream &fin, Dependency &dependency, int startPosition){
	fin >> dependency.s
		>> dependency.pc;
	dependency.pc += startPosition;
}

void readLabel(ifstream &fin, Label &label, int startPosition, int index){
	fin >> label.name
		>> label.pc;
	label.pc += startPosition;
	label.name += index;
}

void readModuleHeader(ifstream &fin, ModuleHeader &moduleHeader){
	fin >> moduleHeader.memSize
		>> moduleHeader.labelSize
		>> moduleHeader.dataSize
		>> moduleHeader.inDependencySize
		>> moduleHeader.outDependencySize;
}

void mergeMemory(ifstream &fin, int memSize, int &pc, char *mem){
	int maxPc = pc + memSize;
	int x;
	for (; pc < maxPc; pc++){
		fin >> x;
		mem[pc] = x;
	}
}

ObjectModule::ObjectModule(char *fileName, int &pc, int index,
		map<string, int> &labelMap, vector<Data> &data, char *mem){
	this->fileName = fileName;
	startPosition = pc;
	ifstream fin(fileName);
	ModuleHeader moduleHeader;
	
	readModuleHeader(fin, moduleHeader);
	for (int i = 0; i < moduleHeader.labelSize; i++){
		Label label_;
		readLabel(fin, label_, startPosition, index);
		labelMap[label_.name] = pc + 1;
	}
	for (int i = 0; i < moduleHeader.dataSize; i++){
		Data data_;
		readData(fin, data_, index);
		data.push_back(data_);
	}
	for (int i = 0; i < moduleHeader.inDependencySize; i++){
		Dependency dependency_;
		readDependency(fin, dependency_, startPosition);
		dependency_.s += i;
		inDependency.push_back(dependency_);
	}
	for (int i = 0; i < moduleHeader.outDependencySize; i++){
		Dependency dependency_;
		readDependency(fin, dependency_, startPosition);
		outDependency.push_back(dependency_);
	}
	mergeMemory(fin, moduleHeader.memSize, pc, mem);
}

void ObjectModule::resolveDependencies(map<string, int> &labelMap, 
		char *mem, int lastModuleIndex){
	for (int i = 0; i < inDependency.size(); i++){
		int pc = inDependency[i].pc;
		int value = labelMap[inDependency[i].s] - 1;
		mem[pc] = value;
	}
	for (int i = 0; i < outDependency.size(); i++){
		int pc = outDependency[i].pc;
		int value;
		for (int j = 0; j < lastModuleIndex; j++){
			if ((labelMap[outDependency[i].s + to_string(j)]) > 0){
				value = labelMap[outDependency[i].s + to_string(j)] - 1;
			}
		}
		mem[pc] = value;
	}
}
