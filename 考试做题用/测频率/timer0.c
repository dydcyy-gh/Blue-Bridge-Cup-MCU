#include <STC15F2K60S2.H>
#include "typedef.h"

//计数器0为ne555专用

//计数器0 模式1 (16位自动重载)
//@12.000Mhz 1t (不分频)
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

////主函数在这里！
//void main()
//{
//	timer0init();
//	timer1init(2);
//	while(1)
//	{
//		
//	}
//}

////这里是定时器1中断函数
//ne555测频用
//void interrupttimer1() interrupt 3
//{
//	u16 FreqCnt;//频率计数
//	static u16 AllTime = 0;
//	if(AllTime == 0)          //ALLTime为计时的变量
//	{
//		TR0 = 1;              //计数器0开启计数
//		AllTime++;
//	}
//	else if(AllTime < 500)  //如果小于1s钟的话
//	{
//		AllTime++;
//	}
//	else                        //如果1s到了的话
//	{
//		AllTime = 0;            //清空计时变量
//		TR0 = 0;                //停止计时
//		FreqCnt = (((u16)TH0 << 8) |(u16)TL0); //将脉冲频率取出
//		TH0 = 0;                //清除脉冲计数现有值，做好初始化
//		TL0 = 0;
//	}
//}
