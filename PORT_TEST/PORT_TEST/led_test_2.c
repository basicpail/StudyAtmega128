/*
 * led_test_2.c
 *
 * Created: 2020-06-12 오후 4:24:02
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h.>

int main()
{
	DDRA = 0xff;
	unsigned char LED_data =0x00;
	while(1)
	{
		PORTA = LED_data;
		LED_data++;
		_delay_ms(100);
		if(LED_data > 0xff)
		{
			for(int i=LED_data;i<0;i--)
			{
				PORTA = LED_data;
				_delay_ms(100);
			}
		}
		
	}
}