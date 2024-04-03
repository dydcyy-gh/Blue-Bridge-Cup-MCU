#include "typedef.h"

#ifndef __UART1TIMER2_H__
#define __UART1TIMER2_H__

void uart1init();

void SendData(u8 dat);
void SendString(u8 *s);

u8 ReceiveData();
u8 Uart_WaitRecive();
	
#endif