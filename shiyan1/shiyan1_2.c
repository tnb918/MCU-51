#include <reg51.h>  				//头文件
void delay1s()							//延时函数216ms
{	 
	unsigned char i,j,k;			//定义计数器i,j,k
	for(i=65;i>0;i--){				//循环65次
	for(j=40;j>0;j--){				//循环40次
	for(k=40;k>0;k--)					//循环40次
	{;}												//循环内容
}}} 												//[(2*40+3)*40+3]*65+5=216000 晶振12MHZ

void main()
{
	unsigned char a = 0x01;		//定义初始状态
    while(1)								//死循环
	{
	  if(a == 0x00)   				//如果高位溢出
	  {
	    a = 0x01;     			  //则恢复
	  }
	  P1 = ~a; 							  //低电平有效，对a按位取反
	  a = a<<1;								//左移实现跑马灯
	  delay1s();							//延时函数
	}
}