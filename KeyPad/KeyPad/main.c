/*
 * KeyPad.c
 *
 * Created: 2020-08-01 오전 10:50:15
 * Author : PKNU
 */ 
#define F_CPU 7372800
#include<avr/io.h>
#include<util/delay.h>

int main()
{
	DDRB = 0xFE;
	PORTB = 0x0E; //0000 1110
	
	DDRE = 0x7F; // 0111 1111
	PORTE = 0x0F; 
	
	while(1)
	{
		if(PINB == 0x0E) //0000 1110
		{
			PORTB = 0xF0;
			_delay_ms(1000);
			PORTB = 0x0E;
		}
		
		if(PINE == 0x8F) //1000 1111 
		{
			PORTE = 0x00;
			_delay_ms(1000);
			PORTE = 0x0F;
		}
	}
}