#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	system("make -C ../Montador all");
	system("cp ../Montador/montador.exe montador.exe");

	system("make -C ../Linkador all");
	system("cp ../Linkador/linkador.exe linkador.exe");

	for (int i = 1; i < argc-1; i++){
		printf("Montando %d!\n", i);
		char montar[255];
		sprintf(montar, "./montador.exe %s saidaTmp%d.obj", argv[i], i);
		system(montar);
		printf("%s\n", montar);
	}	

	char args[9999] = "";
	for (int i = 1; i < argc-1; i++){
		printf("Linkando %d!\n", i);
		char link[999];
		sprintf(link, "saidaTmp%d.obj ", i);
		strcat(args, link);
	}
	char linkar[1100];
	sprintf(linkar, "./linkador.exe %s %s", argv[argc-1], args);
	printf("%s\n", linkar);

	system(linkar);	
	
	for (int i = 1; i < argc-1; i++){
		char remove[999];
		sprintf(remove, "rm *.exe saidaTmp%d.obj", i);	
		system(remove);
	}
}
