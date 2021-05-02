#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar code LED1[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//单灯左移
uchar code LED2[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};//单灯右移
uchar code LED3[]={0x03,0x0c,0x30,0xc0};//双灯左移
uchar code LED4[]={0x55,0xaa};//奇偶数灯交替闪烁
uchar num=0;//用于统计按键次数
void delay(uint cnt)//延时函数
{
	uint i;//定义计数器i
	do{
		for(i=0;i<6000;i++);
	}while(cnt--);
}

void int1() interrupt 2 //外部1中断
{
	num++;//按键次数加1
	if(num==4)//按键次数超过4次时，重新计数
		num=0;
}
main()//主函数
{
	EA=1;//开中断总开关
	EX1=1;//允许外部1中断
	IT1=1;//负跳沿产生中断
	while(1)//等待中断
	{
		uchar j;//定义计数器j
		if(num==0)//第一次按键，LED1模式
		{
			for(j=0;j<8;j++)
			{P1=LED1[j];
			delay(10);
			if(num!=0)break;}//按键次数发生改变，则立刻跳出此模式
		}
		if(num==1)//第二次按键，LED2模式
		{
			for(j=0;j<8;j++)
			{P1=LED2[j];
			delay(10);
			if(num!=1)break;}//按键次数发生改变，则立刻跳出此模式
		}
		if(num==2)//第三次按键，LED3模式
		{
			for(j=0;j<4;j++)
			{P1=LED3[j];
			delay(10);
			if(num!=2)break;}//按键次数发生改变，则立刻跳出此模式
		}
		if(num==3)//第四次按键，LED4模式
		{
			for(j=0;j<2;j++)
			{P1=LED4[j];
			delay(10);
			if(num!=3)break;}//按键次数发生改变，则立刻跳出此模式
		}
	}
}

