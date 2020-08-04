/*
 * 16bitTC_test.c
 *
 * Created: 2020-06-16 오전 11:34:21
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char led_data = 0x01;
unsigned char timer1cnt = 0;

int main(void)
{
	DDRA = 0xff;
	
	TCCR1A = 0x00;
	TCCR1B = (1<<CS10); //0x01;
	
	TCNT1 = 0; //카운터 값을 저장
	TIMSK = (1<<TOIE1); //0x04; 인터럽트ENABLE
	TIFR |= (1<<TOV1); //인터럽트 플래그 리셋
	
	sei();
	
    while (1) 
    {
		PORTA = led_data;
    }
	return 0;
}

ISR(TIMER1_OVF_vect)
{
	cli();
	
	timer1cnt++;
	if(timer1cnt == 255)
	{
		led_data <<= 1;
		
		if(led_data == 0x80)
			led_data = 0x01;
			
		timer1cnt = 0;
	}
	sei();
}

