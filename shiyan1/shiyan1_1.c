#include <reg51.h>					//ͷ�ļ�
char data *p_data;					//�䵱Ƭ��ָ��
char xdata *p_xdata;				//�䵱Ƭ��
char i;											//���������
void main()
{		p_data = 0x30;					//��ʼ��ַ
		p_xdata = 0x1000;				//��ʼ��ַ
		for(i=0;i<49;i++)			//��Ƭ��ram��ֵ
		{
			*p_xdata = i;					//��i����p_xdataָ��ĵ�ַ
			p_xdata++;						//��ַ��1
		}
		p_xdata = 0x1000;				//ָ��ԭ��ַ
		for(i=0;i<49;i++)			//copy���ݲ����Ƭ������
		{
			*p_data = *p_xdata;		//copy����
			*p_xdata=0;						//Ƭ����������
			p_data++;							//��ַ��1
			p_xdata++;						//��ַ��1
		}
}