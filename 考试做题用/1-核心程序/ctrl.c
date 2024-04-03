#include <STC15F2K60S2.H>
#include "typedef.h"
#include "16key.h"
#include "4key.h"
#include "shuma.h"

extern u8 shumatmp[];
u8 ledtmp[8]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

u8  key_s4_flag = 0;//界面切换
u8  key_s5_flag = 0;//回显切换
bit key_s8_flag = 0;//+1 
bit key_s9_flag = 0;//-1 

//所有变量都在这声明

//按键行为函数
void keyaction16(u8 i)
{
	switch(i)
	{
		case 4:
			
			break;
		
		case 5:
			
			break;
		
		case 8:
			
			break;
		
		case 9:
			
			break;
		
		default:
			break;
	}
}

//要实现什么功能就写什么函数

//led刷新
void led_scan()//@100ms @timer1
{
	u8 i;
	u8 x = 0x00;
	for(i=0;i<8;i++)
	{
		x |= (0x01<<i)&ledtmp[i];
	}
	P2=(P2&0x1f)|0x80;
	P0 = x;
	P2&=0x1f;
}

//led显示控制
void led_ctrl()//@100ms @timer1
{

}

//根据按键状态刷新状态，进行数码管显示
void shuma_exchange_ctrl()//@300ms @timer1
{
	
}
