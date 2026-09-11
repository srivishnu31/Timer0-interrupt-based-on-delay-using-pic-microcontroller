/*
 * File:   HECT.c
 * Author: SAN
 *
 * Created on September 10, 2026, 4:12 PM
 */


// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = LP        // Oscillator Selection bits (LP oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF     // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF         // Data EEPROM Memory Code Protection bit (Data EEPROM code-protected)
#pragma config WRT = HALF       // Flash Program Memory Write Enable bits (0000h to 0FFFh write-protected; 1000h to 1FFFh may be written to by EECON control)
#pragma config CP = ON          // Flash Program Memory Code Protection bit (All program memory code-protected)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.





#include <xc.h>

unsigned int count = 0;



void __interrupt() ISR(void)
{
    if(TMR0IF)
    {
        TMR0IF = 0;
        TMR0 = 61;

        count++;

        if(count <= 500)
        {
            RB0 = 1;
            RB1 = 0;
            RB2 = 0;
        }
        else if(count <= 700)
        {
            RB0 = 0;
            RB1 = 1;
            RB2 = 0;
        } 
        else if(count <= 1200)
        {
            RB0 = 0;
            RB1 = 0;
            RB2 = 1;
        }
     else
        {
            count = 0;
        }
    }
}


void main(void)
{
    TRISB = 0x00;
    PORTB = 0x00;

    OPTION_REG = 0x07;
    TMR0 = 61;

    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;

    
    RB0 = 1;       
    RB1 = 0;
    RB2 = 0;

    while(1)
    {
        

        if(RB0 == 1)
        {
            
            RB3 = 0;
            RB4 = 0;
            RB5 = 1;
        }
           else if(RB1 == 1)
        {
            
            RB3 = 0;
            RB4 = 1;
            RB5 = 0;
        }

        else if(RB2 == 1)
        {
            
            RB3 = 1;
            RB4 = 0;
            RB5 = 0;
        }
    }
}
