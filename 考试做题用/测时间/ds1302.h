#include "typedef.h"

#ifndef __DS1302_H__
#define __DS1302_H__

void Write_Ds1302_Byte( u8 address,u8 dat );
u8 Read_Ds1302_Byte ( u8 address );
void DS1302_SetTime(void);
void DS1302_ReadTime(void);

#endif
