/*
 * SW_TEST.c
 *
 * Created: 2020-06-15 오전 10:08:18
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xff;
	DDRF = 0x00;
	
	while(1)
	{
		//PORTA = PINF;
		if(PINF == 0x01)
		{
			PORTA = 0x01;	
		}
		else if(PINF == 0x02)
		{
			PORTA = 0x02;
		}
	}
	return 0;
}