/*
 * DISPLAYING NUMBERS(0 TO 9) IN 7 SEGMENT DISPLAY
 * USING TIMER0 TO GENERATE DELAY
 * IN ORDER TO CHANGE DELAY YOU HAVE TO PASS THE CORRESPONDING VALUES NEEDED TO ACHIEVE THE DESIRED DELAY
*/
#include <p18f452.h>
#pragma config WDT = OFF

#define TRUE 1

void delay(unsigned char config, unsigned char HIGH, unsigned char LOW);

#pragma interrupt SERVICE
void SERVICE(void)
{
}

#pragma code VECTOR = 0x00008
void VECTOR(void)
{
	_asm
		GOTO SERVICE
	_endasm
}
#pragma code



void main(void)
{
	unsigned char counter = 0;	// COUNTER USED TO COUNT NUMBERS
	TRISD = 0xF0;			// THE LOWEST NIBBLE OF PORTD AS OUTPUT
	while(TRUE)
	{
		if(counter != 0x0A)	// CHECK IF COUNTER DOES NOT EXCEEDS 0x0A
		{
			LATD = counter;	
			delay(0x02, 0x0B, 0xDC);		// PASS ARGUMENTS NEEDED TO GENERATE THE DESIRED DELAY
			++counter;				// INCREMENT THE COUNTER
		}
		else
			counter = 0;				// RESET THE COUNTER
	}
}

void delay(unsigned char config, unsigned char HIGH, unsigned char LOW)
{
	T0CON = config;
	TMR0H = HIGH;
	TMR0L = LOW;
	INTCONbits.TMR0IF = 0;
	T0CONbits.TMR0ON = 1;
	while(!INTCONbits.TMR0IF);
	INTCONbits.TMR0IF = 0;
	T0CONbits.TMR0ON = 0;
}
