/*
 * AD_test.c
 *
 * Created: 2020-06-16 오후 4:57:32
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


int main(void)
{
	unsigned int addata = 0;
	
	DDRF = 0x02;
	PORTF = 0x02;
	
	PORTA = 0xff;
		
	LcdInit_4bit();
	
	ADMUX = 0x00;
	ADCSRA = 0x86;
	
	Byte str[] = "hi";

    while (1) 
    {
		ADCSRA |= 0x40;
		while((ADCSRA & 0x10) == 0x00);
		addata = ADC;
		Lcd_Pos(0,0);
		
		//Lcd_Data("Cds: ")
		//Lcd_CHAR((addata/1000)%10 + '0');
		//Lcd_STR((addata/100)%10 + '0');
		//Lcd_STR((addata/10)%10 + '0');
		//Lcd_STR((addata)%10 + '0');
		//Lcd_STR(addata);
		
		Lcd_STR(str);
		_delay_ms(500);
    }
}

