#include <STC15F2K60S2.H>
#include "typedef.h"
#include "16key.h"
#include "4key.h"
#include "shuma.h"
#include "timer1.h"
#include "ctrl.h"

bit u1flag = 0;
bit u2flag = 0;
bit u3flag = 0;
bit u4flag = 0;
bit u5flag = 0;
bit u6flag = 0;

void main()
{
	DS1302_SetTime();
	timer0init();
	timer1init(2);
	ds18b20_read_tempeture();
	while(1)
	{
		if(u1flag == 1)
		{
			u1flag = 0;
			
		}
		if(u2flag == 1)
		{
			u2flag = 0;
			
		}
		if(u3flag == 1)
		{
			u3flag = 0;
			
		}
		if(u4flag == 1)
		{
			u4flag = 0;
			
		}
		if(u5flag == 1)
		{
			u5flag = 0;
			led_scan();
			led_ctrl();
		}
		if(u6flag == 1)
		{
			u6flag = 0;
			shuma_exchange_ctrl();
		}
	}
}

//这里是定时器1中断函数（示例）
void interrupttimer1() interrupt 3
{
	static u8 count1=0;
	static u8 count2=0;
	static u8 count3=0;
	static u8 count4=0;
	static u8 count5=0;
	static u8 count6=0;
	count1++;
	count2++;
	count3++;
	count4++;
	count5++;
	count6++;
	if(count1>99)
		{count1=0;u1flag = 1;}
	if(count2>99)
		{count2=0;u2flag = 1;}
	if(count3>49)
		{count3=0;u3flag = 1;}
	if(count4>49)
		{count4=0;u4flag = 1;}
	if(count5>49)
		{count5=0;u5flag = 1;}
	if(count6>149)
		{count6=0;u6flag = 1;}
	shumascan();
	keyscan16();
}
