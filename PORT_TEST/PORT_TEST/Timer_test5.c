/*
 * Timer_test5.c
 *
 * Created: 2020-06-16 오전 10:22:06
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,
								0x67,0x77,0x7c,0x39,0x5e,0x79,0x71,0x08,0x80};
								
volatile unsigned char time_s = 0;
volatile unsigned char time_stop = 0;

unsigned char timer0cnt = 0;

int main(void)
{
	DDRA = 0xFF;
	DDRE = 0x00;
	
	TCCR2 |= (1<<CS22)|(1<<CS20); //0x05;
	OCR2 = 72;
	TIMSK |= (1<<OCIE2);
	TIFR |= (1<<OCF2);
	
	EICRB |= (1<<ISC41)|(1<<ISC40);
	EIMSK |= (1<<INT4);
	EIFR |= (1<<INTF4);
	
	sei();
	while(1)
	{
		PORTA = FND_DATA_TBL[time_s];
	}
	return 0;
}
ISR(TIMER2_COMP_vect)
{
	cli();
	OCR2 += 72;
	timer0cnt++;
	
	if(timer0cnt == 50)
	{
		if(time_stop == 0)
		{
			if(time_s >= 16)
				time_s = 0;
			else
				time_s++;
		}
		timer0cnt = 0;
	}
	sei();
}
ISR(INT4_vect)
{
	cli();
	
	if(time_stop== 0)
		time_stop = 1;
	else
		time_stop = 0;
	
	sei();
}