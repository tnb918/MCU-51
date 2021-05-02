#include<reg51.h>
void int1() interrupt 2 //外部1中断
{
	P1=(P1>>7)|(P1<<1);//P1口实现循环左移
}
main()//主函数
{
	P1=0x01;//对P1口赋初值
	EA=1;//开中断总开关
	EX1=1;//允许外部1中断
	IT1=1;//负跳沿产生中断
	while(1);//等待中断
}