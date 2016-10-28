#include <fstream>
#include <bitset>
#include <iomanip>
#include "Linker.hpp"

using namespace std;

Linker::Linker(int argc, char *argv[]){
	fileName = argv[1];
	pc = 0;
	objModule.reserve( (unsigned long) argc-2);
	for (int i = 2; i < argc; i++){
		objModule.push_back(ObjectModule(argv[i] , pc, i-2,
								labelMap, dataVec, mem));
	}
}

void Linker::initializeData(){
	for (int i = 0; i < dataVec.size(); i++){
		labelMap[dataVec[i].name] = pc + 1;
		while(dataVec[i].numBytes--)
			mem[pc++] = dataVec[i].value >> (8 * dataVec[i].numBytes);
	}
}

void Linker::resolveDependencies(){
	for (int i = 0; i < objModule.size(); i++){
		objModule[i].resolveDependencies(labelMap, mem, objModule.size());
	}
}

void Linker::writeMemory(){
	ofstream fout(fileName);
	fout << "DEPTH = 256;" << endl
		 << "WIDTH = 8;" << endl
		 << "ADDRESS_RADIX = HEX;" << endl
		 << "DATA_RADIX = BIN;" << endl
		 << "CONTENT" << endl
		 << "BEGIN" << endl << endl;

	for (int i = 0; i < 256; i++){
		int init = i;
		char inst = mem[i];		
		while((mem[i] == inst) && (i<256))
			i++;
		if (i == init){
			fout << hex << uppercase << setfill('0') << setw(2) << i << " : "
				 << bitset<8>(inst) << " ;" << endl;
		}
		else{
			fout << '[' << hex << uppercase << setfill('0') << setw(2) << init << ".."
				 << hex << uppercase << setfill('0') << setw(2) << i << "] : "
				 << bitset<8>(inst) << " ;" << endl;
		}
	}
	fout << "END;";
}
