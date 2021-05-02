#include <reg51.h>
#include <string.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit RS=P2^0;//0-指令，1-数据
sbit RW=P2^1;//0-写，1-读
sbit E=P2^2;
sbit right=P2^3;//为1密码正确，灯亮，开锁

uchar code table1[]="Input Password:";
uchar code table2[]="Password Error!";
uchar code table3[]="Unclock Success!";
uchar code table4[]="Old Password:";
uchar code table5[]="New Password:";
uchar code table6[]="Password digits";
uchar code table7[]="should >5";
uchar code table8[]="Change Success!";

void delay(uchar cnt)		//延时子程序
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
LCD忙信号检测，忙返回1，不忙返回0，写操作前调用此函数
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
	result=(bit)(temp&0x80);//最高位为1表示正忙
	return result;
}


/**************************************
LCD数据写入函数
**************************************/
void Data_Write(uchar dataz)
{
	while(Check_Busy());
	RS=1;
	RW=0;
	P0=dataz;
	E=1;
	E=0;	//产生下降沿
}


/**************************************
LCD指令写入函数
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
LCD初始化函数
**************************************/
void Init_LCD()
{
	RS=0;
	E=0;
	Comd_Write(0x38);    //设置16x2显示，5x7点阵，8位数据接口
	Comd_Write(0x0c);    //开显示，不显示光标，不闪烁
	Comd_Write(0x06);    //读或写完一个字符后地址指针和光标加一，整屏显示不移动
	Comd_Write(0x01);    //数据指针清零，显示清零
}


/**************************************
LCD显示函数
**************************************/
void Display_LCD(uchar x,uchar y,uchar *str)
{
	uchar addr;
	//Init_LCD();
	if(x==1)
	{
		addr=0x80+y;//第一行y位置显示
	}
	else
	{
		addr=0x80+0x40+y;//第二行y位置显示
	}
	//Comd_Write(0x02);
	Comd_Write(addr);//从addr位置开始写
	while(*str!='\0')
	{
		Data_Write(*str++);
	}
}


/**************************************
扫描4X4键盘函数
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
			/****************扫描第一行****************/
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
			/****************扫描第二行****************/
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
			/****************扫描第三行****************/				
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
			/****************扫描第四行****************/				
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

uchar data password[17]={'1','1','1','1','1','1','1','1'};//存放原始密码（可改）
uchar data passwordbf[17]={'1','1','1','1','1','1','1','1'};//存放原始密码（不可改）
uchar data tem_password[17]={'\0'};//存放输入密码进行比较
uchar data new_password[17]={'\0'};	//存放预修改密码
uchar code bank[]="                ";//清空LCD某一行
uchar data star[16];//存放*号
/**************************************
显示num个*数组函数
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
主函数
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
	Init_LCD();//LCD初始化
	Display_LCD(1,0,table1);
	for(j=0;;)
	{
		i=scan();//扫描键盘
		/**************************密码输入**************************/
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
			{//不显示数值，显示*号
				Display_LCD(2,j,"*");
			  delay(10);
			}
			else 
			{//显示数值，用“&”传入函数参数
				Display_LCD(2,j,&i);
			  delay(10);
			}
			j++;
		}
		
		/**************************确认输入密码完毕**************************/		
		if(i=='a')
		{
			if(j<6)
		  {//密码位数小于6提示错误				
				Comd_Write(0x01);				
				Display_LCD(1,0,table6);
				Display_LCD(2,3,table7);
				delay(100);//报错延时		
				Comd_Write(0x01);
				Display_LCD(1,0,table1);
				change=0;
				j=0;time=1;//重新显示输入密码
				memset(tem_password,0,sizeof(tem_password));
				memset(new_password,0,sizeof(new_password));
				strcpy(password,passwordbf);//清空数据，密码置初值
			}
			if(j>=6)
			{//密码位数必须大于等于六位
				if(change==0)
				{
					tem_password[j+1]='\0';//输入完毕
					if(strcmp(tem_password,password)==0)
					{//密码输入正确，灯亮一段时间，提示后返回输入密码界面
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
					{//密码输入错误，提示后返回输入密码界面
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
				{//密码修改成功，提示后返回输入密码界面
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
					{//修改密码验证通过，进入设置新密码功能
						Comd_Write(0x01);				
						Display_LCD(1,0,table5);
						delay(1000);
						j=0;time=1;
						change=2;
						memset(new_password,0,sizeof(new_password));		
						memset(password,0,sizeof(password));						
					}
					else
					{//修改密码验证失败，提示后返回密码验证界面
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
		
		/**************************回车删除最后一位密码**************************/
		if(i=='b')
		{
			if(j>0)
			{				
				j--;//清除最后一位数据
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
					Display_LCD(2,0,bank);//清空LCD第二行数据
					if(change==0)//显示对应数组的元素
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
					Display_LCD(2,0,bank);//清空LCD第二行数据
					Display_LCD(2,0,star);//显示j个*
				}
				/*
				Comd_Write(0x10);//光标左移1格，地址值减 1
				Data_Write(' ');//通过显示空白实现删除最后一个“*”
				Comd_Write(0x10);
				*/
			}	
		}
		
		/**************************显示/隐藏密码**************************/
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
				flag=1;	//显示密码			
			}
			else
			{
				stars(j);
				Display_LCD(2,0,bank);//清空LCD第二行数据
				Display_LCD(2,0,star);//显示j个*
				delay(10);
				flag=0;//不显示密码
			}
			time++;	
			if(time==10) time=0;
		}
		
		/**************************取消键*************************/		
		if(i=='d')
		{
			if(change==0)
			{
				memset(tem_password,0,sizeof(tem_password));//清空数组
			}
			if(change==1)
			{
				memset(new_password,0,sizeof(new_password));//清空数组
			}
			if(change==2)
			{
				memset(password,0,sizeof(password));//清空数组
			}			
			Display_LCD(2,0,bank);
			delay(10);
			j=0;time=1;
		}
		
		/**************************修改密码*************************/		
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
