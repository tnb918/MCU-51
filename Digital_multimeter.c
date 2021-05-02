#include <reg51.h>
#include <string.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit RS=P2^0;//0-ָ�1-����
sbit RW=P2^1;//0-д��1-��
sbit E=P2^2;
sbit oe=P2^3;
sbit eoc=P2^4;
sbit start=P2^5;
sbit X1=P2^6;
sbit X2=P2^7;
sbit X3=P3^0;
sbit X4=P3^1;
sbit P3_4=P3^4;
sbit ADD1=P3^5;
sbit ADD2=P3^6;
sbit ADD3=P3^7;

uchar flag1=0;//�������ͱ�־λ
uchar flag2=0;//������λ��־λ

unsigned long temp,tempz;

void delay(uchar cnt)		//��ʱ�ӳ���
{
	unsigned int i;
	while(cnt--)
	{
		for(i=0;i<250;i++)
		{
			_nop_();_nop_();_nop_();_nop_();
		}
	}
}

/**************************************
LCDæ�źż�⣬æ����1����æ����0��д����ǰ���ô˺���
**************************************/
bit Check_Busy()
{
	bit result;
	uchar temp;	
	P0=0xff;
	RS=0;
	RW=1;
	E=1;
	temp=P0;	
	E=0;
	result=(bit)(temp&0x80);//���λΪ1��ʾ��æ
	return result;
}
/**************************************
LCD����д�뺯��
**************************************/
void Data_Write(uchar dataz)
{
	while(Check_Busy());
	RS=1;
	RW=0;
	P0=dataz;
	E=1;
	E=0;	//�����½���
}


/**************************************
LCDָ��д�뺯��
**************************************/
void Comd_Write(uchar comd)
{
	while(Check_Busy());
	RS=0;
	RW=0;
	P0=comd;
	E=1;
	E=0;

}

/**************************************
LCD��ʼ������
**************************************/
void Init_LCD()
{
	RS=0;
	E=0;
	Comd_Write(0x38);    //����16x2��ʾ��5x7����8λ���ݽӿ�
	Comd_Write(0x0c);    //����ʾ������ʾ��꣬����˸
	Comd_Write(0x06);    //����д��һ���ַ����ַָ��͹���һ��������ʾ���ƶ�
	Comd_Write(0x01);    //����ָ�����㣬��ʾ����
}


/**************************************
LCD��ʾ����
**************************************/
void Display_LCD(uchar x,uchar y,uchar *str)
{
	uchar addr;
	if(x==1)
	{
		addr=0x80+y;//��һ��yλ����ʾ
	}
	else
	{
		addr=0x80+0x40+y;//�ڶ���yλ����ʾ
	}
	Comd_Write(addr);//��addrλ�ÿ�ʼд
	while(*str!='\0')
	{
		Data_Write(*str++);
	}
}



uchar code table1[]="value= 0000.00V";
uchar data table2[]="value= 0000.00V";
uchar code table3[]="value= 00.000 A";
uchar data table4[]="value= 00.000 A";
uchar code table5[]="value= 00.000 K";
uchar data table6[]="value= 00.000 K";
uchar code bank[]="                ";//�����ʾ��ĳһ��
uchar err=0;//�����־

/***********************��������***********************/
void ERROR()
{
 	err=1;
}
/***********************����ʵ��ֵ***********************/
void cal(uchar times)
{
	if(flag1==0)
	{
		strcpy(table2,table1);//���ԭ����
		temp=tempz;//��ֹ���ݱ仯�����п��ޣ�
		temp=temp*times*500*1.0/255;//��ѹ�Ŵ�100��������ʾ������
		table2[8]=temp/10000%10+48;	//��	
		table2[9]=temp/1000%10+48;	//ǧ	
		table2[10]=temp/100%10+48;	//��	
		table2[12]=temp/10%10+48;		//ʮ
		table2[13]=temp%10+48;			//��			
	}
	if(flag1==1)
	{
		strcpy(table4,table3);
		temp=tempz;
		temp=temp*50000*1.0/(255*times);//��ѹ�Ŵ�10000��
		table4[8]=temp/10000%10+48;	
		table4[10]=temp/1000%10+48;	
		table4[11]=temp/100%10+48;	
		table4[12]=temp/10%10+48;	
	}
	if(flag1==2)
	{
		strcpy(table6,table5);
		temp=tempz;
		temp=temp*1.0/(255-temp)*times*500;
		table6[7]=temp/10000%10+48;			
		table6[8]=temp/1000%10+48;	
		table6[10]=temp/100%10+48;	
		table6[11]=temp/10%10+48;	
		table6[12]=temp%10+48;		
	}
}
/***********************�����ʾ����**********************/
void display()
{
	/***********************���ѹ***********************/
	if(flag1==0)
	{
		if(flag2==0)
		{						
			Display_LCD(1,0,"(0-5V)V_MEA:   ");	
			cal(1);
			err=0;
			if(temp>=500)
			{ERROR();}
		}
		if(flag2==1)
		{				
			Display_LCD(1,0,"(5-50V)V_MEA:  ");
			cal(10);
			err=0;
			if(temp>=5000)
			{ERROR();}			
		}
		if(flag2==2)
		{			
			Display_LCD(1,0,"(50-500V)V_MEA:");
			cal(100);
			err=0;
			if(temp>=50000)
			{ERROR();}			
		}
		if(err==1)
		{
			Display_LCD(2,0,bank);
			Display_LCD(2,0,"OVER RANGE!");
			delay(10);
			X1=0;X2=0;X3=0;X4=1;
		}
		else
		{
			Display_LCD(2,0,table2);
			delay(10);
		}
	}
	
	/***********************�����***********************/	
	if(flag1==1)
	{
		if(flag2==0)
		{					
			//Display_LCD(1,0,bank);	
			Display_LCD(1,0,"(0-50mA)A_MEA:  ");	
			cal(100);
			err=0;
			if(temp>=500)
			{ERROR();}
		}
		if(flag2==1)
		{
			//Display_LCD(1,0,bank);				
			Display_LCD(1,0,"(50-500mA)A_MEA:");
			cal(10);
			err=0;
			if(temp>=5000)
			{ERROR();}			
		}
		if(flag2==2)
		{
			//Display_LCD(1,0,bank);				
			Display_LCD(1,0,"(0.5-5A)A_MEA:  ");
			cal(1);
			err=0;
			if(temp>=50000)
			{ERROR();}			
		}
		if(err==1)
		{
			Display_LCD(2,0,bank);
			Display_LCD(2,0,"OVER RANGE!");
			delay(1);
			X1=0;X2=0;X3=0;X4=1;
		}
		else
		{
			//Display_LCD(2,0,bank);
			Display_LCD(2,0,table4);
			delay(10);
		}		
	}

	/***********************�����***********************/	
	if(flag1==2)
	{
		if(flag2==0)
		{					
			//Display_LCD(1,0,bank);	
			Display_LCD(1,0,"(0-500)R_MEA:   ");	
			cal(1);
			err=0;
			if(temp>=500)
			{ERROR();}
		}
		if(flag2==1)
		{
			//Display_LCD(1,0,bank);				
			Display_LCD(1,0,"(0.5-5K)R_MEA:  ");
			cal(10);
			err=0;
			if(temp>=5000)
			{ERROR();}			
		}
		if(flag2==2)
		{
			//Display_LCD(1,0,bank);				
			Display_LCD(1,0,"(5-50K)R_MEA:   ");
			cal(100);
			err=0;
			if(temp>=50000)
			{ERROR();}			
		}
		if(err==1)
		{
			Display_LCD(2,0,bank);
			Display_LCD(2,0,"OVER RANGE!");
			delay(1);
			X1=0;X2=0;X3=0;X4=1;
		}
		else
		{
			//Display_LCD(2,0,bank);
			Display_LCD(2,0,table6);
			delay(10);
		}		
	}	
}


/***********************ADת������**********************/
void A_D()
{
	start=0;
	oe=0;
	start=1;
	start=0;
	delay(1);
	if(eoc==1)//ADת������
	{
		oe=1;
		temp=P1;
		tempz=temp;
		oe=0;
		display();//LCD��Ļ��ʾ
		start=1;
		start=0;
	}
}


void int0() interrupt 0 //�ⲿ0�ж� �л���������
{	
	flag1++;
	if(flag1==3) flag1=0;
	flag2=0;err=0;X4=0;
}


void int1() interrupt 2 //�ⲿ1�ж� �л�������λ
{	
	flag2++;
	if(flag2==3) flag2=0;err=0;X4=0;
}


void main()
{
	Init_LCD();//LCD��ʼ��
	X1=0;X2=0;X3=0;X4=0;
	ADD1=0;ADD2=0;ADD3=0;
	EA=1;//���ж��ܿ���
	EX1=1;//�����ⲿ1�ж�
	EX0=1;//�����ⲿ0�ж�
	IT1=1;
	IT0=1;//�����ز����ж�
	Display_LCD(1,0," Welcome To Use ");
	Display_LCD(2,0,"  This Product  ");	
	delay(1000);
	while(1)
	{ 
		if(err==0)
		{
			switch(flag1)
			{
				case 0:ADD1=0,ADD2=0,ADD3=0;break;//ѡIN0
				case 1:ADD1=1,ADD2=0,ADD3=0;break;//ѡIN1
				case 2:ADD1=0,ADD2=1,ADD3=0;break;//ѡIN2
			}							
			switch(flag2)
			{
				case 0:X1=1,X2=0,X3=0;break;//��λ1
				case 1:X1=0,X2=1,X3=0;break;//��λ2
				case 2:X1=0,X2=0,X3=1;break;//��λ3
			}
			delay(10);			
			A_D();
		}	
		if(P3_4==0)
		{											//��һ�μ�⵽������Ϣ
			delay(10);					//��ʱԼ10ms����������
			if(P3_4==0)
			{										//�ڶ��μ�⵽������Ϣ 
				if(X4==1){
					switch(flag1)
					{
						case 0:ADD1=0,ADD2=0,ADD3=0;break;//ѡIN0
						case 1:ADD1=1,ADD2=0,ADD3=0;break;//ѡIN1
						case 2:ADD1=0,ADD2=1,ADD3=0;break;//ѡIN2
					}							
					switch(flag2)
					{
						case 0:X1=1,X2=0,X3=0;break;//��λ1
						case 1:X1=0,X2=1,X3=0;break;//��λ2
						case 2:X1=0,X2=0,X3=1;break;//��λ3
					}
					delay(10);
					A_D();X4=0;}
				while(P3_4==0);		//�ȴ������ͷ�
			}
		}
	}
}