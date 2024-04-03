#include <STC15F2K60S2.H>
#include "typedef.h"
#include "ds18b20.h"
#include "shuma.h"
#include "timer1.h"

void main()
{
	timer1init(2);
	while(1)
	{
		
	}
}

//这里是定时器1中断函数
void interrupttimer1() interrupt 3
{
	static u16 count=0;
	count++;
	if(count>499)
		{count=0;ds18b20_shuma();}
	shumascan();
}