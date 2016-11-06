#include <fstream>
#include <bitset>
#include <iomanip>
#include <algorithm>
#include "Linker.hpp"

using namespace std;

Linker::Linker(int argc, char *argv[]){
    /* get the first file name  */
	fileName = argv[1];
	/* start pc on 0  */
	pc = 0;
	/* Requests that the vector capacity be at least enough to contain argc-2 elements. */
	objModule.reserve((unsigned long) argc-2);
	/* set all positions from mem to zero */
	fill(mem, mem+256, 0);

	/* for each args... */
	for (int i = 2; i < argc; i++){
		/* ...push on objModule array a instance of ObjectModule */
		objModule.push_back(ObjectModule(argv[i], pc, i-2,
								labelMap, dataVec, mem));
	}
}

void Linker::initializeData(){
    /* for each dataVec... */
    for (int i = 0; i < dataVec.size(); i++){
        /* ...fills the labelMap with pc + 1 (with name as key) */
        labelMap[dataVec[i].name] = pc + 1;

		while(dataVec[i].numBytes--)
            /* sets the 'pc' position of mem vector with the bin of dataVec value
             * (with numBytes size) then add 1 to pc */
            mem[pc++] = dataVec[i].value >> (8 * dataVec[i].numBytes);
	}
}

void Linker::resolveDependencies(){
    /* for each objModule... */
    for (int i = 0; i < objModule.size(); i++){
        /* ...resolve their dependency */
        objModule[i].resolveDependencies(labelMap, mem, i, objModule.size());
	}
}

void Linker::writeMemory(){
    /* open ofstream to file out */
    ofstream fout(fileName);
    /* write file default header */
    fout << "DEPTH = 256;" << endl
		 << "WIDTH = 8;" << endl
		 << "ADDRESS_RADIX = HEX;" << endl
		 << "DATA_RADIX = BIN;" << endl
		 << "CONTENT" << endl
		 << "BEGIN" << endl << endl;

    /* starts to write the 'mem' in file */
    for (int i = 0; i < 256; i++){
		int init = i;
		char inst = mem[i];		
		while((mem[i+1] == inst) && (i<256))
			i++;
        /* write binary with length 8 in file  */
        if (i == init){
			fout << hex << uppercase << setfill('0') << setw(2) << i << " : "
				 << bitset<8>(inst) << " ;" << endl;
		}
		else{
            /* group same line binary code*/
            fout << '[' << hex << uppercase << setfill('0') << setw(2) << init << ".."
				 << hex << uppercase << setfill('0') << setw(2) << i << "] : "
				 << bitset<8>(inst) << " ;" << endl;
		}
	}
    /* file default footer */
    fout << "END;";
}
