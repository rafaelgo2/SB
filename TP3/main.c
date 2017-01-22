#include "snake.h"

//SIZEQUEUE = N*M+1

int main(){
	Snake s;
	srand(time(NULL));
	while (1){
		srand(time(NULL));
		char direction;
		startSnake(&s);
		while (!end(&s)){
			print(&s);
			scanf("%c%*c", &direction);
			move(&s, direction);
		}
		if (won(&s)){
			printf("VENCEU!");
		}
		else{
			printf("PERDEU!");
		}
	}
	return 0;
}
