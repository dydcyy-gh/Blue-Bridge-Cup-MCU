#include <STC15F2K60S2.H>
#include "iic.h"
#include "typedef.h"

#define ADDRESS	0x90//pcf8591写地址

//AD：模拟（外设）（电压）->数字（计算机）
	//AIN0: 右边排针  channel 0  0x00
	//AIN1: 光敏电阻  channel 1  0x01
	//AIN2: 放大器    channel 2  0x02
	//AIN3: 滑动变阻器channel 3  0x03
u8 adc(u8 addr)
{
	u8 ADC;
	I2CStart();	//发送IIC开始信号
	I2CSendByte(ADDRESS);	//发送写命令
	I2CWaitAck();
	I2CSendByte(addr); //写控制字
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(ADDRESS|0x01); //发送读命令			   
	I2CWaitAck();
	ADC=I2CReceiveByte();	//读入ADC值
	I2CStop();//产生停止信号    
	return ADC;
}


//               //
//ADC四路轮询程序
//               //


//DA：数字（计算机）->模拟（外设）（电压）
//输出DAC 0~255 to 0~5V
void dac(u8 DAC)
{
	I2CStart();	//发送IIC开始信号
	I2CSendByte(ADDRESS);	//发送写命令
	I2CWaitAck();
	I2CSendByte(0x40);  //写控制字:使能DAC输出
	I2CWaitAck();
	I2CSendByte(DAC);	//写DAC值
	I2CWaitAck();
	I2CStop();//产生停止信号
}

//获取ADC转换值,输出DAC
u8 adda(u8 addr,u8 DAC)
{
	u8 ADC;
	I2CStart();	//发送IIC开始信号
	I2CSendByte(ADDRESS);	//发送写命令
	I2CWaitAck();
	I2CSendByte(addr); //写控制字 010000XX（使能DAC）
	I2CWaitAck();
	I2CSendByte(DAC);	//写DAC值
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(ADDRESS|0X01); //发送读命令			   
	I2CWaitAck();
	ADC=I2CReceiveByte();	//读入ADC值
	I2CStop();//产生停止信号	    
	return ADC;
}