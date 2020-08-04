/*
 * 0618Exam.c
 *
 * Created: 2020-06-18 오전 10:17:25
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);
	
	UDR0 = data;
	UCSR0A |= 0x20;
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

unsigned char val;
unsigned char flag=1;

int main(void)
{
	unsigned char text[] = 
		"\r\n++++Menu++++\r\n L: LED\r\n C: CDS\r\n 0~7 PIANO\r\n S: Step Motor\r\ push button: stop\r\n";
	
	unsigned char i = 0;
	
	EICRA = 0x03;
	EIMSK = 0x03;
	EIFR = 0x03;
	sei();
	
	DDRE = 0x04;
	PORTE = 0x04;
	
	
	ADMUX = 0x00;
	ADCSRA = 0x87;
	
	DDRB = 0x20;
	DDRD = 0XF0;
	PORTB &= ~0x20;
	
	DDRE = 0xfe;
	DDRA = 0xFF;
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	while(text[i] != '\0')
	{
		putch(text[i++]);
	}

	while(1)
	{
		//putch(getch());
		//val = getch();
		if(getch() == 'l'||getch() == 'L')
		{
			led();
			_delay_ms(100);
		}
		if(getch() == 'f'||getch() == 'r')
		{
			val = getch();
			step_motor(val);
			_delay_ms(100);
		}
		if(getch() == 'c' || getch() == 'C')
		{
			cds();
			_delay_ms(100);
		}
	}
}

SIGNAL(INT0_vect)
{
	cli();
	flag = 0;
	sei();
}
void cds()
{
	unsigned int addata = 0;
	unsigned char data[5];
	unsigned char i = 0;
	ADCSRA |= 0x40;
	while((ADCSRA& 0x01) == 0x00);
	addata = ADC;
	data[0] = ((addata/1000)%10);
	data[1] = ((addata/100)%10);
	data[2] = ((addata/10)%10);
	data[3] = ((addata%10));
	
	while(data[i] != '\0')
	{
		putch(data[i++]);
	}
}
void led()
{
	while(flag)
	{
		
	unsigned char led_data = 0x01;
	
	for(int i=0;i<7;i++)
	{
		PORTA = led_data;
		led_data <<= 1;
		_delay_ms(50);
		if(led_data == 0x80)
		{
			for(int j=0;i<7;j++)
			{
				PORTA = led_data;
				led_data >>= 1;
				_delay_ms(50);
			}
		}
	}
	
	}
}

void step_motor(unsigned char x)
{
	if(x == 'f')
	{
		//unsigned char m_data= 0x10;
		/*for(int i=0;i<4;i++)
		{
			PORTD = m_data;
			m_data <<= 1;
			_delay_ms(10);
			
		}*/
		for(int i =0;i<10;i++){
		PORTD = 0x10;
		_delay_ms(10);
		PORTD = 0x20;
		_delay_ms(10);
		PORTD = 0x40;
		_delay_ms(10);
		PORTD = 0x80;
		_delay_ms(10);
		}
		
	}
	if(x == 'r')
	{
		//unsigned char m_data= 0x80;
		//for(int i=0;i<4;i++)
		//{
			//PORTD = m_data;
			//m_data >>= 1;
			//_delay_ms(10);
		//}
	for(int i=0;i<10;i++){	
		PORTD = 0x80;
		_delay_ms(10);
		PORTD = 0x40;
		_delay_ms(10);
		PORTD = 0x20;
		_delay_ms(10);
		PORTD = 0x10;
		_delay_ms(10);
	}
	}
}