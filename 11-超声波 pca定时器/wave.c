#include <STC15F2K60S2.H>
#include "intrins.h"
#include "typedef.h"

#define TX P10	//超声波发送引脚
#define RX P11	//超声波信号接收反馈引脚

void send_wave()//40khz方波（25us）
{
	u8 i = 8;
	while(i--)
	{
		TX = 1;_nop_();_nop_();_nop_();
		TX = 0;_nop_();_nop_();_nop_();
	}
}

//返回0-99cm的数字，使用pca定时器，tmod改为cmod，tl th改为cl ch就行
u8 receive_wave()
{
	u16 time,distance;
	CMOD = 0x00;			//设置定时器模式
	CL = 0x00;				//设置定时初始值
	CH = 0x00;				//设置定时重载值
	CF = 0;				//清除CF标志
	CR = 0;				//定时器0不开始计时
	
	send_wave();
	CR = 1;
	while(RX == 1 && CH<0x17);
	CR = 0;
	
	if(RX == 0)
	{
		RX = 1;
		time = (CH * 256) + CL;
		distance = (u32)(time * 0.017);
		//340/2/10000
	}
	else
	{
		distance = 99; 
	}
	return distance;
}