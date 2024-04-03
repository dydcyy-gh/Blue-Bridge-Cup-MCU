#include <STC15F2K60S2.H>
#include "pcf8591.h"
#include "4key.h"
#include "p0init.h"
#include "timer1.h"
#include "typedef.h"
#include "shuma.h"

u8 num;

void main()
{
	p0init();
	timer1init(2);
	while(1)
	{
		dac(51);
	}
}

//这里是定时器1中断函数
void interrupttimer1() interrupt 3
{
	
}