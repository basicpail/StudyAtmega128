

/*
 * CFile2.c
 *
 * Created: 2020-06-15 오후 2:15:19
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char time_stop = 0;

SIGNAL(INT0_vect)
{
	cli();
	if(time_stop == 0)
	{
		time_stop = 1;
	}
	else
	{
		time_stop = 0;
	}
	sei();
}

int main(void)
{
		unsigned char led_data = 0x01;
		DDRA = 0xFF;
		DDRD = 0x00;
		EICRA = 0x03;
		EIMSK = 0x10;
		EIFR = 0X10;
		EIMSK = 0x01;
		sei();
		while(1)
		{
			PORTA = led_data;
			if(time_stop == 0)
			{
				if(led_data == 0x80)
					led_data= 0x01;
				else
					led_data <<= 1;
			}
			_delay_ms(100);
		}
}