//12MHz 78ms ���ǲ�
#include <reg51.h>
unsigned int num=0;
void time1() interrupt 3 //��ʱ��/������T1����ж�
{
	num++;
	if(num<=255) P1++;
	else P1--;
	if(num==510) num=0;
}
void main()
{
	TMOD=0x20;//д�뷽ʽ������
	TH1=(256-153);//д�������ֵ
	TL1=(256-153);
	EA=1;
	ET1=1;//��ʱ��1�����ж�
	TR1=1;//����T1��ʱ
	P1=0;
	while(1);
}