/*
 * Timer_test.c
 *
 * Created: 2020-06-15 오후 4:51:41
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char led_data = 0x00;
unsigned char timercnt = 0;
SIGNAL(TIMER0_OVF_vect);

int main(void)
{
	DDRA = 0xff;
	TCCR0 = 0x07;
	TCNT0 = 184;
	TIMSK = 0x01;
	TIFR |= 1<<TOV0;
	sei();
	while(1)
	{
		PORTA = led_data;
	}
	
}

SIGNAL(TIMER0_OVF_vect)
{
	cli();
	TCNT0 = 184;
	timercnt++;
	if(timercnt == 100)
	{
		led_data++;
		if(led_data> 0xff) led_data=0;
		timercnt = 0;
	}
	sei();
	
}