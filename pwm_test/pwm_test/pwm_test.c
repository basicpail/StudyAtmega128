/*
 * pwm_test.c
 *
 * Created: 2020-06-17 오전 11:21:55
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char light = 0;
	DDRB = 0x10;
		
	TCCR0 |= (1 <<WGM00)|(1<<COM01)|(1<<COM00)|(1<<CS02)|(1<<CS01)|(1<<CS00); //0x77;
	TCNT0 = 0x00;	
    while (1) 
    {
		for(light = 0; light<255;light++)
		{
			OCR0 = light;
			_delay_ms(10);
		}
		for(light=255;0<light;light--)
		{
			OCR0 = light;
			_delay_ms(10);
		}

    }
}

