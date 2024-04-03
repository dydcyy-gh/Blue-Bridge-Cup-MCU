#include <STC15F2K60S2.H>
#include "typedef.h"

//计数器0为ne555专用

//计数器0 模式1 (16位自动重载)
//@12mhz 1t (不分频)
void timer0init()
{
	AUXR |= 0x80;
	//TMOD
	TMOD |= 0x05;		//设置定时器模式
	//TL TH
	TL0 = 0x00;		    //设置定时初始值
	TH0 = 0x00;		    //设置定时初始值	
	//TCON
	TF0 = 0;			//清除TF0标志
	TR0 = 0;			//定时器0不计时
	//interupt
	ET0 = 0;            //中断允许位
}
