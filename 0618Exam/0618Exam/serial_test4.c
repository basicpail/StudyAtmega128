/*
 * serial_test4.c
 *
 * Created: 2020-06-17 오후 5:03:23
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int Do[10]={261,293,329,349,391,440,493,523};

unsigned char scale = 0;
	
void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);
	
	UDR0 = data;
	UCSR0A |= 0x20;
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

int main(void)
{
	//unsigned char piano=0;
		
	//DDRB = 0x80;
		
	TCCR3A |= 0x00;
	TCCR3B |= 0x19;
	TCCR3C = 0x00;
	TCNT3 = 0x0000;


	DDRE = 0x08;
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 0x03;

	while(1)
	{
		scale = getch();
		ICR3 = 7273800/Do[scale-0x31]/30;
		TCCR3A = 0x40;
		_delay_ms(200);
		TCCR3A = 0x00;
	}
}