#include <STC15F2K60S2.H>
#include "shuma.h"
#include "typedef.h"

//独立按键用此声明
//读出的值为0即为按下
sbit KEY_IN_1 = P3^3;sbit KEY_IN_2 = P3^2;sbit KEY_IN_3 = P3^1;sbit KEY_IN_4 = P3^0;

extern u8 num;

//按键行为函数
void keyaction4(u8 i)
{
	switch(i)
	{
		case 0:num = 0x00;break;
		case 1:num = 0x01;break;
		case 2:num = 0x02;break;
		case 3:num = 0x03;break;
	}
}

//独立按键扫描函数(在中断调用)
void keyscan4()
{
	u8 i;
	//2*8ms延时判断
	static u8 keytmp[4] = {0xff,0xff,0xff,0xff};
	//防止重复对比
	static u8 keyold[4] = {1,1,1,1};
	static u8 keynow[4] = {1,1,1,1};

	keytmp[0] = (keytmp[0]<<1)| KEY_IN_1;
	keytmp[1] = (keytmp[1]<<1)| KEY_IN_2;
	keytmp[2] = (keytmp[2]<<1)| KEY_IN_3;
	keytmp[3] = (keytmp[3]<<1)| KEY_IN_4;
	
	for(i=0;i<4;i++)
	{
		if(keytmp[i] == 0xff)
		{
			keynow[i] = 1;
		}
		else if(keytmp[i] == 0x00)
		{
			keynow[i] = 0;
		}
		else {}
	}
	for(i=0;i<4;i++)
	{
		if(keynow[i]!=keyold[i])
		{
			if(keynow[i]==0)
			{
				keyaction4(i);
			}
			keyold[i]=keynow[i];
		}
	}
}