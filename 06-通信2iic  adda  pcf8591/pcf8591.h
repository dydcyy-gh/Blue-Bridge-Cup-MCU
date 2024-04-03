#include "typedef.h"

#ifndef __PCF8591_H__
#define __PCF8591_H__

u8 adc(u8 addr);
void dac(u8 DAC_Value);
u8 adda(u8 addr,u8 DAC);

#endif