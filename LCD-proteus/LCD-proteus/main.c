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

int key=1;

Byte KeyPad()
{
	PORTD = 0xFE; // 1111 1110
	_delay_ms(200);
	if((Keypadin & 0xF0) == 0xE0) {key=0; return '1';} // 1110 1110 & 1111 0000 = 1110 0000
	if((Keypadin & 0xF0) == 0xD0) {key=0; return '4';} //1101 1111
	if((Keypadin & 0xF0) == 0xB0) {key=0; return '7';} // 1011 1111
	if((Keypadin & 0xF0) == 0x70) {key=0; return '*';}
	
	PORTD = 0xFD; // 1111 1101
	_delay_ms(200);
	if((Keypadin & 0xF0) == 0xE0) {key=0; return 2;}
	if((Keypadin & 0xF0) == 0xD0) {key=0; return 5;}
	if((Keypadin & 0xF0) == 0xB0) {key=0; return 8;}
	if((Keypadin & 0xF0) == 0x70) {key=0; return 0;}
	
	PORTD = 0xFB; // 1111 1011
	_delay_ms(200);
	if((Keypadin & 0xF0) == 0xE0) {key=0; return 3;}
	if((Keypadin & 0xF0) == 0xD0) {key=0; return 6;}
	if((Keypadin & 0xF0) == 0xB0) {key=0; return 9;}
	if((Keypadin & 0xF0) == 0x70) {key=0; return '#';}
}

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
	DDRD = 0x0F;
	Byte str[] ="Iot BigData";
	Byte str1[] ="Hello!!!!!";
	Byte str2[1]=" ";
	DDRA = 0xFF;
	LcdInit_4bit();
	
	Byte number[16]="";
	int arr_cnt = 0;

	
	DDRE = 0xfe;
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	
	Byte i;
    while (1) 
    {
		number[arr_cnt]=(Byte)KeyPad();
		_delay_ms(10);
		if(key==0)
		{
			_delay_ms(50);
			arr_cnt++;
			key = 1;
		}
		Lcd_Pos(0,0);
		Lcd_STR(str1);

    }
}

