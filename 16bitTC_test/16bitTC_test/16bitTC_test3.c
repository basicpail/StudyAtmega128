/*
 * _16bitTC_test3.c
 *
 * Created: 2020-06-17 오전 10:02:01
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,
								0x67,0x77,0x7c,0x39,0x5e,0x79,0x71,0x08,0x80};
								
volatile unsigned char time_s = 0;
volatile unsigned char FND_flag=0, edge_flag = 0;

int main()
{
	DDRA = 0xff;
	DDRE = 0x00;
	
	TCCR3A = 0x00;
	TCCR3B = 0x45;
	EIMSK = 0x20;
	EIFR |= 1<<ICF3;
	
	sei();
	PORTA = FND_DATA_TBL[0];
	while(1)
	{
		if(FND_flag)
		{
			if(time_s > 15)
				time_s = 15;
				
			PORTA = FND_DATA_TBL[time_s];
			FND_flag = 0;
		}
	}
	return 0;
}

SIGNAL(TIMER3_CAPT_vect)
{	
	cli();
	
	unsigned int count_check;
	
	if(edge_flag == 0)
	{
		TCCR3B = 0x05;
		TCNT3 = 0;
		ICR3 = 0;
		edge_flag = 1;
	}
	else
	{
		TCCR3B = 0x45;
		count_check = ICR3;
		
		time_s = count_check/7200;
		
		FND_flag = 1;
		edge_flag = 0;
	}
	sei();
}