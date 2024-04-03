#include <STC15F2K60S2.H>
#include "typedef.h"

sbit IR_INPUT = P1^1;

bit irflag = 0;
u8 ircode[4];

void InitInfrared()
{
 	IR_INPUT = 1;
	AUXR &= 0xBF;
	TMOD &= 0x0F;
	TMOD |= 0x10;
	TR1 = 0;
	ET1 = 0;
}

u16 GetHighTime()
{
 	TH1 = 0;
	TL1 = 0;
	TR1 = 1;
	while(IR_INPUT)
	{
	 	if(TH1 >= 0x46)
		{
		 	break;
		}
	}
	TR1 = 0;

	return (TH1*256 + TL1);
}

u16 GetLowTime()
{
 	TH1 = 0;
	TL1 = 0;
	TR1 = 1;
	while(!IR_INPUT)
	{
	 	if(TH1 >= 0X46)
		{
		 	break;
		}
	}
	TR1 = 0;

	return (TH1*256 + TL1);
}

void IRScan()//12m晶振
{
 	u8 i, j;
	u8 byt;
	u16 time;

	time = GetLowTime();
	if((time<8500) || (time>9500))
	{
		return; 	
	}

	time = GetHighTime();
	if((time<4000) || (time>5000))
	{
	 	return;	
	}

	for(i=0; i<4; i++)
	{
		for(j=0; j<8; j++)
		{
		 	time = GetLowTime();
			if((time<340) || (time>780))
			{
			 	return;
			}

			time = GetHighTime();
			if((time>340) && (time<780))
			{
			 	byt >>= 1;
			}
			else if((time>1460) && (time<1900))
			{
				byt >>= 1;
				byt |= 0x80;
			}
			else
			{
			 	return;
			}
		}
		ircode[i] = byt;
	}
	irflag = 1;
}

//void IRScan()//11.0592m晶振
//{
// 	u8 i, j;
//	u8 byt;
//	u16 time;

//	time = GetLowTime();
//	if((time <7833) || (time > 8755))	   
//	{
//		return;	
//	}

//	time = GetHighTime();
//	if((time<3686) || (time > 4608))
//	{
//		return;
//	}
//	for(i=0; i<4; i++)
//	{
//		for(j=0; j<8; j++)
//		{
//			time = GetLowTime();
//			if((time<313) ||(time >718))
//			{
//				return;
//			}
//			time = GetHighTime();
//			if((time>313) && (time <718))
//			{
//				byt >>= 1;	
//			}
//			else if((time>1345) && (time<1751))
//			{
//				byt >>= 1;
//				byt |= 0x80;
//			}
//			else
//			{
//				return;
//			}
//		}
//		ircode[i] = byt;
//	}
//	irflag = 1;
//}
