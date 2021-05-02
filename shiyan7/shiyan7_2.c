//12MHz 78ms 三角波
#include <reg51.h>
unsigned int num=0;
void time1() interrupt 3 //定时器/计数器T1溢出中断
{
	num++;
	if(num<=255) P1++;
	else P1--;
	if(num==510) num=0;
}
void main()
{
	TMOD=0x20;//写入方式控制字
	TH1=(256-153);//写入计数初值
	TL1=(256-153);
	EA=1;
	ET1=1;//定时器1允许中断
	TR1=1;//启动T1定时
	P1=0;
	while(1);
}