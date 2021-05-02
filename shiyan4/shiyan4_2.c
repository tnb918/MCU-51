#include <reg51.h>
sbit P2_0=P2^0;
sbit P2_1=P2^1;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char d1=2,d2=4;
unsigned int time=0;
unsigned int run=0;
void delay(unsigned int i)
{
	unsigned int j;
	while(i--)
	{
		for(j=0;j<120;j++);
	}
}

void time1() interrupt 3 //��ʱ��/������T1����ж�
{
	time++;
	if(time==4000)
	{
		if(d2--==0)
		{
			d2=9;
			if(d1--==0)
			{d1=0;d2=0;}
		}
		time=0;
	}
}

void int1() interrupt 2 //�ⲿ1�ж� ��λ24
{
	d1=2;
	d2=4;
	TR1=0;
	time=0;
	run=0;
}

void int0() interrupt 0 //�ⲿ0�ж� ����/��ͣ��
{
	if(run%2==0)
		TR1=1;//����T1��ʱ
	else
		TR1=0;//�ر�T1��ʱ
	run++;
	if(run==10) run=0;
}

void display(void)
{	
	P2&=0xfc;		//�ض�λѡ�ź�
	P1=table[d1];	//����ʾ����
	P2_0=1;		//ѡ�е�һ�������
	delay(2);		//��ʱ
	P2&=0xfc; 		//�ض�λѡ�ź�
	P1=table[d2];	//����ʾ����
	P2_1=1; ;		//ѡ�еڶ��������
	delay(2);		//��ʱ
	P1=0;		//�ض���
	P2&=0xfc;	//��λ��
}


void main(void) 
{ 
	TMOD=0x20;//д�뷽ʽ������
	TH1=(256-250);//д�������ֵ
	TL1=(256-250);
	EA=1;//���ж��ܿ���
	EX1=1;//�����ⲿ1�ж�
	EX0=1;//�����ⲿ0�ж�
	IT1=1;
	IT0=1;//�����ز����ж�
	ET1=1;//��ʱ��1�����ж�

	while(1)
	{
		display();
	}
} 
