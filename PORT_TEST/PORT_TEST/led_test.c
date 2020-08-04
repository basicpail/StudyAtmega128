/*
 * led_test.c
 *
 * Created: 2020-06-12 오후 3:42:36
 *  Author: PKNU
 */ 
//#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

	
    while (1) 
    {
		DDRA = 0x03;
		PORTA= 0x03;
		_delay_ms(1000);
		
		PORTA = 0x0f;
		_delay_ms(1000);
		
		DDRA = 0x0C;
		PORTA = 0x0F;
		_delay_ms(1000);
		
		PORTA = 0x00;
		_delay_ms(1000);
    }
	return 0;
}

