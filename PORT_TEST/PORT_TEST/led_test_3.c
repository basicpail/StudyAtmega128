#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char LED_data = 0x01, i;
	DDRA = 0xff;
	while(1)
	{
		LED_data = 0x01;
		
		for(i=0; i<8; i++)
		{
			PORTA =LED_data;
			LED_data <<= 1;
			_delay_ms(100);
			
			if(LED_data == 0x80)
			{
				for(i=0;i<8;i++)
				{
					PORTA = LED_data;
					LED_data >>= 1;
					_delay_ms(100);
				}
			}
		}
	}
}