/*
 * interrup_test3.c
 *
 * Created: 2020-06-15 오후 3:26:16
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char time_stop = 0;
	unsigned char cnt = 0;
int main(void)
{
	unsigned char FND_DATA_TBL[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,
									0x67,0x77,0x7c,0x39,0x5e,0x79,0x71,0x08,0x80};
	

	DDRA = 0xFF;
	DDRD = 0x00;
	
	EICRA = 0xff;
	EIMSK = 0x0f;
	EIFR = 0x0f;
	sei();
	
	while(1)
	{
		PORTA = FND_DATA_TBL[cnt];
		if(time_stop == 0)
		{
			cnt++;
			if(cnt>17) cnt = 0;
		}
		if(time_stop == 1)
		{
			cnt--;
			if(cnt <0) cnt = 16; 
		}
		_delay_ms(200);
	}
}

SIGNAL(INT0_vect)
{
	cli();
	
	time_stop = 1;
}
SIGNAL(INT1_vect)
{
	cli();
	time_stop = 0;
	sei();
}
SIGNAL(INT2_vect)
{
	cli();
	
	time_stop = 2;
	cnt = 0;
}