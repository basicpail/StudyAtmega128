/*
 * pwm_test2.c
 *
 * Created: 2020-06-17 오전 11:38:09
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int light = 0;
volatile unsigned char light_flag = 1;

int main(void)
{
	DDRB = 0xf0;
	DDRD = 0x00;
	DDRE = 0x00;
	
	TCCR2 |= (1<<WGM20)|(1<<COM21)|(1<<CS21); //0x62;
	TCNT2 = 0x00;
	EICRA = 0xff;
	EICRB = 0xff;
	EIMSK = 0xff;
	EIFR = 0xff;
	sei();
	while(1)
	{
		if(light_flag)
		{
			OCR2 =light;
			light_flag = 0;
			
		}
	}
} 
SIGNAL(INT0_vect)
{
	cli();
	light = 0;
	light_flag = 1;
	sei();
}
SIGNAL(INT1_vect)
{
	cli();
	light -= 21;
	if(light <0)
	light = 0;
	light_flag = 1;
	sei();
}
SIGNAL(INT2_vect)
{
	cli();
	light -= 41;
	if(light <0)
	light = 0;
	light_flag = 1;
	sei();
}
SIGNAL(INT3_vect)
{
	cli();
	light += 21;
	if(light >255)
	light = 255;
	light_flag = 1;
	sei();
}
SIGNAL(INT4_vect)
{
	cli();
	light += 41;
	if(light >255)
	light = 255;
	light_flag = 1;
	sei();
}
SIGNAL(INT5_vect)
{
	cli();
	light = 255;
	light_flag = 1;
	sei();
}