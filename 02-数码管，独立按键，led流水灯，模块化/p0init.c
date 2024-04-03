#include <STC15F2K60S2.H>

//用于关闭p0口的所有外设
void p0init()
{
	//关闭led！  y4c
	P2=(P2&0x1f)|0x80;
	P0=0xff;
	P2&=0x1f;
	//关闭蜂鸣器继电器   y5c
	P2=(P2&0x1f)|0xa0;
	P06=0;//蜂鸣器
	P04=0;//继电器
	P2&=0x1f;
	//初始化数码管（全灭）
	P2=(P2&0x1f)|0xc0;  //y6c
	P0=0xff;
	P2&=0x1f;
	P2=(P2&0x1f)|0xe0;  //y7c
	P0=0xff;
	P2&=0x1f;
}