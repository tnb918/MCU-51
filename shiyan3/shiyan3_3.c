#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit P1_0=P1^0; //�������P1_0ΪP1�����λ
uchar num=0;//����ͳ�ư�������
uint time=0; 
uint i=0;
uint high;//�ߵ�ƽ�жϴ���
uint period;//һ�������жϴ���
float k=0.5;//ռ�ձ�k

void time1() interrupt 3 //��ʱ��/������T1����ж�
{
	if(++time==high)//�ߵ�ƽʱ�䵽
		P1_0=0;//���0
	else if(time==period)//һ������ʱ�䵽
	{
		time=0;//�жϴ������¼���
		P1_0=1;//���1
	}
}

void int1() interrupt 2 //�ⲿ1�ж�
{
	k+=0.1;
	if(k==1.0)
		k=0.1;
}

void int0() interrupt 0 //�ⲿ0�ж�
{
	k=0.5;
	num++;
	if(num==4)//������������4��ʱ�����¼���
	 num=0;
	time=0;
	P1_0=1;
}

main()//������
{
	TMOD=0x20;//д�뷽ʽ������
	TH1=(256-50);//д�������ֵ
	TL1=(256-50);
	EA=1;//���ж��ܿ���
	EX1=1;//�����ⲿ1�ж�
	EX0=1;//�����ⲿ0�ж�
	IT1=1;
	IT0=1;//�����ز����ж�
	ET1=1;//��ʱ��1�����ж�
	TR1=1;//����T1��ʱ
	P1_0=1;//P1.0����1 
	while(1)//�ȴ��ж�
	{
		switch(num)
		{
			case 0:period=20;break;//1kHz
			case 1:period=200;break;//100Hz
			case 2:period=2000;break;//10Hz
			case 3:period=20000;break;//1Hz
		}
		high=period*k;
	}
}