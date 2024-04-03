#include <STC15F2K60S2.H>
#include "wave.h"
#include "shuma.h"
#include "timer1.h"

u8 flag = 0;

void main()
{
	timer1init(2);
	while(1)
	{
		if(flag == 1)
		{
			flag = 0;
			warma(2,receive_wave());
		}
	}
}

//这里是定时器1中断函数
void interrupttimer1() interrupt 3
{
	u8 count;
	count++;
	if(count>250)
	{
		count = 0;
		flag = 1;
	}
	shumascan();
}