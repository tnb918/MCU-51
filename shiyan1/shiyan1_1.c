#include <reg51.h>					//头文件
char data *p_data;					//充当片内指针
char xdata *p_xdata;				//充当片外
char i;											//定义计数器
void main()
{		p_data = 0x30;					//初始地址
		p_xdata = 0x1000;				//初始地址
		for(i=0;i<49;i++)			//给片外ram赋值
		{
			*p_xdata = i;					//将i赋给p_xdata指向的地址
			p_xdata++;						//地址加1
		}
		p_xdata = 0x1000;				//指向原地址
		for(i=0;i<49;i++)			//copy数据并清空片外数据
		{
			*p_data = *p_xdata;		//copy数据
			*p_xdata=0;						//片外数据置零
			p_data++;							//地址加1
			p_xdata++;						//地址加1
		}
}