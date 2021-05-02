#include <reg51.h>
sbit dot=P1^7;
sbit P2_0=P2^0;
sbit P2_1=P2^1;
sbit P2_2=P2^2;
sbit oe=P2^3;
sbit eoc=P2^4;
sbit start=P2^5;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned long temp,num;
void delay(unsigned int i)
{
	unsigned int j;
	while(i--)
	{
		for(j=0;j<120;j++);
	}
}

void display()
{
	num=temp%10;
	P2&=0xf8;		//关断位选信号
	P1=table[num];	//送显示数据
	P2_2=1;		//选中第三个数码管
	delay(2);		//延时
	num=temp/10%10;
	P2&=0xf8;		//关断位选信号
	P1=table[num];	//送显示数据
	P2_1=1;		//选中第二个数码管
	delay(2);		//延时
	num=temp/100%10;
	P2&=0xf8;		//关断位选信号
	P1=table[num];	//送显示数据
	dot=1;
	P2_0=1;		//选中第一个数码管
	delay(2);	
	P1=0;		//关段码
	P2&=0xf8;	//关位码
}
	
void main()
{
	start=0;
	oe=0;
	start=1;
	start=0;
	while(1)
	{
		if(eoc==1)
		{
			oe=1;
			temp=P0;
			temp=temp*500/255;
			oe=0;
			display();
			start=1;
			start=0;
		}
	}
}