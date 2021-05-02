//12MHz ��� �ж�
#include <reg51.h>
sbit P2_0=P2^0;
sbit P2_1=P2^1;
sbit P2_2=P2^2;
sbit P2_3=P2^3;
sbit P2_4=P2^4;
sbit P2_5=P2^5;
sbit P2_6=P2^6;
sbit P2_7=P2^7;
sbit dot=P1^7;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char d1=0,d2=0,d3=0,d4=0,d5=0,d6=0;
unsigned int time=0;
unsigned int num=0;
unsigned int flag=0;
unsigned int allow=0;
unsigned int anum=0;
void delay(unsigned char cnt)		//��ʱ�ӳ���
{
	unsigned int i;
	do
	{
		for(i=0;i<165;i++);
	}while(--cnt);
}
		
void int1() interrupt 2 //�ⲿ1�ж� ȷ����
{
	if(anum%2==0)
	{
		TR1=0;//�ر�T1��ʱ
		allow=1;
	}
	else
	{
		TR1=1;//����T1��ʱ
		allow=0;
	}
	anum++;
	if(anum==10) anum=0;
	
}

void int0() interrupt 0 //�ⲿ0�ж� �ı�ʱ����
{
	TR1=0;
	if(num++==2)
		num=0;
}

void time1() interrupt 3 //��ʱ��/������T1����ж�
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
	P2&=0xc0;		//�ض�λѡ�ź�
	P1=table[d1];	//����ʾ����
	P2_0=1;		//ѡ�е�һ�������
	delay(1);		//��ʱ
	
	P2&=0xc0; 		//�ض�λѡ�ź�
	P1=table[d2];	//����ʾ����
	dot=1;			//��ʾС����
	P2_1=1; ;		//ѡ�еڶ��������
	delay(2);		//��ʱ
	
	P2&=0xc0;		//�ض�λѡ�ź�
	P1=table[d3];	//����ʾ����
	P2_2=1;		//ѡ�е����������
	delay(1);		//��ʱ
	
	P2&=0xc0; 		//�ض�λѡ�ź�
	P1=table[d4];	//����ʾ����
	dot=1;			//��ʾС����
	P2_3=1; ;		//ѡ�е��ĸ������
	delay(1);		//��ʱ
	
	P2&=0xc0; 		//�ض�λѡ�ź�
	P1=table[d5];	//����ʾ����
	P2_4=1; ;		//ѡ�е���������
	delay(2);		//��ʱ
	
	P2&=0xc0; 		//�ض�λѡ�ź�
	P1=table[d6];	//����ʾ����
	P2_5=1; ;		//ѡ�е����������
	delay(1);		//��ʱ
	P1=0;		//�ض���
	P2&=0xc0;	//��λ��
}

void shezhi()
{
	/*****************��һ*****************/
	if(flag==1){
	if(num==0)//ʱ��һ����
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
	if(num==1)//�ּ�һ����
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
	if(num==2)//���һ����
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
	/*****************��һ*****************/
	if(flag==2){
	if(num==0)//ʱ��һ����
	{
		//P2&=0xc3;
		if(d2--==0)
		{
			d2=9;
			if(d1--==0)
			{d1=2;d2=3;}
		}		
	}
	if(num==1)//�ּ�һ����
	{
		//P2&=0xcc;
		if(d4--==0)
		{
			d4=9;
			if(d3--==0)
			{d3=5,d4=9;}
		}
	}
		if(num==2)//���һ����
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
	TMOD=0x20;//д�뷽ʽ������
	TH1=(256-250);//д�������ֵ
	TL1=(256-250);
	EA=1;//���ж��ܿ���
	EX1=1;//�����ⲿ1�ж�
	EX0=1;//�����ⲿ0�ж�
	IT1=1;
	IT0=1;//�����ز����ж�
	ET1=1;//��ʱ��1�����ж�
	TR1=1;
	while(1)
	{
		if(allow==1){
		/**********************ʵ�ּ�1**********************/
		if(P2_6==0)
		{											//��һ�μ�⵽������Ϣ
			delay(30);					//��ʱԼ20ms����������
			if(P2_6==0)
			{										//�ڶ��μ�⵽������Ϣ
				flag=1;
				shezhi();
				display();
				while(P2_6==0)		//�ȴ������ͷ�
				{display();}
			}
		}
		/**********************ʵ�ּ�1**********************/
		if(P2_7==0)
		{											//��һ�μ�⵽������Ϣ
			delay(30);					//��ʱԼ20ms����������
			if(P2_7==0)
			{										//�ڶ��μ�⵽������Ϣ
				flag=2;
				shezhi();
				display();
				while(P2_7==0)		//�ȴ������ͷ�
				{display();}
			}
		}}
		display();
	}
}