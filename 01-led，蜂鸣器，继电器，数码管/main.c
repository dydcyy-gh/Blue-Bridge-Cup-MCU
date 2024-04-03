#include <STC15F2K60S2.H>

typedef unsigned char u8; //0-255    0x00 - 0xff
typedef unsigned int u16; //0-65535  0x0000 - 0xffff
typedef unsigned long u32;

u8 T1H;
u8 T1L;

void p0init();
void led(u8 locate);
void buzz();
void relay();
void shuma(u8 locate,u8 number);
void timer1init(u8 ms);

//共阳数码管段码表(考试会给的吧)
u8 code LedChar[] = {
	0xC0, 0xF9, 0xA4, 0xB0,//0-3
	0x99, 0x92, 0x82, 0xF8,//4-7
	0x80, 0x90, 0x88, 0x83,//8-b
	0xC6, 0xA1, 0x86, 0x8E,//C-F
}; 

void main()
{
	p0init();
	timer1init(2);
	while(1)
	{
		
	}
}

//用于关闭p0口的所有外设
void p0init()
{
	//关闭led！  y4c
	P2=(P2&0x1f)|0x80;
	P0=0xff;
	P2&=0x1f;
	//关闭蜂鸣器继电器   y5c
	P2=(P2&0x1f)|0xa0;
	P06=0;//蜂鸣器
	P04=0;//继电器
	P2&=0x1f;
	//初始化数码管（全灭）
	P2=(P2&0x1f)|0xc0;  //y6c
	P0=0xff;
	P2&=0x1f;
	P2=(P2&0x1f)|0xe0;  //y7c
	P0=0xff;
	P2&=0x1f;
}

//基础led
void led(u8 locate)//0亮
{
	P2=(P2&0x1f)|0x80;
	P0=locate;
	P2&=0x1f;
}

//打开蜂鸣器
void buzz()
{
	P2=(P2&0x1f)|0xa0;
	P06=1;//蜂鸣器
	P04=0;//继电器
	P2&=0x1f;
}

//打开继电器
void relay()
{
	P2=(P2&0x1f)|0xa0;
	P04=1;//继电器
	P06=0;//蜂鸣器
	P2&=0x1f;
}


//数码管显示
void shuma(u8 locate,u8 number)
{
	//清零
	P2=(P2&0x1f)|0xe0;
	P0=0xff;
	P2&=0x1f;
	//数码管位选（1亮）   y6c
	P2=(P2&0x1f)|0xc0;
	P0=(0x01<<(locate-1));
	P2&=0x1f;
	//数码管段选（0亮）   y7c
	P2=(P2&0x1f)|0xe0;
	P0=LedChar[number];
	P2&=0x1f;
}


//定时器1 模式1 (16位自动重载)
//@12hz xms 12t (12分频) 低速模式
void timer1init(u8 ms)
{
	u32 tmp;
	//计算得出TL TH的值
	tmp = 12000000/12;  //每s 计数TMP次
	tmp = (tmp*ms)/1000;//每ms计数TMP次
	tmp = 65536 - tmp;
	T1H = (u8)(tmp>>8); //tmp / 256
	T1L = (u8)tmp;      //tmp % 256
	//AUXR在12t模式时可省略
	AUXR &= 0xBF;
	//TMOD
	TMOD &= 0x0F;    	//设置定时器模式
	//TH TL
	TH1 = T1H;	        //设置定时初始值
	TL1 = T1L;				
	//TCON
	TF1 = 0;			//清除TF0标志
	TR1 = 1;			//定时器0开始计时
	//interupt
	ET1 = 1;            //中断允许位
	EA = 1;             //cpu中断允许位
	PT1 = 0;            //优先级0(最低)
}

void interrupttimer1() interrupt 3
{
	static u8 count = 0;
    count++;
    switch(count)
    {
        case 1:
            shuma(1,1);
            break;
        case 2:
            shuma(2,2);
            break;
        case 3:
            shuma(3,3);
			count = 0;//最后一个case加
            break;
        // 添加更多的case
	}
}

