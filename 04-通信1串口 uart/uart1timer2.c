//串口发送(写)：单片机->其他设备（如电脑）
//串口接收(读)：其他设备->单片机

#include <STC15F2K60S2.H>
#include "typedef.h"

bit busysend;
bit busyreceive;

extern u8 Rxdata[30];//接收储存函数
u8 RxdataCnt;//状态记录+数组计数
u8 RxdataPre;//状态对照

//单片机发送一个字节
void SendData(u8 dat)
{
	while (busysend);
	busysend = 1;
	SBUF = dat;  //写数据到UART数据寄存器
}

//单片机接收一个字节
u8 ReceiveData()
{
	u8 dat;
	while (busyreceive);
	busyreceive = 1;
	dat = SBUF;
	return dat;
}

//单片机发送字符串
//u8 *p = "hello"
void SendString(u8 *s)
{
    while (*s != '\0')  // 检测字符串结束标志
    {
        SendData(*s++); // 发送当前字符
    }
}

//串口波特率生成器
void Uart1_Init(void)	//9600bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0xE6;			//设置定时初始值
	T2H = 0xFF;			//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
	ES = 1;				//使能串口1中断
	EA = 1;             //打开总中断（加上）
}

//定时器2中断函数，16位自动重装填
void timer2uart1() interrupt 4
{
	if (TI)				//检测串口1发送中断
	{
		TI = 0;			//清除串口1发送中断请求位
		busysend = 0;   //清忙标志（加上）
	}
	if (RI)				//检测串口1接收中断
	{
		Rxdata[RxdataCnt++] = SBUF;// 一定要在串口接收数据！！！
		RI = 0;			//清除串口1接收中断请求位
		busyreceive = 0;//清忙标志（加上）
	}
}

//不定字符接收函数，就是不知道为什么不能接收\0
u8 Uart_WaitRecive(void)
{
	if(RxdataCnt == 0) 						//如果接收计数为0, 则说明没有处于接收数据中，所以直接跳出，结束函数
	return 1;
	if(RxdataCnt == RxdataPre)				//如果上一次的值和这次相同，则说明接收完毕
	{ 
		RxdataCnt = 0;  					//清0接收计数
		return 0;							//返回接收完成标志
	}
	RxdataPre = RxdataCnt;					//置未相同
	return 1;								//返回接收未完成标志
}