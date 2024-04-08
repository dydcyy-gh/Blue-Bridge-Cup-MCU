#include <STC15F2K60S2.H>

#include "timer1.h"
#include "led.h"
#include "p0init.h"
#include "typedef.h"
#include "pwmtimer2.h"

//static u8 percent = 0;
u8 exvalue[] = {12,25,37,50,62,75,87,99};//
extern u8 i;//

//主函数在这里！
void main()
{
	p0init();
	timer1init(2);
	timer2init();
	while(1)
	{
		
	}
}


//这里是定时器1中断函数
void interrupttimer1() interrupt 3
{
//	static u8 count1=0;
//	static u8 flag = 0;
	static u8 count2=0;
//	count1++;
	count2++;
//	if(count1>12)//呼吸调速
//	{
//		count1=0;
//		if(percent == 99) flag = 1;
//		if(percent == 1) flag = 0;
//		switch(flag){
//			case 0:percent++;break;
//			case 1:percent--;break;
//		}
//	}
	if(count2>249)//流水灯调速
		{count2=0;ledflow();}
}

//这里是定时器2（pwm）中断函数
void interrupttimer2() interrupt 12
{
	pwm(100,exvalue[i]);//
}

//在前的是一种led呼吸流水灯
//在后的是另外一种
