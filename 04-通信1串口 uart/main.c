//串口，定时器2
//串口发送(写)：单片机->其他设备（如电脑）
//串口接收(读)：其他设备->单片机
//本程序收发数据是从单片机的角度来的！

#include <STC15F2K60S2.H>
#include "typedef.h"
#include "uart1timer2.h"
 
u8 Rxdata[30] = {'\0'};

//主函数在这
void main()
{
	uart1init(); // 初始化串口
	while (1)
	{
		if (Uart_WaitRecive()==0)
		{
			SendString(Rxdata);
		}
	}
}
