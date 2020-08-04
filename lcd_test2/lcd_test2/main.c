/*
 * led_test.c
 *
 * Created: 2020-06-16 오후 6:48:14
 *  Author: Sang-Geun, SONG
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

Byte **gugudan[10][11] = { 0, };
Byte* ptr;
Byte str[1];
int i,j;
int x,y; 

int main(void)
{
		DDRA = 0xff;
		PORTA = 0xff;
		DDRD = 0x00;
		LcdInit_4bit();
		
	while(1)
	{
		if(PIND == 0x01) calc(2);
		if(PIND == 0x02) calc(3);
		if(PIND == 0x04) calc(4);
		if(PIND == 0x08) calc(5);
		if(PIND == 0x10) calc(6);
		if(PIND == 0x20) calc(7);
		if(PIND == 0x40) calc(8);
		if(PIND == 0x80) calc(9);
	}
}
void calc(int x)
{
	i= x;
	str[0]=x+48;
	Lcd_Pos(1,0);
	Lcd_STR(str);
	Lcd_Pos(1,1);
	Lcd_STR("DAN");
	
	for (j = 1;j <= 9;j++)
	{
		ptr = (Byte *)malloc(sizeof(char) * 2);
		ptr[0] = ((i * j) / 10) + 48;
		ptr[1] = ((i * j) % 10) + 48;

		gugudan[i][j] = &ptr;
		Lcd_Pos(0,0);
		Lcd_STR(*gugudan[i][j]);
		_delay_ms(500);
		free(ptr);
	}
}