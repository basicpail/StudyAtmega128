/*
 * LCD-proteus.c
 *
 * Created: 2020-08-08 오후 2:14:24
 * Author : PKNU
 */ 
#define F_CPU 7372800

#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"
#define Keypadin PIND

int arr_length=0;


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
	arr_length++;
	return data;
}

int main(void)
{
	DDRA = 0xFF; //lcd

	LcdInit_4bit();
	
	Byte str[] ="Hello!!!!!";

	Byte RX_data[16]="";
	
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
		RX_data[arr_length] = getch();
		//putch(RX_data);
		//Lcd_CHAR(RX_data);
		Lcd_STR(RX_data);
    }
}
