#include <iostream>
#include <fstream>
#include <map>

using namespace std;

void fillFunction(map<string, int> &function){
	function["nome"] = opCode;
}

int main(int argc, char *argv[]){
	map<string, int> label, function;
	fstream fin(argv[1]), fout(argv[2]);
	int line = 0;	
	string s;
	while (fin >> s){
		if (s[0] == '_'){
			label[s] = line;
			fin >> s;		
		}
		
	}
	return 0;
}
