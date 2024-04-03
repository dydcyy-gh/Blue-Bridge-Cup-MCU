//独立按键长按，短按控制
#include <STC15F2K60S2.H>
#include "ctrl.h"
#include "typedef.h"

//读出的值为0即为按下
sbit KEY_IN_1 = P3^3;sbit KEY_IN_2 = P3^2;
sbit KEY_IN_3 = P3^1;sbit KEY_IN_4 = P3^0;

u16 keytimelen[4]={0,0,0,0};//长按时间

//按键行为函数 放在CTRL里面
void keyaction4(u8 i)
{
	switch(i)
	{
		case 1:
			break;
		
		case 2:
			break;

		default:
			break;
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
	//长按起始时间
	static u16 timemax[4] = {1000,1000,1000,1000};
	
	keytmp[0] = (keytmp[0]<<1)| KEY_IN_1;
	keytmp[1] = (keytmp[1]<<1)| KEY_IN_2;
	keytmp[2] = (keytmp[2]<<1)| KEY_IN_3;
	keytmp[3] = (keytmp[3]<<1)| KEY_IN_4;
	
	for(i=0;i<4;i++)
	{
		if(keytmp[i] == 0xff)
		{
			keynow[i] = 1;
			keytimelen[i] = 0;
		}
		if(keytmp[i] == 0x00)
		{
			keynow[i] = 0;
			keytimelen[i] += 2;
		}
	}
	
	for(i=0;i<4;i++)
	{
		//短按检测
		if(keyold[i] != keynow[i])
		{
			if(keynow[i]==0)
			{
				keyaction4(i);
			}
			keyold[i]=keynow[i];
		}
		//长按检测
		if(keytimelen[i] < 60000 && timemax[i] < 60000)
		{			
			if(keytimelen[i] > timemax[i])
			{
				keyaction4(i);
				timemax[i] += 100;//0.1ms+1
			}
		}
		else
		{
			keytimelen[i] = 900;
			timemax[i] = 1000;
		}
	}
}