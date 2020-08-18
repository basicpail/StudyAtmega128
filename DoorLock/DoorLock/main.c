/*
 * DoorLock.c
 *
 * Created: 2020-08-14 오후 3:12:26
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"
#define Keypadin PIND
#include <string.h>

int key=1;
int pw_length = 6;
int cmp;

int m_cnt = 0 ;
unsigned char input_start = 1;
unsigned char old_input_start;

Byte password[6]="111111";
Byte Ispassword[6]={0,};
Byte blank[6];

int arr_length=0;
unsigned char RX_data[16];

Byte KeyPad()
{
	PORTD = 0xFE; // 1111 1110
	_delay_ms(10);
	if((Keypadin & 0xF0) == 0xE0) {
		while((Keypadin & 0xF0)==0xE0);
		key=0; return '1';
	} // 1110 1110 & 1111 0000 = 1110 0000
	if((Keypadin & 0xF0) == 0xD0) {
		while((Keypadin & 0xF0)==0xD0);
		key=0; return '4';
	} //1101 1111
	if((Keypadin & 0xF0) == 0xB0) {
		while((Keypadin & 0xF0)==0xB0);
		key=0; return '7';
	} // 1011 1111
	if((Keypadin & 0xF0) == 0x70)
	{
		while((Keypadin & 0xF0)==0x70);
		old_input_start = !input_start;
		input_start = old_input_start;
		return 0;
	}
	
	PORTD = 0xFD; // 1111 1101
	_delay_ms(10);
	if((Keypadin & 0xF0) == 0xE0) {while((Keypadin & 0xF0)==0xE0);key=0; return '2';}
	if((Keypadin & 0xF0) == 0xD0) {while((Keypadin & 0xF0)==0xD0);key=0; return '5';}
	if((Keypadin & 0xF0) == 0xB0) {while((Keypadin & 0xF0)==0xB0);key=0; return '8';}
	if((Keypadin & 0xF0) == 0x70) {while((Keypadin & 0xF0)==0x70);key=0; return '0';}
	
	PORTD = 0xFB; // 1111 1011
	_delay_ms(10);
	if((Keypadin & 0xF0) == 0xE0) {while((Keypadin & 0xF0)==0xE0);key=0; return '3';}
	if((Keypadin & 0xF0) == 0xD0) {while((Keypadin & 0xF0)==0xD0);key=0; return '6';}
	if((Keypadin & 0xF0) == 0xB0) {while((Keypadin & 0xF0)==0xB0);key=0; return '9';}
	if((Keypadin & 0xF0) == 0x70) {while((Keypadin & 0xF0)==0x70);key=0; return '#';}
	
	return 0;
}

void putch(unsigned char *data)
{
	static int i=0;
	while((UCSR0A & 0x20) == 0);
	unsigned char data2 = *(data+(i++));
	UDR0 = data2;
	UCSR0A |= 0x20;
}

unsigned char getch()
{
	unsigned char data;
	//while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0x80;
	arr_length++;
	return data;
}

int main(void)
{
	DDRD = 0x0F; //keypad
	DDRA = 0xFF; //lcd

	LcdInit_4bit();
	
	Byte str[] ="Put your PW!";
	
	//시리얼
	DDRE = 0xfe;
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	
	//모터
	DDRC = 0xFF;
	
	
	Lcd_Pos(0,0);
	Lcd_STR(str);
	
	while (1)
	{
		Lcd_Pos(0,0);
		Lcd_STR(str);
		Lcd_Pos(1,0);
		
		Ispassword[arr_length] = KeyPad(); //arr_length,arr_cnt
		
		if(key==0 && old_input_start==0)
		{
			_delay_ms(10);
			Put_into_arr();
		}
		
		if(!((UCSR0A & 0x80)==0))
		{
			Ispassword[arr_length] = getch();
			putch(Ispassword);
			Lcd_STR(Ispassword);
		}
		
		if(key==1 && old_input_start==1 )
		{
			_delay_ms(10);
			
			PORTC = 0xFE;
			_delay_ms(100);
			PORTC = 0xFF; //디버깅
			
			if(CmpPW()==3)
			{
				M_start();
				old_input_start=0;
			}
		}
	}
}

void M_start(void)
{
	PORTC = 0xFE;
	Lcd_STR("Door is Open!!");
	_delay_ms(3000);
	PORTC = 0xFF;
	Lcd_Clear();
	m_cnt=0;
	arr_length=0;
}
void Put_into_arr(void)
{
	arr_length++;

	PORTC = 0xFE; //디버깅용
	_delay_ms(100);
	PORTC = 0xFF;
	
	if(arr_length==pw_length) // 지정된 암호길이
	{
		for (int x=0;x<pw_length;x++)
		{
			if(password[x]==Ispassword[x]){m_cnt++;}
		}
	}

	if(arr_length>=10) //10은 임의의 길이
	{
		for(int i=0;i<10;i++)
		{
			Ispassword[i]="";
		}
		arr_length=0;
	}
	Lcd_STR(Ispassword);
	key=1;
}

int ComparePassword()
{
	cmp = strcmp(Ispassword,password);
	if(cmp==1)
	{
		PORTC = 0xFE; //디버깅용
		_delay_ms(1000);
		PORTC = 0xFF;
	}
	else if (cmp==-1)
	{
		PORTC = 0xFE; //디버깅용
		_delay_ms(2000);
		PORTC = 0xFF;
	}
	return cmp;
}

int CmpPW()
{
	for (int x=0;x<pw_length;x++)
	{
		if(password[x]==Ispassword[x]){m_cnt++;}
	}
	if(m_cnt==pw_length)
	{
		for (int x=0;x<pw_length;x++)
		{
			Ispassword[x]="";
		}
		return 3;
	}
}