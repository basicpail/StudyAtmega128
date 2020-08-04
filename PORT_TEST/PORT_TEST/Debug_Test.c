/*
 * FND_TEST3.c
 *
 * Created: 2020-06-15 오전 11:45:06
 *  Author: PKNU
 */
#include <avr/io.h>

unsigned char data =0x01;
int main()
{
	unsigned long i;
	DDRA = 0xff;
	PORTA = 0x00;
	while(1)
	{
		PORTA = data;
		data << 1;
		for(i=0; i<1000; i++)
		{
			if(data == 0x00)
			data = 0x01;
		}
	}
}
