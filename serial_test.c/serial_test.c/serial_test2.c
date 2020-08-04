/*
 * serial_test2.c
 *
 * Created: 2020-06-17 오후 3:33:29
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int Do[10]={1046,1046,1174,1318,1396,1567,1760,1975,2093};
volatile unsigned char sound_flag = 1;

int scale=0;

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
	unsigned char piano=0;
		
	DDRB = 0x80;
		
	TCCR1A |= 0x0A;// (1<<COM1C1)|(1<<WGM11);			
	TCCR1B |= 0x19;//(1<<WGM12)|(1<<WGM12)|(1<<CS10);
	TCCR1C = 0x00;
	TCNT1 = 0x0000;

	DDRE = 0xfe;
	
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 0x03;

	while(1)
	{
		scale = getch();
		putch(getch());
		//putch(scale);


		
	}
}

void buz(int x){
	ICR1 = 7273800/Do[x];
	OCR1C = ICR1/10;
	//piano++;
	//if(8<piano) piano = 0;
	_delay_ms(1000);
}