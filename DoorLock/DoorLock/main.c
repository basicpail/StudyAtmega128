/*
 * DoorLock.c
 *
 * Created: 2020-08-14 오후 3:12:26
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "Lcd.h"


#define Keypadin PIND
#define ModeSW PINB

int arr_length=0;
int key=1;
int pw_length=6;
int cmp;
int Terminal=0;
int Putch_int=0;
int m_cnt=0;

unsigned char input_start = 1;
unsigned char old_input_start;

Byte password[]="1111";
Byte Ispassword[];



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
	if((Keypadin & 0xF0) == 0x70)
	{
		while((Keypadin & 0xF0)==0x70);
		return 0;
	}
	
	return 0;
}

void putch(unsigned char *data)
{
	//static int i=0;
	while((UCSR0A & 0x20) == 0);
	unsigned char data2 = *(data+(Putch_int++));
	UDR0 = data2;
	UCSR0A |= 0x20;
}

void _putch(unsigned char data) //putch_str에 쓰기 위함
{
	while((UCSR0A & 0x20) == 0);
	
	UDR0 = data;
	UCSR0A |= 0x20;
}

unsigned char getch()
{
	unsigned char data;
	//while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0x80;
	//arr_length++;
	return data;
}

void putch_str(char *str)
{
	unsigned char i = 0;
	while(str[i] != '\0')
	{
		_putch(str[i++]);
	}
}

int main(void)
{
	DDRD = 0x0F; //keypad
	DDRA = 0xFF; //Lcd
	
	DDRB = 0xF6; //1111 0110 터미널

	LcdInit_4bit();
	
	Byte str[] ="Put your PW!";
	Byte str2[] ="\r\n****Terminal Mode****\r\nEnter your PW and press the 'x'\r\nTo change the PW, Press 'c'\r\n\0";
	Byte str3[] ="\r\n****KeyPad Mode****\r\n\0";
	Byte str4[] ="PW Change Mode";
	Byte str5[] ="Change Completed";
	
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
		
		if((ModeSW & 0xFF) == 0x08)  //0000 1000 터미널 모드
		{
			while((ModeSW & 0xFF)==0x08);
			PORTC = 0xFE; //디버깅용
			_delay_ms(100);
			PORTC = 0xFF;
			PW_Clear();
			putch_str(str2);
			Terminal = 1;
		}
		
		if((ModeSW & 0xFF) == 0x01)  //0000 0001 키패드로 복귀
		{
			while((ModeSW & 0xFF)==0x01);
			PORTC = 0xFE; //디버깅용
			_delay_ms(100);
			PORTC = 0xFF;
			PW_Clear();
			putch_str(str3);
			
			Terminal = 0;
		}
		
		if(Terminal ==0)
		{
			Ispassword[arr_length] = KeyPad();
			
			if(key==0 && old_input_start==0)
			{
				_delay_ms(10);
				Put_into_arr();
			}
			
			if(key==1 && old_input_start==1 )
			{
				if(!ComparePassword())
				{
					M_start();
					old_input_start=0;
				}
				else
				{
					Incorrect();
					old_input_start=0;
				}
			}
		}
		
		if(Terminal == 1)
		{
			if(!((UCSR0A & 0x80)==0))
			{
				Ispassword[arr_length] = getch();
				arr_length++;
				putch(Ispassword);
				Lcd_STR(Ispassword);
				if(Ispassword[arr_length-1]=='x')
				{
					Ispassword[arr_length-1] = NULL; //strcmp 쓰기 위함
					
					if(!ComparePassword())
					{
						putch_str("\r\n");
						putch_str("Door is Open!");
						putch_str("\r\n");
						M_start();
						
						Putch_int = 0;
					}
					else
					{
						putch_str("\r\n");
						putch_str("Wrong PassWord!");
						putch_str("\r\n");
						Incorrect();
						
						Putch_int = 0;
					}
				}
				
				if(Ispassword[arr_length-1]=='c')
				{
					for (int x=0;x<4;x++)
					{
						password[x] = Ispassword[x];
					}
					password[arr_length-1] = NULL;
					Putch_int = 0;
					putch_str("\r\n");
					putch_str("Change Complete!");
					putch_str("\r\n");
					PW_Clear();
					Lcd_Clear();
					Lcd_STR(str5);
					_delay_ms(2000);
					Lcd_Clear();
					arr_length=0;
				}
				
			}
		}
	}
}


void M_start(void)
{
	
	Lcd_Clear();
	Lcd_Pos(0,0);
	Lcd_STR("Correct!");
	Lcd_Pos(1,0);
	Lcd_STR("Door is Open!!");
	
	PORTC = 0xFE; // 1111 1110
	_delay_ms(1000);
	PORTC = 0x7F; // 0111 1111
	_delay_ms(1000);
	PORTC = 0xFF;
	Lcd_Clear();
	PW_Clear();
	m_cnt=0;
	arr_length=0;
}
void Put_into_arr(void)
{
	arr_length++;

	PORTC = 0xFE; //디버깅용
	_delay_ms(100);
	PORTC = 0xFF;
	
	Lcd_STR(Ispassword);
	key=1;
}

int ComparePassword()
{
	cmp = strcmp(Ispassword,password);
	
	return cmp;
}
void Incorrect()
{
	Lcd_Clear();
	Lcd_Pos(0,0);
	Lcd_STR("Wrong PW!");
	Lcd_Pos(1,0);
	Lcd_STR("Try Again!!");
	_delay_ms(2000);
	Lcd_Clear();
	PW_Clear();
	m_cnt=0;
	arr_length=0;
}

void PW_Clear()
{
	for(int x=0;x<16;x++)
	{
		Ispassword[x]=NULL;
	}
}
