/*
 * pwm_test4.c
 *
 * Created: 2020-06-17 오후 1:51:04
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DO 261.63
#define RE 293.66
#define MI 329.63
#define FA 349.23
#define SOL 391.99
#define RA 440.0
#define SI 493.88


unsigned int Do[10]={1046,1046,1174,1318,1396,1567,1760,1975,2093};

volatile unsigned char sound_flag = 1;

int main(void)
{
	DDRE = 0x08;
	DDRD = 0x00;
	
	TCCR3A = 0x00;
	TCCR3B = 0x19;
	
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	EICRA = 0xff;
	EICRB = 0xff;
	EIMSK = 0xFF;
	EIFR = 0xFF;
	sei();
	while(1)
	{
		if(sound_flag)
		{
			_delay_ms(500);
			TCCR3A = 0x00;
			sound_flag = 0;
		}
	}
}
SIGNAL(INT0_vect)
{
	cli();
	ICR3 = 7273800/Do[0]/10;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}
SIGNAL(INT1_vect)
{
	cli();
	ICR3 = 7273800/Do[1]/10;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}
SIGNAL(INT2_vect)
{
	cli();
	ICR3 = 7273800/Do[2]/10;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}
SIGNAL(INT3_vect)
{
	cli();
	ICR3 = 7273800/Do[3]/10;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}
