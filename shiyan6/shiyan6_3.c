//12MHz 秒表
#include <reg51.h>
sbit P2_0=P2^0;
sbit P2_1=P2^1;
sbit P2_2=P2^2;
sbit P2_3=P2^3;
sbit P2_4=P2^4;
sbit P2_5=P2^5;
sbit dot=P1^7;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char d1=0,d2=0,d3=0,d4=0;
unsigned int time=0;
unsigned int num=0;

void delay(unsigned char cnt)		//延时子程序
{
	unsigned int i;
	do
	{
		for(i=0;i<165;i++);
	}while(--cnt);
}

void time1() interrupt 3 //定时器/计数器T1溢出中断
{
	time++;
	if(time==4000)
	{
		if(d4++==9)
		{
			d4=0;
			if(d3++==5)
			{
				d3=0;d4=0;
				if(d2++==9)
				{
					d2=0;
					if(d1++==5)
					{
						d1=0,d2=0,d3=0,d4=0;
					}
				}
			}
		}
	time=0;
	}
}

void display(void)
{	
	P2&=0xf0;		//关断位选信号
	P1=table[d1];	//送显示数据
	P2_0=1;		//选中第一个数码管
	delay(2);		//延时
	P2&=0xf0; 		//关断位选信号
	P1=table[d2];	//送显示数据
	dot=1;			//显示小数点
	P2_1=1; ;		//选中第二个数码管
	delay(2);		//延时
	P2&=0xf0;		//关断位选信号
	P1=table[d3];	//送显示数据
	P2_2=1;		//选中第三个数码管
	delay(2);		//延时
	P2&=0xf0; 		//关断位选信号
	P1=table[d4];	//送显示数据
	P2_3=1; ;		//选中第四个数码管
	delay(2);		//延时
	P1=0;		//关段码
	P2&=0xf0;	//关位码
}

main()
{
	TMOD=0x20;//写入方式控制字
	TH1=(256-250);//写入计数初值
	TL1=(256-250);
	EA=1;//开中断总开关
	ET1=1;//定时器1允许中断
	while(1)
	{
		/********************启动/暂停功能********************/
		if(P2_4==0)
		{											//第一次检测到按键信息
			delay(30);					//延时约20ms，消除抖动
			if(P2_4==0)
			{										//第二次检测到按键信息
				if(num%2==0)
					TR1=1;//启动T1定时
				else
				TR1=0;//关闭T1定时
				num++;
				if(num==10) num=0;
				while(P2_4==0)		//等待按键释放
				{display();}
			}
		}
		/**********************复位**********************/
		if(P2_5==0)
		{											//第一次检测到按键信息
			delay(30);					//延时约20ms，消除抖动
			if(P2_5==0)
			{										//第二次检测到按键信息
				d1=0;d2=0;d3=0;d4=0;
				TR1=0;
				num=0;
				while(P2_5==0)		//等待按键释放
				{display();}
			}
		}
		display();
	}
}