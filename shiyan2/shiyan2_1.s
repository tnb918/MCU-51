	ORG 0000H;ָ����ַ
	AJMP MAIN;תMAIN
	ORG 0003H;�ⲿ�ж�0���
	AJMP SER_INT0;ת�жϷ������
	ORG 0100H;ָ����ַ
MAIN:MOV P1,#0FH;Ϩ�𷢹�������ҶԿ�������������1
	SETB IT0;���崥����ʽ
	SETB EX0;�����ⲿ0�ж�
	SETB EA;���ж��ܿ���
	AJMP $;�ȴ��ж�
SER_INT0:MOV P1,#0FH;Ϩ�𷢹�������ҶԿ�������������1
	MOV A,P1;���뿪��״̬
	CPL A;״̬ȡ��
	ANL A,#0FH;����A�ĸ߰��ֽ�
	SWAP A;A�ߵͰ��ֽڽ���
	MOV P1,A;����״̬���
	RETI;�жϷ���
END ;�������