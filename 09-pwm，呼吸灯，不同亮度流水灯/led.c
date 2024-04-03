#include <STC15F2K60S2.H>
#include "typedef.h"

static u8 shift = 0x01;
u8 i = 0;//

//基础led
void led(u8 locate)//0亮
{
	P2=(P2&0x1f)|0x80;
	P0=locate;
	P2&=0x1f;
}

//led流水灯(中断调用）
void ledflow()
{
	static bit x = 0;
	
	P2=(P2&0x1f)|0x80;
	P0=~shift;
	if(x == 0)
	{
		shift <<= 1;
		i++;//
		if(shift == 0x80) x = 1;
	}
	else
	{
		shift >>= 1;
		i--;//
		if(shift == 0x01) x = 0;
	}
	P2&=0x1f;
}

//pwm计算函数  定时器10us（100000hz）
//max（最大精度）:建议10（T=100us）-100（T=1ms）
//ex（占空比）：Ton/T  ex/max
void pwm (u8 max,u8 ex)
{
	static u8 cnt = 0;
	if(cnt == ex)
	{
		led(0xff);
	}
	if(cnt < max)
		cnt++;
	else
	{
		led(~shift);
		cnt = 0;
	}
}


////动态亮度级别控制之水滴低落
//code u8 LightLevel[8]= {0,1,2,4,8,16,32,64}; //亮度等级
//code u8 LightTime[16]= {16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};//每一等级持续时间实现加速效果

//void main()
//{
//	u8 i,j,k;
//	u8 temp = 0, state, count;
//	
//	P2 = (P2&0x1F) | 0xA0;
//	P0 &= 0xAF;
//	P2 = P2&0x1F;
//	
//	P2 = (P2&0x1F) | 0x80;
//	P0 = 0xFF;
//	P2 = P2&0x1F;
//	
//	while(1)
//	{
//		//第一个水滴，逐渐变大！
//		for(i=0; i<64; i++)//i控制亮度等级
//		{
//			for(j=0; j<64; j++)//j控制每个等级的持续时间
//			{
//				P2 = (P2&0x1F) | 0x80;
//				P0 = 0xFE;
//				P2 = P2&0x1F;
//				
//				for(k=0; k<64; k++)//k确定亮度等级
//				{
//					if(k>i)
//					{
//						P2 = (P2&0x1F) | 0x80;
//						P0 = 0xFF;
//						P2 = P2&0x1F;
//					}
//				}
//			}
//		}
//		
//		//流动拖尾实现
//		for(state=0; state<16; state++)
//		{
//			for(count=0; count<=LightTime[state]; count++)
//			{//每一状态维持LightTime[state]个脉冲
//				for(j=0; j<64; j++)//总脉冲个数，控制总周期
//				{
//					temp = 0x00;
//					for(k=0; k<8; k++)
//					{
//						if(LightLevel[k] <= j)
//						{
//							temp |= (1<<k);//高电平持续时间
//						}
//					}
//					if(state <= 7)
//					{
//						P2 = (P2&0x1F) | 0x80;
//						P0 = ~((~temp) >> (7-state));
//						P2 = P2&0x1F;
//					}
//					else
//					{
//						P2 = (P2&0x1F) | 0x80;
//						P0 = ~((~temp) << (state-7));
//						P2 = P2&0x1F;
//					}
//				}
//			}
//		}
//	}
//}

