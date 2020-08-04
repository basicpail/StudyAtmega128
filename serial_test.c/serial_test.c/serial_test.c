/*
 * serial_test.c.c
 *
 * Created: 2020-06-17 오후 3:05:35
 * Author : PKNU
 */ 

#include <avr/io.h>

void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= (1<<UDRE0); //0x20;
}

int main(void)
{
	unsigned char text[] = "Hello! \r\n";
	unsigned char i=0;
	
	DDRE = 0xfe;
	UCSR0A = 0x00;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //0x18;
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); //0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 0x03; //115,200
	
    while (text[i] != '\0') 
    {
		putch(text[i++]);
    }
}

