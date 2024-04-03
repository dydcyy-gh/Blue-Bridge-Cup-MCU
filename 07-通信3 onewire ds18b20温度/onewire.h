#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

void Delay_OneWire(unsigned int t);
bit init_ds18b20();
void Write_DS18B20(unsigned char dat);
unsigned char Read_DS18B20();

#endif