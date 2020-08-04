/*
 * _16bitTC_test2.c
 *
 * Created: 2020-06-16 오후 12:17:17
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char led_data = 0x00;

int main(void)
{
	DDRA = 0xff;
	
	TCCR3A = 0x00;
	TCCR3B = (1<<CS12)|(1<<CS10); //0x05;
	
	TCNT3 = 58336; // 65536 - 7200
	ETIMSK = (1<<TOIE3);
	ETIFR |= 1<<TOV3;
	
	sei();
	while(1)
	{
		PORTA = led_data;
	}
	return 0;
}

ISR(TIMER3_OVF_vect)
{
	cli();
	
	TCNT3 = 58336;
	led_data++;
	
	if(led_data>0xFF)
		led_data = 0;
	sei();
}