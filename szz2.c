//12MHz 秒表
#include <reg51.h>
sbit P2_0=P2^0;
sbit P2_1=P2^1;
sbit P2_2=P2^2;
sbit P2_3=P2^3;
sbit P2_4=P2^4;
sbit P2_5=P2^5;
sbit P2_6=P2^6;
sbit P2_7=P2^7;
sbit P3_0=P3^0;
sbit P3_1=P3^1;
sbit dot=P1^7;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char d1=0,d2=0,d3=0,d4=0,d5=0,d6=0;
unsigned int time=0;
unsigned int num=0;
unsigned int flag=0;
unsigned int allow=1;
unsigned int anum=0;
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
		if(d6++==9)
		{
			d6=0;
			if(d5++==5)
			{
				d5=0;
				if(d4++==9)
				{
					d4=0;
					if(d3++==5)
					{
						d3=0;
						if(d1!=2)
						{
							if(d2++==9)
							{
								d2=0;
								d1++;
							}
						}
						else if(d2++==3)
						{
							d1=0;d2=0;
						}
					}
				}
			}
		}
	time=0;
	}
}

void display(void)
{	
	P2&=0xc0;		//关断位选信号
	P1=table[d1];	//送显示数据
	P2_0=1;		//选中第一个数码管
	delay(1);		//延时
	
	P2&=0xc0; 		//关断位选信号
	P1=table[d2];	//送显示数据
	dot=1;			//显示小数点
	P2_1=1; ;		//选中第二个数码管
	delay(2);		//延时
	
	P2&=0xc0;		//关断位选信号
	P1=table[d3];	//送显示数据
	P2_2=1;		//选中第三个数码管
	delay(1);		//延时
	
	P2&=0xc0; 		//关断位选信号
	P1=table[d4];	//送显示数据
	dot=1;			//显示小数点
	P2_3=1; ;		//选中第四个数码管
	delay(1);		//延时
	
	P2&=0xc0; 		//关断位选信号
	P1=table[d5];	//送显示数据
	P2_4=1; ;		//选中第五个数码管
	delay(2);		//延时
	
	P2&=0xc0; 		//关断位选信号
	P1=table[d6];	//送显示数据
	P2_5=1; ;		//选中第六个数码管
	delay(1);		//延时
	P1=0;		//关段码
	P2&=0xc0;	//关位码
}

void shezhi()
{
	/*****************加一*****************/
	if(flag==1){
	if(num==0)//时加一操作
	{
		//P2&=0xc3;
		if(d1!=2)
			{
				if(d2++==9)
					{
						d2=0;
						d1++;
					}
			}
		else if(d2++==3)
			{
				d1=0;d2=0;
			}
	}
	if(num==1)//分加一操作
	{
		//P2&=0xcc;
		if(d4++==9)
		{
			d4=0;
			if(d3++==5)
			{
				d3=0;
			}
		}
	}
	if(num==2)//秒加一操作
	{
		//P2&=0xf0;
		if(d6++==9)
		{
			d6=0;
			if(d5++==5)
			{
				d5=0;
			}
		}
	}}
	/*****************减一*****************/
	if(flag==2){
	if(num==0)//时减一操作
	{
		//P2&=0xc3;
		if(d2--==0)
		{
			d2=9;
			if(d1--==0)
			{d1=2;d2=3;}
		}		
	}
	if(num==1)//分减一操作
	{
		//P2&=0xcc;
		if(d4--==0)
		{
			d4=9;
			if(d3--==0)
			{d3=5,d4=9;}
		}
	}
		if(num==2)//秒减一操作
	{
		//P2&=0xf0;
		if(d6--==0)
		{
			d6=9;
			if(d5--==0)
			{d5=5,d6=9;}
		}
	}}	
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
		/**********************确定键**********************/
		if(P2_6==0)
		{											//第一次检测到按键信息
			delay(20);					//延时消除抖动
			if(P2_6==0)
			{										//第二次检测到按键信息
				if(anum%2==0)
					{
						TR1=1;//启动T1定时
						allow=0;
					}
				else
					{
						TR1=0;//关闭T1定时
						allow=1;
					}
				anum++;
				if(anum==10) anum=0;
				while(P2_6==0)  	//等待按键释放
				{display();}
			}
		}
		/**********************控制改变时分秒**********************/
		if(P2_7==0)
		{											//第一次检测到按键信息
			delay(20);					//延时消除抖动
			if(P2_7==0)
			{										//第二次检测到按键信息
				if(num++==2)
					num=0;
				while(P2_7==0)		//等待按键释放
				{display();}
			}
		}		
		if(allow==1){
		/**********************实现加1**********************/
		if(P3_0==0)
		{											//第一次检测到按键信息
			delay(20);					//延时消除抖动
			if(P3_0==0)
			{										//第二次检测到按键信息
				flag=1;
				shezhi();
				while(P3_0==0)		//等待按键释放
				{display();}
			}
		}
		/**********************实现减1**********************/
		if(P3_1==0)
		{											//第一次检测到按键信息
			delay(20);					//延时消除抖动
			if(P3_1==0)
			{										//第二次检测到按键信息
				flag=2;
				shezhi();
				while(P3_1==0)		//等待按键释放
				{display();}
			}
		}}
		display();
	}
}