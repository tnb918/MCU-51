#include <reg51.h>
sbit P2_0=P2^0;
sbit P2_1=P2^1;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char d1=2,d2=4;
unsigned int time=0;
unsigned int run=0;
void delay(unsigned int i)
{
	unsigned int j;
	while(i--)
	{
		for(j=0;j<120;j++);
	}
}

void time1() interrupt 3 //定时器/计数器T1溢出中断
{
	time++;
	if(time==4000)
	{
		if(d2--==0)
		{
			d2=9;
			if(d1--==0)
			{d1=0;d2=0;}
		}
		time=0;
	}
}

void int1() interrupt 2 //外部1中断 复位24
{
	d1=2;
	d2=4;
	TR1=0;
	time=0;
	run=0;
}

void int0() interrupt 0 //外部0中断 启动/暂停键
{
	if(run%2==0)
		TR1=1;//启动T1定时
	else
		TR1=0;//关闭T1定时
	run++;
	if(run==10) run=0;
}

void display(void)
{	
	P2&=0xfc;		//关断位选信号
	P1=table[d1];	//送显示数据
	P2_0=1;		//选中第一个数码管
	delay(2);		//延时
	P2&=0xfc; 		//关断位选信号
	P1=table[d2];	//送显示数据
	P2_1=1; ;		//选中第二个数码管
	delay(2);		//延时
	P1=0;		//关段码
	P2&=0xfc;	//关位码
}


void main(void) 
{ 
	TMOD=0x20;//写入方式控制字
	TH1=(256-250);//写入计数初值
	TL1=(256-250);
	EA=1;//开中断总开关
	EX1=1;//允许外部1中断
	EX0=1;//允许外部0中断
	IT1=1;
	IT0=1;//负跳沿产生中断
	ET1=1;//定时器1允许中断

	while(1)
	{
		display();
	}
} 
