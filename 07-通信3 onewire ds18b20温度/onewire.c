//以下增加
#include <STC15F2K60S2.H>
sbit DQ = P1^4;
//温度读取时禁止中断（自己加）

//延时函数(此处可能有问题，需检查）
void Delay_OneWire(unsigned int t)  
{
	unsigned char i;
	while(t--){
		for(i=0;i<12;i++);
	}
}

//18b20初始化
bit init_ds18b20()
{
  	bit initflag = 0;
  	EA = 0;//禁止中断
  	DQ = 1;
  	Delay_OneWire(12);
  	DQ = 0;
  	Delay_OneWire(80);
  	DQ = 1;
  	Delay_OneWire(10); 
    initflag = DQ;     
  	Delay_OneWire(5);
	
	EA = 1;
  	return initflag;
}

//18b20字节写
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	EA = 0;//禁止中断
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_OneWire(5);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(5);
	EA = 1;
}

//18b20字节读
unsigned char Read_DS18B20()
{
	unsigned char i;
	unsigned char dat;
    EA = 0;//禁止中断
	for(i=0;i<8;i++)
	{
		DQ = 0;
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(5);
	}
	EA = 1;
	return dat;
}
