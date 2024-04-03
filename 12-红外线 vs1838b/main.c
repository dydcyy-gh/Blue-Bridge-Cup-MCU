//显示键码到数码管

#include <STC15F2K60S2.H>
#include "infrared.h"
#include "typedef.h"

sbit IR_INPUT = P1^1;

u8 code LedChar[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};
u8 LedBuff[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

u8 T0RH = 0, T0RL = 0;

void ConfigTimer0(u16 ms);
void CloseFucker();

void main()
{	
	EA = 1;
	ConfigTimer0(1);
	InitInfrared();

	while(1)
	{
		if(!IR_INPUT)
		{
			IRScan();
		}
		if(irflag)
		{
		 	irflag = 0;
			LedBuff[5] = LedChar[ircode[0] >> 4];
			LedBuff[4] = LedChar[ircode[0]&0x0F];
			LedBuff[1] = LedChar[ircode[2] >> 4];
			LedBuff[0] = LedChar[ircode[2]&0x0F];
		}
	}
}

void ConfigTimer0(u16 ms)
{
    u32 tmp; 
    
    tmp = 12000000 / 12;    
    tmp = (tmp * ms) / 1000;  
    tmp = 65536 - tmp;          
    T0RH = (u8)(tmp>>8);  
    T0RL = (u8)tmp;
    TMOD &= 0xF0;   
    TMOD |= 0x01;   
    TH0 = T0RH;     
    TL0 = T0RL;
    ET0 = 1;       
    TR0 = 1;       
}

void LedScan()
{
 	static u8 index=0;

	P2 = (P2 & 0x1F) | 0xE0;
	P0 = 0xFF;
	P2 = (P2 & 0x1F);

	P2 = (P2 & 0x1F) | 0xC0;
	P0 = 0x80>>index;
	P2 = (P2 & 0x1F);
	P2 = (P2 & 0x1F) | 0xE0;
	P0 = LedBuff[index];
	P2 = (P2 & 0x1F);
	
	index++;
	index &= 0x07;
}

void InterruptTimer0() interrupt 1
{
    TH0 = T0RH; 
    TL0 = T0RL;

	LedScan();
}
