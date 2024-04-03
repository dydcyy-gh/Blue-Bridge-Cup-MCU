//独立按键(短按加长按)，数码管显示，led流水灯
#include <STC15F2K60S2.H>
#include "shuma.h"
#include "16key.h"
#include "timer1.h"
#include "led.h"
#include "p0init.h"
#include "typedef.h"

//主函数在这里！
void main()
{
	p0init();
	timer1init(1);
	while(1)
	{
		
	}
}

//这里是定时器1中断函数
void interrupttimer1() interrupt 3
{
	static u8 count=0;
	count++;
	if(count>249)
		{count=0;ledflow();}
	keyscan16();shumascan();
}