/*
 * Timer_test3.c
 *
 * Created: 2020-06-16 오전 9:23:13
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char led_data = 0x00;
unsigned int timer0cnt = 0;

ISR(TIMER0_OVF_vect);

int main(void)
{
	DDRA = 0xFF;
	
	TCCR0 = 0x06;
	TCNT0 = 184;
	TIMSK = 0x01;
	TIFR |= 1<<TOV0;
	sei();
	while(1)
	{
		PORTA = led_data;
	}
}

ISR(TIMER0_OVF_vect)
{
	cli();
	
	TCNT0 = 184;
	timer0cnt++;
	
	if(timer0cnt == 400)
	{
		led_data++;
		if(led_data>0xFF) led_data = 0;
		timer0cnt = 0;
	}
	sei();
}