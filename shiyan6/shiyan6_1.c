#include <reg51.h>
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
sbit P1_0=P1^0;
void delay(unsigned char cnt)		//延时子程序
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
	P2=0x00;								//LED数码管初始状态全灭
	while(1)
	{
		if(P1_0==0)
		{											//第一次检测到按键信息
			delay(30);					//延时约20ms，消除抖动
			if(P1_0==0)
			{										//第二次检测到按键信息
				P2=table[k];			//LED显示
				k++;				
				if(k==10) k=0;		//实现循环显示
				while(P1_0==0);		//等待按键释放
			}
		}
	}
}