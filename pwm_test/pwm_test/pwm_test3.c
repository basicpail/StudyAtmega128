/*
 * pwm_test3.c
 *
 * Created: 2020-06-17 오후 12:18:41
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

unsigned int Do[8]={523,587,659,698,783,880,987,1046};

int main()
{
	unsigned char piano=0;
	
	DDRB = 0x80;
	
	TCCR1A |= 0x0A;// (1<<COM1C1)|(1<<WGM11);
	TCCR1B |= 0x19;//(1<<WGM12)|(1<<WGM12)|(1<<CS10);
	TCCR1C = 0x00;
	TCNT1 = 0x0000;
	while(1)
	{
		ICR1 = 7273800/Do[piano];
		OCR1C = ICR1/5;
		piano++;
		if(8<piano) piano = 0;
		_delay_ms(1000);
	}
}