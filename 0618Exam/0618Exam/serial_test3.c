/*
 * serial_test3.c
 *
 * Created: 2020-06-17 오후 4:07:44
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TX_flag = 0;
volatile char TX_data = 0;

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
	unsigned char text[] = "\r\nWelcom!!\r\n USART 0 Test Program.\r\n";
	
	unsigned char echo[] = "ECHO >> ";
	unsigned char i = 0;
	
	DDRE = 0xfe;
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	while(text[i] != '\0')
	{
		putch(text[i++]);
	}
	i = 0;
	while(echo[i]!='\0')
	{
		putch(echo[i++]);
	}
	while(1)
	{
		putch(getch());
	}
}