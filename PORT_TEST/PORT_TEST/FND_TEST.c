﻿/*
 * FND_TEST.c
 *
 * Created: 2020-06-15 오전 11:03:08
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char FND_DATA_TBL[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,
									0x67,0x77,0x7c,0x39,0x5e,0x79,0x71,0x08,0x80};
	DDRA = 0xff;
	unsigned char cnt =0;
	
	while(1)
	{
		PORTA = FND_DATA_TBL[cnt];
		cnt++;
		if(cnt>17) cnt = 0;
		_delay_ms(500);
	}
}