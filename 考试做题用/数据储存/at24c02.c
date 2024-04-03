#include <STC15F2K60S2.H>
#include "iic.h"
#include "typedef.h"

#define ADDRESS	0xA0//at24c02写地址

//iicstart--iicstop 5ms延迟，但单字节读写不用
//（上电时间已大于）5ms

void Delay5ms(void)	//@11.0592MHz
{
	unsigned char data i, j;

	i = 54;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

//AT24C02字节写
void AT24C02_WriteByte(u8 Ad,u8 Data)
{
	I2CStart();
	I2CSendByte(ADDRESS);
	I2CWaitAck();
	I2CSendByte(Ad);
	I2CWaitAck();
	I2CSendByte(Data);
	I2CWaitAck();
	I2CStop();
	Delay5ms();	//如果连续操作iic还是延时一下
}

//AT24C02字节读
u8 AT24C02_ReadByte(u8 Ad)
{
	u8 Data;
	I2CStart();
	I2CSendByte(ADDRESS);
	I2CWaitAck();
	I2CSendByte(Ad);
	I2CWaitAck();
	I2CStart();
	I2CSendByte(ADDRESS|0x01);
	I2CWaitAck();
	Data=I2CReceiveByte();
	I2CSendAck(1);
	I2CStop();
	Delay5ms();
	return Data;
}

//注：at24c02可以读写所有字符(包括\n\r\0)

//at24c02页写地址：
//第一页 0x00 ~ 0x07  第二页 0x08 ~ 0x0F  以此类推

//连续页写函数
void EEPROM_Write(u8 Ad, u8 *p, u8 lens)//页写入
{
	while(lens > 0)//页循环，循环的是页数
	{
		I2CStart();
		I2CSendByte(ADDRESS);
	    I2CWaitAck();
		I2CSendByte(Ad);
	    I2CWaitAck();
		while(lens > 0)//循环写入1页数据
		{
			I2CSendByte(*p++); //p为源数据指针
			I2CWaitAck();
			Ad++;			
			lens--;
			if((Ad & 0x07) == 0)//判断地址是否达到页边界，24C02每页8字节
				break;//如果达到一页的边界，就跳出该页写数据的循环，然后写下一页
		}
		I2CStop();
		Delay5ms();
	}
}

//连续读函数
void EEPROM_Read(u8 Ad, u8 *p, u8 lens)     
{
	I2CStart();              
	I2CSendByte(ADDRESS);    
	I2CWaitAck();         
	I2CSendByte(Ad);       
	I2CWaitAck();                     

	I2CStart();  
	I2CSendByte(ADDRESS|0x01);
	I2CWaitAck();    
	while(lens--)
	{
		*p++ = I2CReceiveByte();
		if(lens)  I2CSendAck(0);
		else I2CSendAck(1);
	}
	I2CStop();  	//关闭总线
}