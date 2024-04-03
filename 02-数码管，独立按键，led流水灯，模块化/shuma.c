#include <STC15F2K60S2.H>
#include "typedef.h"

u8 shumatmp[8]={23,23,23,23,23,23,23,23};//数码管缓冲区

//共阳数码管段码表(考试会给的吧)
//code代表放入只读存储器
u8 code LedChar[] = {
	0xC0, 0xF9, 0xA4, 0xB0,//0    0  1  2  3
	0x99, 0x92, 0x82, 0xF8,//4    4  5  6  7
	0x80, 0x90, 0x88, 0x83,//8    8  9  A  b
	0xC6, 0xA1, 0x86, 0x8E,//12   C  d  E  F
	0x89, 0xC7, 0xC8, 0x8c,//16   H  L  N  P
	0xC1, 0xbf, 0x7f, 0xff,//20   U  -  .  null
}; 

//单字节数码管显示(直接输入数字，在中断调用)
//locate：1-8  number：1-23
void shuma(u8 locate,u8 number)
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

//数码管辅助多位整数显示 (add zero)
//把值填入缓存数组，放入中断更新数组
//locate：1-8  number：>0 lens:max length
void warma_add_zero(u8 locate,u8 lens,u32 num)
{
	char i,j;
	u8 shark[8];
	for(i=0;i<8;i++)
	{
		shark[i]=num%10;
		num/=10;
	}
	for(j=locate-1;j<8;j++)
	{
		shumatmp[j] = shark[lens-1];
		lens--; if(lens==0) break;
	}
}

//数码管辅助多位整数显示 (none zero)
//把值填入缓存数组，放入中断更新数组
//locate:1-8  locate之前不受影响，locate+lens-1之后的不受影响
void warma_none_zero(u8 locate,u8 lens,u32 num)
{
	char i,j = 0;
	u8 shark[8];
	for(i=0;i<8;i++)
	{
		shark[i]=num%10;
		num/=10;
	}
	for(i=lens-1;i>=0;i--)
	{
		if(shark[i]==0) {shumatmp[locate-1+j]=23;j++;}
		else break;
	}
	for(;i>=0;i--)
	{
		shumatmp[locate-1+j] = shark[i];
		j++;
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