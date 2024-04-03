#include <STC15F2K60S2.H>

//打开蜂鸣器
void buzz()
{
	P2=(P2&0x1f)|0xa0;
	P06=1;//蜂鸣器
	P04=0;
	P2&=0x1f;
}

//打开继电器
void relay()
{
	P2=(P2&0x1f)|0xa0;
	P04=1;//继电器
	P06=0;
	P2&=0x1f;
}
