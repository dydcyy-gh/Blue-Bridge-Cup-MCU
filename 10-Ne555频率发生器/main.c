//独立按键(短按加长按)，数码管显示，led流水灯
//本程序需将j3的signal和p34短接
#include <STC15F2K60S2.H>
#include "shuma.h"
#include "timer1.h"
#include "timer0.h"
#include "typedef.h"


//主函数在这里！
void main()
{
	timer0init();
	timer1init(2);
	while(1)
	{
		
	}
}

//这里是定时器1中断函数
void interrupttimer1() interrupt 3
{
	u16 FreqCnt;
	static u16 AllTime = 0;
	if(AllTime == 0)          //ALLTime为计时的变量
	{
		TR0 = 1;                 //计数器0开启计数
		AllTime++;
	}
	else if(AllTime < 500)  //如果小于1s钟的话
	{
		AllTime++;
	}
	else                        //如果1s到了的话
	{
		AllTime = 0;            //清空计时变量
		TR0 = 0;                //停止计时
		FreqCnt = (((u16)TH0 << 8) |(u16)TL0); //将脉冲频率取出
		warma(1,FreqCnt);
		TH0 = 0;                //清除脉冲计数现有值，做好初始化
		TL0 = 0;
	}
	shumascan();
}