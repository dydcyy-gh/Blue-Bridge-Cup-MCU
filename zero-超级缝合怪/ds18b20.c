#include <STC15F2K60S2.H>
#include "onewire.h"
#include "typedef.h"

//用到的rom命令
#define skip_rom 0xcc
//用到的功能命令
#define convent_t 0x44
#define read_scratchpad 0xbe

//简单读取函数~
float ds18b20_read_tempeture()
{
	u16 temp;
	float tempeture;
	u8 low,high;
	//convent_t
	init_ds18b20();
	Write_DS18B20(skip_rom);
	Write_DS18B20(convent_t);
	Delay_OneWire(200);//2ms
	//read_scratchpad
	init_ds18b20();
	Write_DS18B20(skip_rom);
	Write_DS18B20(read_scratchpad);
	
	low = Read_DS18B20();
	high = Read_DS18B20();
	
	//整合数据，0.0625精度
	if(high>10)//负数
	{
		high &= 0x07;
		temp = (high<<8)|low;
	    tempeture = -(temp*0.0625);
	}
	else
	{
		temp = (high<<8)|low;
		tempeture = temp*0.0625;
	}

	return tempeture;
}

//温度在数码管显示(ctrl.c)
void ds18b20_show()
{
	float temp;
	u32 te;
	temp = ds18b20_read_tempeture();
	if(temp<0) {shumatmp[0]=0xbf; temp = 0-temp;}
	te = (u32)(temp*10000);
	shumatmp[0]=te/1000000;
	shumatmp[1]=te%1000000/100000;
	shumatmp[2]=te%100000/10000;
	//加小数点
	shumatmp[4]=te%10000/1000;
	shumatmp[5]=te%1000/100;
	shumatmp[6]=te%100/10;
	shumatmp[7]=te%10;
}
