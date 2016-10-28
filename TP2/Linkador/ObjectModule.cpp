#include <fstream>
#include "ObjectModule.hpp"
#include <vector>

ObjectModule::ObjectModule(int startPosition, int pc){
	this->startPosition = startPosition;
}

void ObjectModule::fillLabelMap( std::map<string, Label> labelMap){

}

void ObjectModule::fillDataMap( map<string, Data>, int pc){

}