/*
f=6MHz，定时器/计数器T1，方式2，实现从P2.0口输出周期为120ms，占空比为（10+作业号58）%的波形。
*/
#include <reg51.h>
#define unchar unsigned char
sbit P2_0=P2^0;//定义变量P2_0为P2口最低位
unchar time=0;//中断次数
unchar period=250;//一个周期中断次数
unchar high=170;//高电平中断次数
main()
{
	TMOD=0x20;//写入方式控制字
	TH1=0x10;//写入计数初值
	TL1=0x10;
	EA=1;//开中断总开关
	ET1=1;//定时器1允许中断
	TR1=1;//启动T1定时
	P2_0=1;//P2.0口置1 
	while(1);//等待中断
}
time1() interrupt 3//定时器/计数器T1溢出中断
{
	if(++time==high)//中断次数到170次即高电平时间到
		P2_0=0;//输出0
	else if(time==period)//中断次数到250次即周期到
	{
		time=0;//中断次数重新计数
		P2_0=1;//输出1
	}
}