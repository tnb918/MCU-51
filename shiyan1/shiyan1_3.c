#include <reg51.h>  				//头文件
void delay()							//延时函数216ms
{	 
	unsigned char i,j,k;			//定义计数器i,j,k
	for(i=65;i>0;i--){				//循环65次
	for(j=40;j>0;j--){				//循环40次
	for(k=40;k>0;k--)					//循环40次
	{;}												//循环内容
}}} 												//[(2*40+3)*40+3]*65+5=21600 晶振12MHZ

void main()
{
	int i,j;//定义计数器i，j
	unsigned char A[] = {0x01,0x03,0x07,0x0F};//定义数组
	unsigned char a = A[0];	//定义初始状态
    while(1)	{							//死循环
			for(i=0;i<4;i++)//遍历数组元素
				{
					a=A[i];//类似查表，给a赋初值
				for(j=8;j>0;j--) //移位循环
				{					
					P1 = ~a; 	//低电平有效，对a按位取反
					delay();	//延时
					if(a >= 0x80)//最高位为1时
						break;//跳出循环，中断左移
 					a = a<<1;	//左移实现跑马灯
				}}
			}
}