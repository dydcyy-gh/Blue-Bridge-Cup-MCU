#include <STC15F2K60S2.H>
#include "ctrl.h"
#include "typedef.h"

//矩阵键盘用此声明
//IN给零，OUT为0即为按下
sbit key_in_1 = P3^0;//7  11 15 19
sbit key_in_2 = P3^1;//6  10 14 18
sbit key_in_3 = P3^2;//5  9  13 17
sbit key_in_4 = P3^3;//4  8  12 16

sbit key_out_1 = P4^4; //7  6  5  4
sbit key_out_2 = P4^2; //11 10 9  8
sbit key_out_3 = P3^5; //15 14 13 12
sbit key_out_4 = P3^4; //19 18 17 16

//矩阵键盘含义数组
u8 keymap[4][4] ={
	{7, 11,15,19},
	{6, 10,14,18},
	{5, 9, 13,17},
	{4, 8, 12,16}
};

//矩阵键盘扫描函数(在中断调用)
//扫描一轮耗时x*8*4ms（建议中断x=1ms）
void keyscan16()
{
	u8 i;
	static u8 key = 0;
	//2*8ms延时判断
	static u8 keytmp[4][4] = {{0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff},
							{0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff}};
	//防重复对比数组
	static u8 keyold[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
	static u8 keynow[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
		
	switch(key)//打开一路并关闭上一轮打开的
	{
		case 0: key_in_1 = 0; key_in_4 = 1; break;
		case 1: key_in_2 = 0; key_in_1 = 1; break;
		case 2: key_in_3 = 0; key_in_2 = 1; break;
		case 3: key_in_4 = 0; key_in_3 = 1; break;
		default : break;
	}
	
	keytmp[key][0] = (keytmp[key][0]<<1)| key_out_1;
	keytmp[key][1] = (keytmp[key][1]<<1)| key_out_2;
	keytmp[key][2] = (keytmp[key][2]<<1)| key_out_3;
	keytmp[key][3] = (keytmp[key][3]<<1)| key_out_4;
	
	for(i=0;i<4;i++)
	{
		if(keytmp[key][i] == 0xff)
		{
			keynow[key][i] = 1;
		}
		else if(keytmp[key][i] == 0x00)
		{
			keynow[key][i] = 0;
		}
		else {}
	}
	for(i=0;i<4;i++)
	{
		//短按控制
		if(keynow[key][i]!=keyold[key][i])
		{
			//if(keynow[key][i]==1 && keyold[key][i]==0)
			//这样就变成松手检测了
			if(keynow[key][i]==0)
			{
				keyaction16(keymap[key][i]);
			}
			keyold[key][i]=keynow[key][i];
		}
	}
	
//	if(keynow[0][1] == 0 && keynow[1][1] == 0)
//		count++;
//	if(count>600) {init_flag = 1; count = 0;}
	
	if(key == 3) key = 0;
	else key++;
}
