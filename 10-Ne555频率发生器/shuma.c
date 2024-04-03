#include <STC15F2K60S2.H>
#include "typedef.h"

//共阳数码管段码表(考试会给的吧)
u8 code LedChar[] = {
	0xC0, 0xF9, 0xA4, 0xB0,//0-3
	0x99, 0x92, 0x82, 0xF8,//4-7
	0x80, 0x90, 0x88, 0x83,//8-b
	0xC6, 0xA1, 0x86, 0x8E,//C-F
}; 

u8 shumatmp[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};//数码管缓冲区

//基础数码管显示(直接输入数字，在中断调用)
void shumaguan(u8 locate,u8 number)
{
	//清零
	P2=(P2&0x1f)|0xe0;
	P0=0xff;
	P2&=0x1f;
	//数码管位选（1亮）   y6c
	P2=(P2&0x1f)|0xc0;
	P0=(0x01<<(locate-1));
	P2&=0x1f;
	//数码管段选（0亮）   y7c
	P2=(P2&0x1f)|0xe0;
	P0=LedChar[number];
	P2&=0x1f;
}

//数码管显示(输入0x00）
void shuma(u8 locate,u8 num0x)
{
	//清零
	P2=(P2&0x1f)|0xe0;
	P0=0xff;
	P2&=0x1f;
	//数码管位选（1亮）   y6c
	P2=(P2&0x1f)|0xc0;
	P0=(0x01<<(locate-1));
	P2&=0x1f;
	//数码管段选（0亮）   y7c
	P2=(P2&0x1f)|0xe0;
	P0=num0x;
	P2&=0x1f;
}

//数码管辅助多位整数显示（起始位置，u32整数）
void warma(u8 locate,u32 num)
{
	char i,j=0;
	u8 shark[8];
	for(i=0;i<8;i++)
	{
		shark[i]=num%10;
		num/=10;
	}
	for(i=7;i>=0;i--)
	{
		if(shark[i]==0){shumatmp[i]=0xff;j++;}
		else break;
	}
	for(;i>=0;i--)
	{
		shumatmp[6-j-i+locate] = LedChar[shark[i]];
	}
}

//数码管扫描，用于中断函数，实现多位显示
void shumascan()
{
	static u8 count = 0;
	count++;
	switch(count)
	{
		case 1:
			shuma(1,shumatmp[0]);
			break;
		case 2:
			shuma(2,shumatmp[1]);
			break;
		case 3:
			shuma(3,shumatmp[2]);
			break;
		case 4:
			shuma(4,shumatmp[3]);
			break;
		case 5:
			shuma(5,shumatmp[4]);
			break;
		case 6:
			shuma(6,shumatmp[5]);
			break;
		case 7:
			shuma(7,shumatmp[6]);
			break;
		case 8:
			shuma(8,shumatmp[7]);
			count = 0;
			break;
	}
}