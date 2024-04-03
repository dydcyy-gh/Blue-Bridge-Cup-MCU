#include <STC15F2K60S2.H>
#include "typedef.h"

//定时器2 模式1 (16位自动重载)
//@12.000MHz 10us 1t (不分频) 高速模式
void timer2init()
{
	AUXR |= 0x04;
	//计算得出TL TH的值
	T2L = 0x88;				//设置定时初始值
	T2H = 0xFF;				//设置定时初始值	
	//auxr
	AUXR |= 0x10;			//定时器2开始计时
	//interupt
	IE2 |= 0x04;			//使能定时器2中断
	EA = 1;             //cpu中断允许位
}
