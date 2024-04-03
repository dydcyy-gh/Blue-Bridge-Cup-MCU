#include "typedef.h"

#ifndef __AT24C02_H__
#define __AT24C02_H__

void AT24C02_WriteByte(u8 Ad,u8 Data);
u8 AT24C02_ReadByte(u8 Ad);
void EEPROM_Write(u8 Ad, u8 *p, u8 lens);//页写入
void EEPROM_Read(u8 Ad, u8 *p, u8 lens);
void Delay5ms(void);

#endif