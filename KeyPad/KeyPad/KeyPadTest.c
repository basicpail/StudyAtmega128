/*
 * KeyPadTest.c
 *
 * Created: 2020-08-01 오후 2:14:30
 *  Author: PKNU
 */ 
#define F_CPU 7372800
#include<avr/io.h>
#include<util/delay.h>

int main()
{
	//0~2번 까지 출력
	//4~7번 까지 입력
	DDRC = 0x0F;
	
	DDRD = 0x0F; //상위니블 입력, 하위니블 출력
	PORTC = 0xFF;
	while(1)
	{
		PORTD = 0xFE; //1111 1110 //PORTE의 0번 비트에 0이 출력될때
		
		if(PIND == 0xEE) // 1110 1110 -> 1
		{
			PORTC = 0xFE; //1111 1110
			_delay_ms(10);
			PORTC = 0xFF;
		}
		if(PIND == 0xDE) //1101 1110 ->4
		{
			PORTC = 0xFD; //1111 1101
			_delay_ms(10);
			PORTC = 0xFF;
		}
		if(PIND == 0xBE) //1011 1110 -> 7
		{
			PORTC = 0xFB; //1111 1011
			_delay_ms(10);
			PORTC = 0xFF;
		}
		if(PIND == 0x7E) //0111 1110 -> *
		{
			PORTC = 0xF7; //1111 0111
			_delay_ms(10);
			PORTC = 0xFF;
		}
		
		PORTD = 0xFD; //1111 1101
		
		if(PIND == 0xEE){} // 1110 1110 -> 2

		if(PIND == 0xDE){} //1101 1110 -> 5

		if(PIND == 0xBE){} //1011 1110 -> 8

		if(PIND == 0x7E){} //0111 1110 -> 0
		
		
		PORTD = 0xFB; //1111 1011
		
		if(PIND == 0xEE){} // 1110 1110 -> 3

		if(PIND == 0xDE){} //1101 1110 -> 6

		if(PIND == 0xBE){} //1011 1110 -> 9

		if(PIND == 0x7E){} //0111 1110 -> #
	}
}