/*
	@File 		
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		02/10/22
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
 
  
*/

#include "config.h"

#include <xc.h>

//
#define LC75823_DI_HIGH         PORTCbits.RC0=1
#define LC75823_DI_LOW          PORTCbits.RC0=0

#define LC75823_CL_HIGH         PORTCbits.RC1=1
#define LC75823_CL_LOW          PORTCbits.RC1=0

#define LC75823_CE_HIGH         PORTCbits.RC2=1
#define LC75823_CE_LOW          PORTCbits.RC2=0

#define DELAY() __asm__ __volatile__("nop")

unsigned char BUF[159];

static unsigned char address[] = {0,15,30,45,60,75,90,105};

static const unsigned short Font[] =
{
    0x0000,	// space
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x0000,	// 
    0x3186,	// 0
    0x3000,	// 1
    0x238c,	// 2
    0x3388,	// 3
    0x320a,	// 4
    0x138a,	// 5
    0x138e,	// 6
    0x3080,	// 7
    0x338e,	// 8
    0x338a,	// 9
    0x0000,	// :
    0x0000,	// ;
    0x0000,	// <
    0x0000,	// =
    0x0000,	// >
    0x0000,	// ?
    0x0000,	// @
    0x328e,	// A
    0x33c0,	// B
    0x0186,	// C
    0x31c0,	// D
    0x038e,	// E
    0x028e,	// F
    0x1386,	// G
    0x320e,	// H
    0x01c0,	// I
    0x3104,	// J
    0x0c0e,	// K
    0x0106,	// L
    0x3416,	// M
    0x3816,	// N
    0x3186,	// O
    0x228e,	// P
    0x3986,	// Q
    0x2a8e,	// R
};

void LC75823_Write_Byte(int data)
{
    for(int mask=0x0001; mask; mask <<= 1)
    {
        LC75823_CL_LOW;
        if(data & mask) LC75823_DI_HIGH; else LC75823_DI_LOW;
        LC75823_CL_HIGH;
    }
}

void LC75823_Write_Address(unsigned char data)
{
    for(unsigned char mask=0x01; mask; mask <<= 1)
    {
        LC75823_CL_LOW;
        if(data & mask) LC75823_DI_HIGH; else LC75823_DI_LOW;
        LC75823_CL_HIGH;
    }
}

void LC75823_Data()
{
    LC75823_CE_LOW;
    
    LC75823_Write_Address(0x41);
    
    LC75823_CE_HIGH;
    
    for(unsigned char i=0; i<159; i++)
    {
        LC75823_CL_LOW;
        if(BUF[i] == 1) LC75823_DI_HIGH; else LC75823_DI_LOW;
        LC75823_CL_HIGH;
    }
            
    LC75823_CE_LOW;    

    LC75823_CE_HIGH;
}  

void LC75823_Char(unsigned char c, unsigned char digit)
{
    int i = 0; // 
    
    digit = address[digit];
    
    for(unsigned short mask = 0x0001; mask; mask <<= 1)
    {
        if(Font[c - 32] & mask) BUF[i+digit] = 1; else BUF[i+digit] = 0;
        i++;
    }
}

void LC75823_Init(void)
{
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    
    LC75823_CE_HIGH;
    LC75823_CL_HIGH;
}

int main(void) 
{
    // WAIT VCC
    __delay_ms(500);
    
    LC75823_Init();
    
    LC75823_Char('A', 0);
    LC75823_Char('B', 1);
    LC75823_Char('C', 2);
    LC75823_Char('D', 3);
    LC75823_Char('E', 4);
    LC75823_Char('F', 5);
    LC75823_Char('G', 6);
    LC75823_Char('H', 7);
    
    LC75823_Data();
    
    while(1)
    {
        
    }
    
    return 0;
}
