#include <reg51.h>
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
sbit P1_0=P1^0;
void delay(unsigned char cnt)		//��ʱ�ӳ���
{
	unsigned int i;
	do
	{
		for(i=0;i<165;i++);
	}while(--cnt);
}

void main()
{
	unsigned char k=0;
	P2=0x00;								//LED����ܳ�ʼ״̬ȫ��
	while(1)
	{
		if(P1_0==0)
		{											//��һ�μ�⵽������Ϣ
			delay(30);					//��ʱԼ20ms����������
			if(P1_0==0)
			{										//�ڶ��μ�⵽������Ϣ
				P2=table[k];			//LED��ʾ
				k++;				
				if(k==10) k=0;		//ʵ��ѭ����ʾ
				while(P1_0==0);		//�ȴ������ͷ�
			}
		}
	}
}