/*
 * led_test.c
 *
 * Created: 2020-06-16 오후 6:48:14
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

int main()
{
	//DDRA =0x00;
	//PORTA = 0xFF;
	
	Byte str[] = "hello";
	LcdInit_4bit();
			Lcd_Pos(0,0);
			Lcd_STR(str);
	while(1)
	{

	}
}