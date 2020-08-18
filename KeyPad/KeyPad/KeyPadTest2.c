/*
 * KeyPadTest2.c
 *
 * Created: 2020-08-01 오후 3:05:34
 *  Author: PKNU
 */ 
#define F_CPU 7372800
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>


#define Keypadin PIND

int key=1;
int oldkey=0;

unsigned char password[4]={1,1,1,1};
unsigned char Ispassword[4]={0};
int arr_cnt = 0;
int m_cnt = 0 ;
unsigned char input_start = 1;
unsigned char old_input_start=1;

unsigned char KeyPad()
{
	PORTD = 0xFE; // 1111 1110
	_delay_ms(80);
	if((Keypadin & 0xF0) == 0xE0) {key=0; return 1;} // 1110 1110 & 1111 0000 = 1110 0000
	if((Keypadin & 0xF0) == 0xD0) {key=0; return 4;} //1101 1111
	if((Keypadin & 0xF0) == 0xB0) {key=0; return 7;} // 1011 1111
	if((Keypadin & 0xF0) == 0x70) 
	{
		old_input_start = !input_start;
		input_start = old_input_start;
		return '*';
	}
	
	PORTD = 0xFD; // 1111 1101
	_delay_ms(80);
	if((Keypadin & 0xF0) == 0xE0) {key=0; return 2;}
	if((Keypadin & 0xF0) == 0xD0) {key=0; return 5;}
	if((Keypadin & 0xF0) == 0xB0) {key=0; return 8;}
	if((Keypadin & 0xF0) == 0x70) {key=0; return 0;}
	
	PORTD = 0xFB; // 1111 1011
	_delay_ms(80);
	if((Keypadin & 0xF0) == 0xE0) {key=0; return 3;}
	if((Keypadin & 0xF0) == 0xD0) {key=0; return 6;}
	if((Keypadin & 0xF0) == 0xB0) {key=0; return 9;}
	if((Keypadin & 0xF0) == 0x70) {key=0; return '#';}
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
	while(1)
	{
		Ispassword[arr_cnt]=KeyPad(); // 입력된 키패드를 배열에 대입하고 배열순서 증가
		
		if(key==0 && old_input_start==0) //다이얼을 누르면 if 안으로 들어옴
		{
			_delay_ms(10);
			ComparePassword();
		}
		if(m_cnt==4 && old_input_start==1)
		{
			_delay_ms(10);
			M_start();
		}
	}
}
void M_start(void)
{
	PORTF = 0x00;
	_delay_ms(2000);
	PORTF = 0xFF;
	m_cnt=0;
	arr_cnt=0;
}
void ComparePassword(void)
{
	if(arr_cnt==3) // 지정된 암호길이
	{
		for (int x=0;x<4;x++)
		{
			if(password[x]==Ispassword[x]){m_cnt++;}
		}
		strcmp
	}
	arr_cnt++;
	PORTC = arr_cnt;//확인
	_delay_ms(100);
	
	key=1;
}