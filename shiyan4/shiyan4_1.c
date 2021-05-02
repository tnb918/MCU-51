#include <reg51.h>
unsigned int time=0;
unsigned char i,j;
void time1() interrupt 3
{
	time++;
	if(time==400)
	{
		SBUF=j;
		while(!TI);
		TI=0;
		j>>=1;
		if(j==0x00)  
			j=0x80;
		time=0;
	}
}
void main()
{
	SCON=0x00;//串口工作于方式0,发送数据
	TMOD=0x20;//写入方式控制字
	TH1=0x06;//写入计数初值
	TL1=0x06;
	EA=1;//开总中断
	ET1=1;//定时器1允许中断
	TR1=1;//启动T1定时
	j=0x80;
	while(1);
}