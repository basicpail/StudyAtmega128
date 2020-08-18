/*
 * Serial_proteus.c
 *
 * Created: 2020-08-08 오후 4:41:43
 * Author : PKNU
 */ 

#define F_CPU 7372800

#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"
#define Keypadin PIND

int arr_length=0;
unsigned char RX_data[16];

void putch(unsigned char *data)
{
	static int i=0;
	while((UCSR0A & 0x20) == 0);
	unsigned char data2 = *(data+(i++));
	UDR0 = data2;
	UCSR0A |= 0x20;
}

unsigned char getch()
{
	unsigned char data;
	//while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0x80;
	arr_length++;
	return data;
}

int main(void)
{
	DDRA = 0xFF; //lcd

	LcdInit_4bit();
	
	Byte str[] ="Hello!!!!!";
	
	//시리얼
	DDRE = 0xfe;
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	
    while (1) 
    {
		

		Lcd_Pos(0,0);
		Lcd_STR(str);
		Lcd_Pos(1,0);
		
		if(!((UCSR0A & 0x80)==0))
		{
			RX_data[arr_length] = getch();
			putch(RX_data);
		}
		
		//Lcd_CHAR(getch());
		Lcd_STR(RX_data);
    }
}
