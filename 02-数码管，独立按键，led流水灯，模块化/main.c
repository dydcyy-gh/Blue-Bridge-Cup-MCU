//独立按键(短按加长按)，数码管显示，led流水灯
#include <STC15F2K60S2.H>
#include "shuma.h"
#include "4key.h"
#include "timer1.h"
#include "led.h"
#include "p0init.h"
#include "typedef.h"

u32 number = 114;//显示数字
//extern类型，在4key.c再次声明

extern u8 shumatmp[];

//主函数在这里！
void main()
{
	p0init();
	warma_none_zero(3,5,number);
	timer1init(2);
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
	shumascan();
	keyscan4();
}