/*
 * Basic_MCU.c
 *
 * Created: 2020-08-08 오전 9:28:45
 * Author : PKNU
 */ 
#define F_CPU 7372800

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC = 0xFF;
	DDRE = 0x00;
	PORTE = 0x0F;
	
    while (1) 
    {
		PORTC = 0xF0;
		if(PINE == 0xFE) PORTC = 0xFE; //1110 0000
    }
}

