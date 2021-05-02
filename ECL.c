#include <reg51.h>
#include <string.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit RS=P2^0;//0-ָ�1-����
sbit RW=P2^1;//0-д��1-��
sbit E=P2^2;
sbit right=P2^3;//Ϊ1������ȷ������������

uchar code table1[]="Input Password:";
uchar code table2[]="Password Error!";
uchar code table3[]="Unclock Success!";
uchar code table4[]="Old Password:";
uchar code table5[]="New Password:";
uchar code table6[]="Password digits";
uchar code table7[]="should >5";
uchar code table8[]="Change Success!";

void delay(uchar cnt)		//��ʱ�ӳ���
{
	uint i;
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
	//Init_LCD();
	if(x==1)
	{
		addr=0x80+y;//��һ��yλ����ʾ
	}
	else
	{
		addr=0x80+0x40+y;//�ڶ���yλ����ʾ
	}
	//Comd_Write(0x02);
	Comd_Write(addr);//��addrλ�ÿ�ʼд
	while(*str!='\0')
	{
		Data_Write(*str++);
	}
}


/**************************************
ɨ��4X4���̺���
**************************************/
uchar scan()
{
	uchar temp;
	while(1){
	P1=0xf0;
	temp=P1;
	if(temp!=0xf0)
	{
		delay(30);
		temp=P1;
		if(temp!=0xf0)
		{
			/****************ɨ���һ��****************/
			P1=0xfe;
			temp=P1;
			if((temp&0xf0)!=0xf0)
			{
				switch(temp)
				{
					case 0xee:return '0';break;
					case 0xde:return '1';break;
					case 0xbe:return '2';break;
					case 0x7e:return '3';break;
					default:break;
				}
			}
			/****************ɨ��ڶ���****************/
			P1=0xfd;
			temp=P1;
			if((temp&0xf0)!=0xf0)
			{
				switch(temp)
				{
					case 0xed:return '4';break;
					case 0xdd:return '5';break;
					case 0xbd:return '6';break;
					case 0x7d:return '7';break;
					default:break;
				}
			}
			/****************ɨ�������****************/				
			P1=0xfb;
			temp=P1;
			if((temp&0xf0)!=0xf0)
			{
				switch(temp)
				{
					case 0xeb:return '8';break;
					case 0xdb:return '9';break;
					case 0xbb:return 'a';break;
					case 0x7b:return 'b';break;
					default:break;
				}
			}
			/****************ɨ�������****************/				
			P1=0xf7;
			temp=P1;
			if((temp&0xf0)!=0xf0)
			{
				switch(temp)
				{
					case 0xe7:return 'c';break;
					case 0xd7:return 'd';break;
					case 0xb7:return 'e';break;
					case 0x77:return 'f';break;
					default:break;
				}
			}
		}
		//while(temp!=0xf0);
	}	
}}

uchar data password[17]={'1','1','1','1','1','1','1','1'};//���ԭʼ���루�ɸģ�
uchar data passwordbf[17]={'1','1','1','1','1','1','1','1'};//���ԭʼ���루���ɸģ�
uchar data tem_password[17]={'\0'};//�������������бȽ�
uchar data new_password[17]={'\0'};	//���Ԥ�޸�����
uchar code bank[]="                ";//���LCDĳһ��
uchar data star[16];//���*��
/**************************************
��ʾnum��*���麯��
**************************************/
void stars(uchar num)
{
	uchar i;
	memset(star,0,sizeof(star));
	for(i=0;i<num;i++)
	{
		star[i]='*';
	}
}

/**************************************
������
**************************************/
/*uchar code table1[]="Input Password:";
uchar code table2[]="Password Error!";
uchar code table3[]="Unclock Success!";
uchar code table4[]="Old Password:";
uchar code table5[]="New Password:";
uchar code table6[]="Password digits";
uchar code table7[]="should >5";
uchar code table8[]="Change Success!";
*/

void main()
{
	uchar i;
	uchar time=1;
	uchar j=0,flag=0;
	uchar change=0;
	right=0;
	Init_LCD();//LCD��ʼ��
	Display_LCD(1,0,table1);
	for(j=0;;)
	{
		i=scan();//ɨ�����
		/**************************��������**************************/
		if(i>='0'&&i<='9'&&j<16)
		{
			if(change==0)
			{
				tem_password[j]=i;
			}
			if(change==1)
			{
				new_password[j]=i;
			}	
		  if(change==2)
			{
				password[j]=i;
			}	
			if(flag==0)
			{//����ʾ��ֵ����ʾ*��
				Display_LCD(2,j,"*");
			  delay(10);
			}
			else 
			{//��ʾ��ֵ���á�&�����뺯������
				Display_LCD(2,j,&i);
			  delay(10);
			}
			j++;
		}
		
		/**************************ȷ�������������**************************/		
		if(i=='a')
		{
			if(j<6)
		  {//����λ��С��6��ʾ����				
				Comd_Write(0x01);				
				Display_LCD(1,0,table6);
				Display_LCD(2,3,table7);
				delay(100);//������ʱ		
				Comd_Write(0x01);
				Display_LCD(1,0,table1);
				change=0;
				j=0;time=1;//������ʾ��������
				memset(tem_password,0,sizeof(tem_password));
				memset(new_password,0,sizeof(new_password));
				strcpy(password,passwordbf);//������ݣ������ó�ֵ
			}
			if(j>=6)
			{//����λ��������ڵ�����λ
				if(change==0)
				{
					tem_password[j+1]='\0';//�������
					if(strcmp(tem_password,password)==0)
					{//����������ȷ������һ��ʱ�䣬��ʾ�󷵻������������
						Comd_Write(0x01);
						Display_LCD(1,0,table3);
						right=1;
						delay(1000);
						right=0;
						Comd_Write(0x01);
						Display_LCD(1,0,table1);
						j=0;time=1;
						memset(tem_password,0,sizeof(tem_password));						
						}
					else
					{//�������������ʾ�󷵻������������
						Comd_Write(0x01);
						Display_LCD(1,0,table2);
						delay(1000);
						Comd_Write(0x01);
						Display_LCD(1,0,table1);		
						j=0;time=1;
					  memset(tem_password,0,sizeof(tem_password));				
					}
				}

				if(change==2)
				{//�����޸ĳɹ�����ʾ�󷵻������������
					password[j+1]='\0';
					Comd_Write(0x01);				
					Display_LCD(1,0,table8);
					delay(1000);
					Comd_Write(0x01);				
					Display_LCD(1,0,table1);
					delay(10);
					change=0;
					j=0;time=1;
				}
				if(change==1)
				{
					new_password[j+1]='\0';
					if(strcmp(new_password,password)==0)
					{//�޸�������֤ͨ�����������������빦��
						Comd_Write(0x01);				
						Display_LCD(1,0,table5);
						delay(1000);
						j=0;time=1;
						change=2;
						memset(new_password,0,sizeof(new_password));		
						memset(password,0,sizeof(password));						
					}
					else
					{//�޸�������֤ʧ�ܣ���ʾ�󷵻�������֤����
						Comd_Write(0x01);				
						Display_LCD(1,0,table2);
						delay(1000);
						Comd_Write(0x01);				
						Display_LCD(1,0,table4);
						j=0;time=1;
						memset(new_password,0,sizeof(new_password));	
					}				
				}				
			}

		}
		
		/**************************�س�ɾ�����һλ����**************************/
		if(i=='b')
		{
			if(j>0)
			{				
				j--;//������һλ����
				if(change==0)
				{
					tem_password[j]='\0';		
					delay(10);
				}
				if(change==1)
				{
					new_password[j]='\0';		
					delay(10);
				}		 
				if(change==2)
				{
					password[j]='\0';		
					delay(10);
				}								
				if(flag==1)
				{
					Display_LCD(2,0,bank);//���LCD�ڶ�������
					if(change==0)//��ʾ��Ӧ�����Ԫ��
					{
						Display_LCD(2,0,tem_password);
					}
					if(change==1)
					{
						Display_LCD(2,0,new_password);
					}
					if(change==2)
					{
						Display_LCD(2,0,password);
					}					
				}
				if(flag==0)
				{
					stars(j);
					Display_LCD(2,0,bank);//���LCD�ڶ�������
					Display_LCD(2,0,star);//��ʾj��*
				}
				/*
				Comd_Write(0x10);//�������1�񣬵�ֵַ�� 1
				Data_Write(' ');//ͨ����ʾ�հ�ʵ��ɾ�����һ����*��
				Comd_Write(0x10);
				*/
			}	
		}
		
		/**************************��ʾ/��������**************************/
		if(i=='c')
		{
			if(time%2==1)
			{
				if(change==0)
				{
					Display_LCD(2,0,tem_password); 			
					delay(10);
				}
				if(change==1)
				{
					Display_LCD(2,0,new_password); 			
					delay(10);
				}
				if(change==2)
				{
					Display_LCD(2,0,password); 			
					delay(10);
				}
				flag=1;	//��ʾ����			
			}
			else
			{
				stars(j);
				Display_LCD(2,0,bank);//���LCD�ڶ�������
				Display_LCD(2,0,star);//��ʾj��*
				delay(10);
				flag=0;//����ʾ����
			}
			time++;	
			if(time==10) time=0;
		}
		
		/**************************ȡ����*************************/		
		if(i=='d')
		{
			if(change==0)
			{
				memset(tem_password,0,sizeof(tem_password));//�������
			}
			if(change==1)
			{
				memset(new_password,0,sizeof(new_password));//�������
			}
			if(change==2)
			{
				memset(password,0,sizeof(password));//�������
			}			
			Display_LCD(2,0,bank);
			delay(10);
			j=0;time=1;
		}
		
		/**************************�޸�����*************************/		
		if(i=='e')
		{
			change=1;
			Comd_Write(0x01);				
			Display_LCD(1,0,table4);
			//delay(100);		
			j=0;time=1;
		}
	}
}
