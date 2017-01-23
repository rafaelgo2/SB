#include <xc.h>

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR/VPP/RE3 Pin Function Select bit (MCLR/VPP/RE3 pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (Disabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)
#pragma config CCP2MX = RC1     // CCP2 Multiplex bit (CCP2 is on RC1)
#pragma config CP = OFF         // Flash Program Memory Code Protection bits (Code protection off)

// CONFIG2
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)
#pragma config BORSEN = OFF     // Brown-out Reset Software Enable bit (Disabled)

#include "atraso.h"
#include "lcd.h"
#include "snake.h"

void main(){
	char message[16] = "   pontos! RB1"; //Mensagem de feedback de vitória
	
	TRISC=0x01; //Configurações da board e processor
	TRISD=0x00;
	TRISE=0x00;
	ADCON1=0x0F;
	TRISA|=0x20;
	TRISB=0x3F;
	
	lcd_init(); //Inicia o LCD
	lcd_cmd(L_CLR); //Limpa o LCD
	lcd_cmd(L_L1); //Muda para a primeira linha
	lcd_str("Pressione RB1"); //Escreve no LCD
	lcd_cmd(L_L2);//Muda para a segunda linha
	lcd_str("Para comecar!"); //Escreve no LCD
	while(PORTBbits.RB1); //Espera até o jogador iniciar, apertando RB1
	int direction; // Direção da Snake
	char field[N][M+1]; // Matriz com cada posição do display
	Snake s;
	while (1){
		startSnake(&s);
		print(&s, field); //Transforma o estado do jogo em duas frases
		lcd_cmd(L_CLR);		// a serem exibidas no lcd
		lcd_cmd(L_L1); 
		lcd_str(field[0]);
		lcd_cmd(L_L2);
		lcd_str(field[1]);
		while(!end(&s)){ //Espera nova movimentações até o jogo terminar
			while((direction = (PORTBbits.RB0 << 0) + (PORTBbits.RB1 << 1) + (PORTBbits.RB2 << 2))
			      ==  ((1 << 3) - 1)); // 1000 - 1 == 111
			/*
			* O while continua até um dos sinais ser negado
			* Quando um dos botões for acionado, um número único 
			* é gerado e armazenado em direction, tornando possível
			* reconhecer o movimento escolhido pelo jogador.
			* Neste momento, o while termina.
			*/            
			if (direction == 6) //110 Bit do RB0 está zerado
				direction = 0;
			else if (direction == 5) //101 Bit do RB1 está zerado
				direction = 1;
			else if (direction == 3) //011 Bit do RB2 está zerado
				direction = 2;
			move(&s, direction); //Realiza a movimentação da cobra de acordo com o botão
			print(&s, field);	//precionado. E atualiza a tela para o jogador.
			lcd_cmd(L_CLR);
			lcd_cmd(L_L1);
			lcd_str(field[0]);
			lcd_cmd(L_L2);
			lcd_str(field[1]);
		}
		if (won(&s)){	//Quando a cobra preencher todo o tabuleiro
			lcd_cmd(L_CLR);
			lcd_cmd(L_L1);
			lcd_str("Parabens!");
			lcd_cmd(L_L2);
			lcd_str("Venceu. RB1");
		}
		else{		//Quando a cobra se intersectar
			lcd_cmd(L_CLR);
			lcd_cmd(L_L1);
			int pts = points(&s); //Recebe os pontos (Quantidade de comidas) recolhidos
			message[0] = '0' + pts/10; //Fatorando os pontos na base 10 para exibir no LCD
			message[1] = '0' + pts%10; //A quantidade máxima de pontos é 32. (Apenas 2 dígitos)
			lcd_str(message);
			lcd_cmd(L_L2);
			lcd_str("Tente novamente");
		}
		while(PORTBbits.RB1); //Aguarda comando do usuário para reiniciar o jogo
	}
}
