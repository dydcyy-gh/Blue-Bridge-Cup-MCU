#include "typedef.h"

#ifndef __CTRL_H__
#define __CTRL_H__

void keyaction16(u8 i);
void show_humidity();//all time @timer1
void start_reflash();//200ms @main
void show_time();//200ms @main
void set_tempeture_ctrl();//100ms @timer1
void record_fun();//100ms @timer1
void led_scan();//@100ms @timer1
void led_ctrl();//@100ms @timer1
void shuma_exchange_ctrl();//@300ms @timer1

#endif