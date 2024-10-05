#include <p18f452.h>
#pragma config WDT = OFF

unsigned char flag = 0x00;

void acquisitionTime(void);

#pragma interrupt myFunction
void myFunction(void)
{
	if(PIR1bits.ADIF)
	{
		PIR1bits.ADIF = 0;
		LATD = ADRESL;
		LATB = ADRESH;
		flag = 1;
	}
}

#pragma code myVector = 0x00008
void myVector(void)
{
	_asm
		GOTO myFunction
	_endasm
}
#pragma code


void main(void)
{
	TRISD = 0x00;
	TRISB = 0x00;
	TRISAbits.TRISA0 = 1;
	ADCON0 = 0x41;
	ADCON1 = 0x84;
	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;	
	PIE1bits.ADIE = 1;
	PIR1bits.ADIF = 0;
	flag = 0x01;
	while(1)
	{
		if(flag)
		{
			acquisitionTime();
			ADCON0bits.GO = 1;			
			flag = 0;
		}
	}
}
void acquisitionTime(void)
{
	T0CON = 0x48;	
	TMR0L = 236;
	INTCONbits.TMR0IF = 0;
	T0CONbits.TMR0ON = 1;
	while(!INTCONbits.TMR0IF);
	INTCONbits.TMR0IF = 0;
	T0CONbits.TMR0ON = 0;
}