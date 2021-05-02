#include <reg51.h>
#include <string.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit RS=P2^0;//0-指令，1-数据
sbit RW=P2^1;//0-写，1-读
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

uchar flag1=0;//测量类型标志位
uchar flag2=0;//测量档位标志位

unsigned long temp,tempz;

void delay(uchar cnt)		//延时子程序
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
	if(x==1)
	{
		addr=0x80+y;//第一行y位置显示
	}
	else
	{
		addr=0x80+0x40+y;//第二行y位置显示
	}
	Comd_Write(addr);//从addr位置开始写
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
uchar code bank[]="                ";//清空显示屏某一行
uchar err=0;//错误标志

/***********************报警函数***********************/
void ERROR()
{
 	err=1;
}
/***********************计算实际值***********************/
void cal(uchar times)
{
	if(flag1==0)
	{
		strcpy(table2,table1);//清空原数据
		temp=tempz;//防止数据变化（可有可无）
		temp=temp*times*500*1.0/255;//电压放大100倍便于显示，计算
		table2[8]=temp/10000%10+48;	//万	
		table2[9]=temp/1000%10+48;	//千	
		table2[10]=temp/100%10+48;	//百	
		table2[12]=temp/10%10+48;		//十
		table2[13]=temp%10+48;			//个			
	}
	if(flag1==1)
	{
		strcpy(table4,table3);
		temp=tempz;
		temp=temp*50000*1.0/(255*times);//电压放大10000倍
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
/***********************结果显示函数**********************/
void display()
{
	/***********************测电压***********************/
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
	
	/***********************测电流***********************/	
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

	/***********************测电阻***********************/	
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


/***********************AD转换函数**********************/
void A_D()
{
	start=0;
	oe=0;
	start=1;
	start=0;
	delay(1);
	if(eoc==1)//AD转换结束
	{
		oe=1;
		temp=P1;
		tempz=temp;
		oe=0;
		display();//LCD屏幕显示
		start=1;
		start=0;
	}
}


void int0() interrupt 0 //外部0中断 切换测量类型
{	
	flag1++;
	if(flag1==3) flag1=0;
	flag2=0;err=0;X4=0;
}


void int1() interrupt 2 //外部1中断 切换测量档位
{	
	flag2++;
	if(flag2==3) flag2=0;err=0;X4=0;
}


void main()
{
	Init_LCD();//LCD初始化
	X1=0;X2=0;X3=0;X4=0;
	ADD1=0;ADD2=0;ADD3=0;
	EA=1;//开中断总开关
	EX1=1;//允许外部1中断
	EX0=1;//允许外部0中断
	IT1=1;
	IT0=1;//负跳沿产生中断
	Display_LCD(1,0," Welcome To Use ");
	Display_LCD(2,0,"  This Product  ");	
	delay(1000);
	while(1)
	{ 
		if(err==0)
		{
			switch(flag1)
			{
				case 0:ADD1=0,ADD2=0,ADD3=0;break;//选IN0
				case 1:ADD1=1,ADD2=0,ADD3=0;break;//选IN1
				case 2:ADD1=0,ADD2=1,ADD3=0;break;//选IN2
			}							
			switch(flag2)
			{
				case 0:X1=1,X2=0,X3=0;break;//档位1
				case 1:X1=0,X2=1,X3=0;break;//档位2
				case 2:X1=0,X2=0,X3=1;break;//档位3
			}
			delay(10);			
			A_D();
		}	
		if(P3_4==0)
		{											//第一次检测到按键信息
			delay(10);					//延时约10ms，消除抖动
			if(P3_4==0)
			{										//第二次检测到按键信息 
				if(X4==1){
					switch(flag1)
					{
						case 0:ADD1=0,ADD2=0,ADD3=0;break;//选IN0
						case 1:ADD1=1,ADD2=0,ADD3=0;break;//选IN1
						case 2:ADD1=0,ADD2=1,ADD3=0;break;//选IN2
					}							
					switch(flag2)
					{
						case 0:X1=1,X2=0,X3=0;break;//档位1
						case 1:X1=0,X2=1,X3=0;break;//档位2
						case 2:X1=0,X2=0,X3=1;break;//档位3
					}
					delay(10);
					A_D();X4=0;}
				while(P3_4==0);		//等待按键释放
			}
		}
	}
}