/*
 * KeyPadTest2.c
 *
 * Created: 2020-08-01 오후 3:05:34
 *  Author: PKNU
 */ 
#define F_CPU 7372800
#include<avr/io.h>
#include<util/delay.h>

#define Keypadin PIND

int key=1;
int oldkey=0;

unsigned char KeyPad()
{
	PORTD = 0xFE; // 1111 1110
	_delay_ms(2);
	if((Keypadin & 0xF0) == 0xE0) // 1110 1111
	{key = 0; return 1;}
	if((Keypadin & 0xF0) == 0xD0) return 4; //1101 1111
	if((Keypadin & 0xF0) == 0xB0) return 7; // 1011 1111
	if((Keypadin & 0xF0) == 0x70) return '*';
	
	PORTD = 0xFD; // 1111 1101
	_delay_ms(2);
	if((Keypadin & 0xF0) == 0xE0) return 2;
	if((Keypadin & 0xF0) == 0xD0) return 5;
	if((Keypadin & 0xF0) == 0xB0) return 8;
	if((Keypadin & 0xF0) == 0x70) return 0;
	
	PORTD = 0xFB; // 1111 1011
	_delay_ms(2);
	if((Keypadin & 0xF0) == 0xE0) return 3;
	if((Keypadin & 0xF0) == 0xD0) return 6;
	if((Keypadin & 0xF0) == 0xB0) return 9;
	if((Keypadin & 0xF0) == 0x70) return '#';
}

void Output()
{
	if(KeyPad() == 1 )
	{
		PORTC = 0xFE; //1111 1110
		_delay_ms(100);
		PORTC = 0xFF;
	}
	if(KeyPad() == 2 )
	{
		PORTC = 0xFD; //1111 1101
		_delay_ms(100);
		PORTC = 0xFF;
	}
	if(KeyPad() == 3 )
	{
		PORTC = 0xFC; //1111 1100
		_delay_ms(100);
		PORTC = 0xFF;
	}
	if(KeyPad() == 4 )
	{
		PORTC = 0xFB; //1111 1011
		_delay_ms(100);
		PORTC = 0xFF;
	}
	if(KeyPad() == 5 )
	{
		PORTC = 0xFA; //1111 1010
		_delay_ms(100);
		PORTC = 0xFF;
	}
	if(KeyPad() == 6 )
	{
		PORTC = 0xF9; //1111 1001
		_delay_ms(100);
		PORTC = 0xFF;
	}
	if(KeyPad() == 7 )
	{
		PORTC = 0xF8; //1111 1000
		_delay_ms(100);
		PORTC = 0xFF;
	}
	if(KeyPad() == 8 )
	{
		PORTC = 0xF7; //1111 0111
		_delay_ms(100);
		PORTC = 0xFF;
	}
	if(KeyPad() == 9 )
	{
		PORTC = 0xF6; //1111 0110
		_delay_ms(100);
		PORTC = 0xFF;
	}
}

int main()
{
	DDRD = 0x0F;
	DDRC = 0x0F;
	DDRF = 0xFF;
	
	PORTC = 0xFF;
	PORTF = 0xFF;
	
	unsigned char password[4]={1,1,1,1};
	unsigned char Ispassword[4]={0};
	int i = 0;
	int y = 0 ;
	
	while(1)
	{
		Ispassword[i]=KeyPad(); // 입력된 키패드를 배열에 대입하고 배열순서 증가
		
		if(key==0) //다이얼을 누르면 if문으로 들어옴
		{
			
			if(i==3) // 지정된 암호길이
			{
				for (int x=0;x<4;x++)
				{
					if(password[x]==Ispassword[x]){y++;}
				}
			}
			
			i++;
			PORTC = i;//확인
			_delay_ms(100);
		
			key=1;
		}
		
		if(y==4)
		{
			PORTF = 0x00;
			_delay_ms(1000);
		}
	}
}