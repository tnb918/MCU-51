;f=12MHz����ʱ��/������T0����ʽ1��ʵ�ִ�P1.0���������Ϊ��20+��ҵ��58��ms�ķ��������жϷ�ʽ��
	ORG 0000H;ָ����ַ
	LJMP MAIN;����MAIN     
	ORG 000BH;��ʱ��0�ж���ڵ�ַ
	AJMP SER_T0;�����ж�         
	ORG 0100H;ָ����ַ
MAIN:MOV TMOD,#01H;д�뷽ʽ������        
     MOV TH0,#67H;д�������ֵ        
     MOV TL0,#0A8H;12MHz 65536-39000=26536(ox67A8)
     SETB EA;���ж��ܿ���                
     SETB ET0;��ʱ��0�����ж�               
     SETB TR0;����T0��ʱ              
     SJMP $;�ȴ��ж�                          
SER_T0:MOV TH0,#67H;����д�������ֵ        
      MOV TL0,#0A8H
      CPL P1.0;���ȡ��               
	  RETI;�жϷ���
      END;���� 