#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    static const std::string PLATFORM="WIN";
#else
    static const std::string PLATFORM="UNIX";
#endif

int main(int argc, char *argv[]){

    system("make -C ../Montador all");
    system("make -C ../Linkador all");

    if(PLATFORM == "WIN"){
        system("cp ../Montador/montador.exe montador.exe");
        system("cp ../Linkador/linkador.exe linkador.exe");
    } else {
        system("cp ../Montador/montador montador");
        system("cp ../Linkador/linkador linkador");
    }

	for (int i = 1; i < argc-1; i++){
		printf("Montando %d!\n", i);
		char montar[255];
        if(PLATFORM == "WIN"){
            sprintf(montar, "./montador.exe %s saidaTmp%d.obj", argv[i], i);
        } else {
            sprintf(montar, "./montador %s saidaTmp%d.obj", argv[i], i);
        }
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
    if(PLATFORM == "WIN"){
        sprintf(linkar, "./linkador.exe %s %s", argv[argc-1], args);
    } else {
        sprintf(linkar, "./linkador %s %s", argv[argc-1], args);
    }
	printf("%s\n", linkar);

	system(linkar);

	for (int i = 1; i < argc-1; i++){
		char remove[999];
		sprintf(remove, "rm *.exe saidaTmp%d.obj", i);
		system(remove);
	}
}
