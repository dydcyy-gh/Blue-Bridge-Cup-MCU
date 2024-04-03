#include <STC15F2K60S2.H>
#include "typedef.h"

//定时器2 模式1 (16位自动重载)
//@12.000MHz 10us 12t (不分频) 高速模式
void timer2init()
{
	AUXR |= 0xFB;
	//th tl
	T2L = 0xF6;			//设置定时初始值
	T2H = 0xFF;			//设置定时初始值	
	//auxr
	AUXR |= 0x10;		//定时器2开始计时
	//interupt
	IE2 |= 0x04;		//使能定时器2中断
	EA = 1;             //cpu中断允许位
}

//直流电机
void motor(u8 a)
{
	P2=(P2&0x1f)|0xa0;
	P04=0;//关继电器
	P05=a;//a=0,输出1
	P06=0;//关蜂鸣器
	P2&=0x1f;
}

//pwm计算函数  定时器10us（100000hz）
//max（最大精度）:建议10（T=100us）-100（T=1ms）
//ex（占空比）：Ton/T  ex/max
void pwm (u8 max,u8 ex)
{
	static u8 cnt = 0;
	if(cnt == ex)
	{
		motor(1);
	}
	if(cnt < max)
		cnt++;
	else
	{
		motor(0);
		cnt = 0;
	}
}

//这里是定时器0（pwm）中断函数
void interrupttimer0() interrupt 12
{
	pwm (100,80);
}

