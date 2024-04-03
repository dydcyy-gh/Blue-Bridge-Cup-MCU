#include <STC15F2K60S2.H>
#include <stdlib.h>
#include <string.h>
#include "at24c02.h"
#include "uart1timer2.h"
#include "typedef.h"

u8 Sxdata[30];
u8 Rxdata[30];

void test1();
void test2();

void main()
{
	uart1init(); 
	while(1)
	{
		test2();
		Delay5ms();
	}		
}

void test1()//单字节测试函数
{
	static u8 a;
	a = ReceiveData();//单片机接收一个字节
	AT24C02_WriteByte(0x00,a);//AT24C02字节写
	SendData(AT24C02_ReadByte(0x00));//AT24C02字节读
}

void test2() // 多字节测试函数
{
    if (Uart_WaitRecive()==0) {
        u8 lens = strlen(Rxdata) + 1; // 获取字符串长度
        if (lens!= 0) {
            EEPROM_Write(0x00, Rxdata, lens); // 连续页写函数 
            EEPROM_Read(0x00, Sxdata, lens); // 连续读函数
            SendString(Sxdata);
        }
    }
}

 