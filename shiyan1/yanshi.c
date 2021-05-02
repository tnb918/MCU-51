#include <reg52.h>
void delay(void)
{
	unsigned char i,j,k;
	for(i=2;i>0;i--)
	for(j=110;j>0;j--)
	for(k=1;k>0;k--);
}
void main()
{
	delay();
}