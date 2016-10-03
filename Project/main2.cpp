#include <map>
#include <iostream>

typedef struct{
	int numBytes;
	int value;
} mem;

using namespace std;

int main(){
	map<string, mem> memMap;
	mem mem_ = {10, 12};
	memMap["Oi"] = mem_; 
	cout << memMap.size();
}
