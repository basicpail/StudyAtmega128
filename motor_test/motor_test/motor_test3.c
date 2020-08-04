/*
 * motor_test3.c
 *
 * Created: 2020-06-18 오전 10:05:04
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

unsigned char step[8] = {0x90,0x80,0xc0,0x40,0x60,0x20,0x30,0x10};
	
int main(void)
{
	unsigned char i, t =0;
	
	DDRB = 0x20;
	DDRD = 0xf0;
	PORTB &= ~0x20;
	while(1)
	{
		for(i=0;i<24;i++)
		{
			PORTD = step[t];
			t++;
			if(t>7) t=0;
			_delay_ms(10);
		}
		_delay_ms(500);
	}
}