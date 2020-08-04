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

void putch_str(char *str)
{
	unsigned char i = 0;
	while(str[i] != '\0')
		putch(str[i++]);
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
unsigned char cnt[3];
unsigned char flag ;
unsigned char str[10];

unsigned char text[] =
	"\r\n++++Menu++++\r\n L: LED\r\n C: CDS\r\n 0~7 PIANO\r\n r,f: Step Motor\r\ push button: stop\r\n";
unsigned char cds_text[] = "\r\nCds Value: ";

unsigned int Do[10]={261,293,329,349,391,440,493,523};

unsigned char scale = 0;

int main(void)
{
	unsigned char i,j = 0;
	
		
	TCCR3A |= 0x00;
	TCCR3B |= 0x19;
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	DDRE = 0x08;
	
	DDRF = 0x03;
	PORTF = 0x03;
	
	DDRE = 0x04;
	PORTE = 0x04;

	ADMUX = 0x00;
	ADCSRA = 0x87;
	
	DDRB = 0x20;
	DDRD = 0XF0;
	PORTB &= ~0x20;
	
	EICRA = 0x03;
	EIMSK = 0x01;
	EIFR = 0x01;
	sei();

	
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
		cnt[0] = getch();
		putch(cnt[0]);
		
		//led
		if(cnt[0] == 'l'||cnt[0] == 'L')
		{
			flag=1;
			while(flag)
			{
				led();
			}
			
			cnt[0],cnt[1] ='\0';
		}
		//motor
		if(cnt[0] == 'f'||cnt[0] == 'r')
		{
			flag=1;
			while(flag)
			{
				if(cnt[0] == 'f')
				{
					step_motor_f();
				}
				if(cnt[0] == 'r')
				{
					step_motor_r();
				}
			}
		}
		//cds
		if(cnt[0] == 'c' || cnt[0] == 'C')
		{
			flag=1;
			while(flag)
			{
				cds();
			}
		}
		//piano
		if((cnt[0]-0x31 >=0 && cnt[0]-0x31 <= 9))
		{
			piano(cnt[0]);	
		}

	}
}


SIGNAL(INT0_vect)
{
	cli();
	unsigned char i = 0;
	flag=0;
	while(text[i] != '\0')
	{
		putch(text[i++]);
	}
	sei();
}

void piano(unsigned char x)
{
	scale = x;
	ICR3 = 7273800/Do[scale-0x31]/30;
	TCCR3A = 0x40;
	_delay_ms(200);
	TCCR3A = 0x00;
}


void cds()
{
	unsigned char addata = 0;
	unsigned char data[5];
	unsigned char i = 0;
	
	ADCSRA |= 0x40;
	while((ADCSRA&0x01) == 0x00);
	addata = ADC;
	sprintf(str,"%d",ADC);

	while(cds_text[i] != '\0')
	{
		putch(cds_text[i++]);
	}
	putch_str(str);
	_delay_ms(2000);
}
void led()
{
	
	unsigned char led_data = 0x01;

	for(int i=0;i<7;i++)
	{
		if(flag==1){
		PORTA = led_data;
		led_data <<= 1;
		_delay_ms(100);
		}
	}
	for(int j=0;j<7;j++)
	{
		if(flag==1){
		PORTA = led_data;
		led_data >>= 1;
		_delay_ms(100);
		}
	}
	
}

void step_motor_f()
{
		for(int i=0;i<10;i++)
		{
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
void step_motor_r()
{
		for(int i = 0; i<10; i++)
		{
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