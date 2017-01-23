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
    char message[16] = "   pontos! RB1";

    
	TRISC=0x01;
	TRISD=0x00;
	TRISE=0x00;
    
  
    
    ADCON1=0x0F;
    TRISA|=0x20;

    TRISB=0x3F;
    
	lcd_init();
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Pressione RB1");
    lcd_cmd(L_L2);
    lcd_str("Para comecar!");
    while(PORTBbits.RB1);
    int direction;
    char field[N][M+1];
    Snake s;
    while (1){    
        startSnake(&s);
        print(&s, field);
        lcd_cmd(L_CLR);
        lcd_cmd(L_L1);
        lcd_str(field[0]);
        lcd_cmd(L_L2);
        lcd_str(field[1]);
        while(!end(&s)){
            while((direction = (PORTBbits.RB0 << 0) + (PORTBbits.RB1 << 1) + (PORTBbits.RB2 << 2))
                    ==  ((1 << 3) - 1));
            
            if (direction == 6) //110
                direction = 0;
            else if (direction == 5) //101
                direction = 1;
            else if (direction == 3) //011
                direction = 2;
            
            move(&s, direction);
            print(&s, field);
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1);
            lcd_str(field[0]);
            lcd_cmd(L_L2);
            lcd_str(field[1]);
        }
        if (won(&s)){
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1);
            lcd_str("Parabens!");
            lcd_cmd(L_L2);
            lcd_str("Venceu. RB1");
        }
        else{
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1);
            int pts = points(&s);
            message[0] = '0' + pts/10;
            message[1] = '0' + pts%10;
            lcd_str(message);
            lcd_cmd(L_L2);
            lcd_str("Tente novamente");
        }
        while(PORTBbits.RB1);
    }
}