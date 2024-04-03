#ifndef __IIC_H__
#define __IIC_H__

void I2CStart(void);
void I2CStop(void);

//发送一字节
void I2CSendByte(unsigned char byt);
//接收一字节
unsigned char I2CReceiveByte(void);

//（发送字节后）接收
unsigned char I2CWaitAck(void);
//（接收字节后）发送
void I2CSendAck(unsigned char ackbit);

#endif