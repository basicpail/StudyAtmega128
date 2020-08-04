/*
 * interrupt_test2.c
 *
 * Created: 2020-06-15 오후 2:46:49
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char shift_flag = 1;

int main(void)
{
	unsigned char led_data = 0x01;
	
	DDRA = 0xff;
	DDRD = 0x00;
	
	EICRA = 0xCC;
	//EICRB = 0x03;
	
	EIMSK = 0x0A;
	EIFR = 0x0A;
	
	sei();
	while(1)
	{
		PORTA = led_data;
		if(shift_flag == 1)
		{
			if(led_data == 0x80) led_data = 0x01;
			else led_data <<= 1;
			//led_data++;
			//if(led_data == 0xff) continue;;
		}
		else if(shift_flag == 2)
		{
			if(led_data == 0x01) led_data = 0x80;
			else led_data >>= 1;
			//led_data--;
			//if(led_data == 0x00) continue;
		}
		_delay_ms(50);
	}
}

SIGNAL(INT1_vect)
{
	cli();
	shift_flag = 1;
	sei();
}
SIGNAL(INT3_vect)
{
	cli();
	shift_flag = 2;
	sei();
}