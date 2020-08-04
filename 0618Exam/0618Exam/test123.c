/*
 * test123.c
 *
 * Created: 2020-06-18 오후 1:15:36
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xff;
	while(1)
	{
		led();
	}
}

void led()
{
	
	unsigned char led_data = 0x01;

	for(int i=0;i<7;i++)
	{
		PORTA = led_data;
		led_data <<= 1;
		_delay_ms(1000);
	}
	for(int j=0;j<7;j++)
	{
		PORTA = led_data;
		led_data >>= 1;
		_delay_ms(1000);
	}
	
}