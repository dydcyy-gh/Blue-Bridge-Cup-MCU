#include <STC15F2K60S2.H>
#include "typedef.h"


//定时器1 模式1 (16位自动重载)
//@12mhz xms 12t (12分频) 低速模式
void timer1init(u8 ms)
{
	u32 tmp;
	//AUXR在12t模式时可省略
	AUXR &= 0xBF;
	//TMOD
	TMOD &= 0x0F;    	//设置定时器模式
	//计算得出TL TH的值
	tmp = 12000000/12;  //每s 计数TMP次
	tmp = (tmp*ms)/1000;//每ms计数TMP次
	tmp = 65536 - tmp;
	TH1 = (u8)(tmp>>8); //tmp / 256
	TL1 = (u8)tmp;      //tmp % 256			
	//TCON
	TF1 = 0;			//清除TF0标志
	TR1 = 1;			//定时器0开始计时
	//interupt
	ET1 = 1;            //中断允许位
	EA = 1;             //cpu中断允许位
	PT1 = 0;            //优先级0(最低)
}

