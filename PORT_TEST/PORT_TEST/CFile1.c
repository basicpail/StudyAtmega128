/*
 * CFile1.c
 *
 * Created: 2020-06-15 오전 9:42:50
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xFF;
	while(1)
	{
		PORTA = 0x01;
		_delay_ms(1000);
		PORTA = 0x02;
		_delay_ms(1000);
		//PORTA = 0x03;
		//_delay_ms(1000);
		PORTA = 0X04;
		_delay_ms(1000);
		PORTA = 0X08;
		_delay_ms(1000);
		PORTA = 16;
		_delay_ms(1000);
		PORTA = 32;
		_delay_ms(1000);
		PORTA = 64;
		_delay_ms(1000);
	}
	return 0;
}