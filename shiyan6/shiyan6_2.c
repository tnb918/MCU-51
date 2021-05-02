#include <reg51.h>
sbit P2_0=P2^0;
sbit P2_1=P2^1;
sbit P2_2=P2^2;
sbit P2_3=P2^3;
sbit P2_4=P2^4;
sbit P2_5=P2^5;
sbit P2_6=P2^6;
sbit P2_7=P2^7;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char d1=2,d2=0,d3=1,d4=9;

void delay(unsigned char cnt)		//延时子程序
{
	unsigned int i;
	do
	{
		for(i=0;i<165;i++);
	}while(--cnt);
}

void display(void)
{	
	P2&=0xf0;		//关断位选信号
	P1=table[d1];	//送显示数据
	P2_0=1;		//选中第一个数码管
	delay(2);		//延时
	P2&=0xf0; 		//关断位选信号
	P1=table[d2];	//送显示数据
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
	P2&=0xfc;	//关位码
}

main()
{
	while(1)
	{
		if(P2_4==0)
		{											//第一次检测到按键信息
			delay(30);					//延时约20ms，消除抖动
			if(P2_4==0)
			{										//第二次检测到按键信息
				d1++;				
				if(d1==10) d1=0;		//实现循环显示
				while(P2_4==0)		//等待按键释放
				{display();}
			}
		}
		if(P2_5==0)
		{											//第一次检测到按键信息
			delay(30);					//延时约20ms，消除抖动
			if(P2_5==0)
			{										//第二次检测到按键信息
				d2++;				
				if(d2==10) d2=0;		//实现循环显示
				while(P2_5==0)		//等待按键释放
				{display();}
			}
		}
		if(P2_6==0)
		{											//第一次检测到按键信息
			delay(30);					//延时约20ms，消除抖动
			if(P2_6==0)
			{										//第二次检测到按键信息
				d3++;				
				if(d3==10) d3=0;		//实现循环显示
				while(P2_6==0)		//等待按键释放
				{display();}
			}
		}
		if(P2_7==0)
		{											//第一次检测到按键信息
			delay(30);					//延时约20ms，消除抖动
			if(P2_7==0)
			{										//第二次检测到按键信息
				d4++;				
				if(d4==10) d4=0;		//实现循环显示
				while(P2_7==0)		//等待按键释放
				{display();}
			}
		}
		display();
	}
}