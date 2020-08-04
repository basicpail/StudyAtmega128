/*
 * Timer_test2.c
 *
 * Created: 2020-06-15 오후 5:08:15
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char led_data = 0x01;
unsigned char timer2cnt = 0, shift_flag = 0;

SIGNAL(TIMER2_OVF_vect);

int main(void)
{
	DDRA = 0xff;
	
	TCCR2 = 0x05;
	
	TCNT0 = 184;
	TIMSK = 0x40;
	TIFR |= 1<<TOV2;
	
	sei();
	while(1)
	{
		PORTA = led_data;
	}
	return 0;
}
SIGNAL(TIMER2_OVF_vect)
{
	cli();
	TCNT2 =184;
	timer2cnt++;
	
	if(timer2cnt == 50)
	{
		if(shift_flag == 0)
		{
			led_data <<= 1;
			if(led_data == 0x80)
				shift_flag = 1;
		}
		else
		{
			led_data >>= 1;
			if(led_data == 0x01)
				shift_flag = 0;
		}
		timer2cnt = 0;
	}
	sei();
}