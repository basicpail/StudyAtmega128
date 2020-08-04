/*
 * SW_TEST2.c
 *
 * Created: 2020-06-15 오전 10:22:47
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char switch_flag = 0, switch_flag_pre = 0x00;
	
	DDRA = 0xFF;
	DDRD = 0x00;
	PORTA = 0x00;
	
	while(1)
	{
		switch_flag = PIND;
		
		if((switch_flag == 0x01) || (switch_flag == 0x02) || (switch_flag == 0x04) || (switch_flag == 0x08))
		{
			switch_flag_pre = switch_flag;
		}
		
		//PORTA ^= 0x0f;
		
		
		if(switch_flag_pre == 0x01)
		{
			PORTA = switch_flag_pre;
			_delay_ms(500);
		}
		else if(switch_flag_pre == 0x02)
		{
			PORTA = switch_flag_pre;
			_delay_ms(1000);
		}
		else if(switch_flag_pre == 0x04)
		{
			PORTA = switch_flag_pre;
			_delay_ms(1500);
		}
		else if(switch_flag_pre == 0x08)
		{
			PORTA = switch_flag_pre;
			_delay_ms(2000);
		}
		PORTA = 0x00;
		PIND = 0X00;
	}
	return 0;
}