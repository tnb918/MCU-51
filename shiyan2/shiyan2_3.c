#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar code LED1[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//��������
uchar code LED2[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};//��������
uchar code LED3[]={0x03,0x0c,0x30,0xc0};//˫������
uchar code LED4[]={0x55,0xaa};//��ż���ƽ�����˸
uchar num=0;//����ͳ�ư�������
void delay(uint cnt)//��ʱ����
{
	uint i;//���������i
	do{
		for(i=0;i<6000;i++);
	}while(cnt--);
}

void int1() interrupt 2 //�ⲿ1�ж�
{
	num++;//����������1
	if(num==4)//������������4��ʱ�����¼���
		num=0;
}
main()//������
{
	EA=1;//���ж��ܿ���
	EX1=1;//�����ⲿ1�ж�
	IT1=1;//�����ز����ж�
	while(1)//�ȴ��ж�
	{
		uchar j;//���������j
		if(num==0)//��һ�ΰ�����LED1ģʽ
		{
			for(j=0;j<8;j++)
			{P1=LED1[j];
			delay(10);
			if(num!=0)break;}//�������������ı䣬������������ģʽ
		}
		if(num==1)//�ڶ��ΰ�����LED2ģʽ
		{
			for(j=0;j<8;j++)
			{P1=LED2[j];
			delay(10);
			if(num!=1)break;}//�������������ı䣬������������ģʽ
		}
		if(num==2)//�����ΰ�����LED3ģʽ
		{
			for(j=0;j<4;j++)
			{P1=LED3[j];
			delay(10);
			if(num!=2)break;}//�������������ı䣬������������ģʽ
		}
		if(num==3)//���Ĵΰ�����LED4ģʽ
		{
			for(j=0;j<2;j++)
			{P1=LED4[j];
			delay(10);
			if(num!=3)break;}//�������������ı䣬������������ģʽ
		}
	}
}

