/*
 * Basic_MCU.c
 *
 * Created: 2020-08-08 오전 9:28:45
 * Author : PKNU
 */ 
#define F_CPU 7372800

#include <avr/io.h>
#include <util/delay.h>

unsigned char cnt=0;
unsigned char val;

int main(void)
{
	DDRC = 0xFF;
	DDRE = 0xF0; //사용하지 않는 비트는 출력으로 설정
	
	PORTC = 0xFF;
	PORTE = 0x0F; //내부풀업 사용 내부풀업을 사용하지 않으면 사용하지 않는 핀들이 플로팅상태가 되어 입력을 정확하게 읽을수가 없다.
    while (1) 
    {
		if(PINE==0x0E ) //0000 1110
		{
			leftShift();
		}
		else if(PINE == 0x0D) //0000 1101
		{
			rightShift();
		}
		else if(PINE == 0x0B)
		{
			returnLED();
		}
		else if(PINE == 0x07) //0000 0111
		{
			TurnOFF();
		}
    }
}
void leftShift(void)
{
	if(cnt==0)
	{
		PORTC = 0xFE;
		_delay_ms(200);
	}
	else if(cnt==1)
	{
		PORTC = 0xFD; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==2)
	{
		PORTC = 0xFB; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==3)
	{
		PORTC = 0xF7; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==4)
	{
		PORTC = 0xEF; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==5)
	{
		PORTC = 0xDF; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==6)
	{
		PORTC = 0xBF; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==7)
	{
		PORTC = 0x7F; //1111 0010
		_delay_ms(200);
	}
	cnt++;
	if(cnt==8) cnt=0;
}
void rightShift(void)
{
	cnt--;
	if(cnt<0) cnt=7;
	
	if(cnt==0)
	{
		PORTC = 0xFE;
		_delay_ms(200);
	}
	else if(cnt==1)
	{
		PORTC = 0xFD; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==2)
	{
		PORTC = 0xFB; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==3)
	{
		PORTC = 0xF7; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==4)
	{
		PORTC = 0xEF; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==5)
	{
		PORTC = 0xDF; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==6)
	{
		PORTC = 0xBF; //1111 0010
		_delay_ms(200);
	}
	else if(cnt==7)
	{
		PORTC = 0x7F; //1111 0010
		_delay_ms(200);
	}
}
void returnLED(void)
{
	if(PORTC != 0xFF)
	{
		val = PORTC;
		for(unsigned char i=0;PORTC>0x7F;i++)
		{
			PORTC = (PORTC<<1)|0x01; //1111 1110 -> 1111 1101 | 1
			_delay_ms(100);
		}
		for(unsigned char i=0;PORTC<val;i--)
		{
			PORTC = (PORTC>>1)|0x80; //1111 1110 -> 1111 1101 | 1
			_delay_ms(100);
		}
	}
}
void TurnOFF(void)
{
	PORTC=0xFF;
	_delay_ms(50);
}