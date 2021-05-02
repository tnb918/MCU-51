//12MHz ���
#include <reg51.h>
sbit P2_0=P2^0;
sbit P2_1=P2^1;
sbit P2_2=P2^2;
sbit P2_3=P2^3;
sbit P2_4=P2^4;
sbit P2_5=P2^5;
sbit dot=P1^7;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char d1=0,d2=0,d3=0,d4=0;
unsigned int time=0;
unsigned int num=0;

void delay(unsigned char cnt)		//��ʱ�ӳ���
{
	unsigned int i;
	do
	{
		for(i=0;i<165;i++);
	}while(--cnt);
}

void time1() interrupt 3 //��ʱ��/������T1����ж�
{
	time++;
	if(time==4000)
	{
		if(d4++==9)
		{
			d4=0;
			if(d3++==5)
			{
				d3=0;d4=0;
				if(d2++==9)
				{
					d2=0;
					if(d1++==5)
					{
						d1=0,d2=0,d3=0,d4=0;
					}
				}
			}
		}
	time=0;
	}
}

void display(void)
{	
	P2&=0xf0;		//�ض�λѡ�ź�
	P1=table[d1];	//����ʾ����
	P2_0=1;		//ѡ�е�һ�������
	delay(2);		//��ʱ
	P2&=0xf0; 		//�ض�λѡ�ź�
	P1=table[d2];	//����ʾ����
	dot=1;			//��ʾС����
	P2_1=1; ;		//ѡ�еڶ��������
	delay(2);		//��ʱ
	P2&=0xf0;		//�ض�λѡ�ź�
	P1=table[d3];	//����ʾ����
	P2_2=1;		//ѡ�е����������
	delay(2);		//��ʱ
	P2&=0xf0; 		//�ض�λѡ�ź�
	P1=table[d4];	//����ʾ����
	P2_3=1; ;		//ѡ�е��ĸ������
	delay(2);		//��ʱ
	P1=0;		//�ض���
	P2&=0xf0;	//��λ��
}

main()
{
	TMOD=0x20;//д�뷽ʽ������
	TH1=(256-250);//д�������ֵ
	TL1=(256-250);
	EA=1;//���ж��ܿ���
	ET1=1;//��ʱ��1�����ж�
	while(1)
	{
		/********************����/��ͣ����********************/
		if(P2_4==0)
		{											//��һ�μ�⵽������Ϣ
			delay(30);					//��ʱԼ20ms����������
			if(P2_4==0)
			{										//�ڶ��μ�⵽������Ϣ
				if(num%2==0)
					TR1=1;//����T1��ʱ
				else
				TR1=0;//�ر�T1��ʱ
				num++;
				if(num==10) num=0;
				while(P2_4==0)		//�ȴ������ͷ�
				{display();}
			}
		}
		/**********************��λ**********************/
		if(P2_5==0)
		{											//��һ�μ�⵽������Ϣ
			delay(30);					//��ʱԼ20ms����������
			if(P2_5==0)
			{										//�ڶ��μ�⵽������Ϣ
				d1=0;d2=0;d3=0;d4=0;
				TR1=0;
				num=0;
				while(P2_5==0)		//�ȴ������ͷ�
				{display();}
			}
		}
		display();
	}
}