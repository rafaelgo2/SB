#include <iostream>
#include <fstream>
#include <map>

using namespace std;

void fillFunction(map<string, int> &opCode){
	function["nome"] = opCode;
}

/*  Decodica a instrução, minha ideia é criar uma função pra decodificar
    cada tipo de instrução
    */
void buildInstruction(char instruction, ofstream outFile){
    char *opCode=strchr(instruction, ' ');
    switch(opCode){
        case "exit":
            cout << "0000000000000000";
            break;
        case "loadi":
            break;
        case "storei":
            break;
        case "add":
            break;
        case "subtract":
            break;
        case "multiply":
            break;
        case "divide":
            break;
        case "jump":
            break;
        case "jmpz":
            break;
        case "jmpn":
            break;
        case "move":
            break;
        case "load":
            break;
        case "store":
            break;
        case "loadc":
            break;
        case "clear":
            break;
        case "moveSp":
            break;
        case "slt":
            break;
        case "call":
            break;
        case "loadSp":
            break;
        case "storeSp":
            break;
        case "ret":
            break;
        case "loadRa":
            break;
        case "storeRa":
            break;
        case "addi":
            break;
        case "sgt":
            break;
        case "seq":
            break;
        case "jumpp":
            break;
    }
}

int main(int argc, char *argv[]){
	map<string, int> label, opCode;
	ifstream inFile;
    ofstream outFile;
    int line = 0;	
	string s;
    
    inFile.open(argv[0]);
    outFile.open(argv[1]);
	
	while (fin >> s){
		if (s[0] == '_'){
			label[s] = line;
			fin >> s;		
		}
    }
	
	return 0;
}
