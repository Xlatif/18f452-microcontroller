/*
 * THIS PROGRAM DEMONSTRATES HOW TO RECEIVE DATA FROM ANOTHER MICROCONTROLLER VIA RX LINE
 * THE VALUE RECEIVED VIA RX LINE IS DISPLAYED ON PORTD PORT
*/
#include <p18f452.h>
#pragma config WDT = OFF

#pragma interrupt SERVICE
void SERVICE(void)
{
	if(PIR1bits.RCIF)		// CHECK IF DATA IS PRESENT ?
		LATD = RCREG;		// DISPLAY IT IN PORTD
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
	TRISC = 0xBF;
	TRISD = 0x00;
	RCSTA = 0x90;			// RECEPTION CONFIGURATION REG
	SPBRG = 0x06;
	INTCONbits.GIE = 1;		// INTERRUPT BIT
	INTCONbits.PEIE = 1;
	PIE1bits.RCIE = 1;		// RECEPTION ENABLE BIT
	while(1);
}
