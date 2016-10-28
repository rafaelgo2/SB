#include <fstream>
#include "ObjectModule.hpp"
#include <vector>
#include <map>

using namespace std;

ObjectModule::ObjectModule(int startPosition, int pc){
	this->startPosition = startPosition;
}

void ObjectModule::fillLabelMap( map<string, Label> labelMap){

}

void ObjectModule::fillDataMap( map<string, Data>, int pc){

}