#include <STC15F2K60S2.H>
#include <intrins.h>
#include "typedef.h"

//引脚定义
sbit SCK = P1^7;//sclk
sbit SDA = P2^3;//io
sbit RST = P1^3;//ce

//寄存器写入地址/指令定义
#define sec		0x80
#define min		0x82
#define hour	0x84
#define day 	0x86
#define month	0x88
#define week	0x8A
#define year	0x8C
#define wp		0x8E

u8 addr[]={year,month,day,hour,min,sec,week};

//时间数组，索引0~6分别为年、月、日、时、分、秒、星期
u8 time[]={19,11,16,12,59,55,6};

//发送一个字节到通信总线上（已给出）
void Write_Ds1302(u8 temp) 
{
	u8 i;
	for (i=0;i<8;i++)     	
	{ 
		SCK = 0;
		SDA = temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

//向某一寄存器中写入，address表示寄存器地址，dat为待写入字节（已给出）
void Write_Ds1302_Byte( u8 address,u8 dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

//从某一寄存器中读出一个字节，address表示寄存器地址（已给出）
u8 Read_Ds1302_Byte ( u8 address )
{
 	u8 i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}

//ds1302初始化并设置初始时间
void DS1302_SetTime(void)
{
	u8 i;
	RST=0;  _nop_();
	SCK=0;  _nop_();
	Write_Ds1302_Byte(wp,0x00);
	for(i=0;i<7;i++)
	{
		Write_Ds1302_Byte(addr[i], time[i]/10*16 + time[i]%10);
	}
	Write_Ds1302_Byte(wp,0x80);
}

//DS1302读取时间，数据会被读取到time数组中
void DS1302_ReadTime(void)
{
	u8 Temp,i;
	for(i=0;i<7;i++)
	{
		Temp = Read_Ds1302_Byte(addr[i]|0x01);
		time[i] = Temp/16*10+Temp%16;
	}
}
