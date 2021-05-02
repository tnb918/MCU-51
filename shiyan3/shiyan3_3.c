#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit P1_0=P1^0; //定义变量P1_0为P1口最低位
uchar num=0;//用于统计按键次数
uint time=0; 
uint i=0;
uint high;//高电平中断次数
uint period;//一个周期中断次数
float k=0.5;//占空比k

void time1() interrupt 3 //定时器/计数器T1溢出中断
{
	if(++time==high)//高电平时间到
		P1_0=0;//输出0
	else if(time==period)//一个周期时间到
	{
		time=0;//中断次数重新计数
		P1_0=1;//输出1
	}
}

void int1() interrupt 2 //外部1中断
{
	k+=0.1;
	if(k==1.0)
		k=0.1;
}

void int0() interrupt 0 //外部0中断
{
	k=0.5;
	num++;
	if(num==4)//按键次数超过4次时，重新计数
	 num=0;
	time=0;
	P1_0=1;
}

main()//主函数
{
	TMOD=0x20;//写入方式控制字
	TH1=(256-50);//写入计数初值
	TL1=(256-50);
	EA=1;//开中断总开关
	EX1=1;//允许外部1中断
	EX0=1;//允许外部0中断
	IT1=1;
	IT0=1;//负跳沿产生中断
	ET1=1;//定时器1允许中断
	TR1=1;//启动T1定时
	P1_0=1;//P1.0口置1 
	while(1)//等待中断
	{
		switch(num)
		{
			case 0:period=20;break;//1kHz
			case 1:period=200;break;//100Hz
			case 2:period=2000;break;//10Hz
			case 3:period=20000;break;//1Hz
		}
		high=period*k;
	}
}