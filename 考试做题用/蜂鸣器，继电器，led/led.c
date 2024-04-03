#include <STC15F2K60S2.H>
#include "typedef.h"

u8 shift = 0x01;

//基础led
void led(u8 locate)//0x
{
	P2 = (P2&0x1f)|0x80;
	P0 = locate;
	P2 &= 0x1f;
}

//led流水灯(中断调用）
void ledflow()
{
	static bit x = 0;
	
	P2 = (P2&0x1f)|0x80;
	P0 = ~(shift);
	P2 &= 0x1f;
	
	if(x == 0)
	{
		shift<<1;
		if(shift == 0x80) x = 1;
	}
	else
	{
		shift>>1;
		if(shift == 0x01) x = 0;
	}
}


//pwm计算函数  定时器10us（100000hz）
//max（最大精度）:建议10（T=100us）-100（T=1ms）
//ex（占空比）：Ton/T  ex/max
void pwm (u8 max,u8 ex)
{
	static u8 cnt = 0;
	if(cnt == ex)
	{
		led(0xff);
	}
	if(cnt < max)
		cnt++;
	else
	{
		led(~shift);
		cnt = 0;
	}
}