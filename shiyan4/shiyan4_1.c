#include <reg51.h>
unsigned int time=0;
unsigned char i,j;
void time1() interrupt 3
{
	time++;
	if(time==400)
	{
		SBUF=j;
		while(!TI);
		TI=0;
		j>>=1;
		if(j==0x00)  
			j=0x80;
		time=0;
	}
}
void main()
{
	SCON=0x00;//���ڹ����ڷ�ʽ0,��������
	TMOD=0x20;//д�뷽ʽ������
	TH1=0x06;//д�������ֵ
	TL1=0x06;
	EA=1;//�����ж�
	ET1=1;//��ʱ��1�����ж�
	TR1=1;//����T1��ʱ
	j=0x80;
	while(1);
}