//12MHz 78ms 
#include <reg51.h>
unsigned int num=0;
void time1() interrupt 3 //定时器/计数器T1溢出中断
{
	num++;
	if(num<=128) P1++;
	else P1--;
	if(num==382) 
	{num=0;P1=127;}
}
void main()
{
	TMOD=0x20;//写入方式控制字
	TH1=(256-204);//写入计数初值
	TL1=(256-204);
	EA=1;
	ET1=1;//定时器1允许中断
	TR1=1;//启动T1定时
	P1=127;
	while(1);
}