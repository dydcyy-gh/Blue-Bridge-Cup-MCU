#include <STC15F2K60S2.H>
#include "typedef.h"

//基础led
void led(u8 locate)//0亮
{
	P2=(P2&0x1f)|0x80;
	P0=locate;
	P2&=0x1f;
}

//led流水灯(中断调用）
void ledflow()
{
	static bit x = 0;
	static u8 shift = 0x01;
	
	P2=(P2&0x1f)|0x80;
	P0=~shift;
	if(x == 0)
	{
		shift <<= 1;
		if(shift == 0x80) x = 1;
	}
	else
	{
		shift >>= 1;
		if(shift == 0x01) x = 0;
	}
	P2&=0x1f;
}
