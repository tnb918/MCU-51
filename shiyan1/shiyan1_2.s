	ORG 0000H			;ָ����ַ
	AJMP MAIN			;����MAIN
	ORG 0100H			;ָ����ַ
MAIN:MOV A,#0FEH		;�涨��ʼ״̬11111110
LOOP:MOV P1,A			;��A��ֵ����P1
	RL A				;����ʵ�������
 	ACALL DELAY			;������ʱ����216ms
	AJMP LOOP			;����ѭ��
DELAY:MOV R3,#65		;��R3��ֵ65   
D1:MOV R4,#40			;��R4��ֵ40
D2:MOV R5,#16			;��R5��ֵ16
D3: NOP					;�ղ���
	NOP					;�ղ���
	NOP					;�ղ���
	DJNZ R5,D3			;ѭ��16��
	DJNZ R4,D2			;ѭ��40��
	DJNZ R3,D1			;ѭ��65��
    RET					;����
						;[(5*16+2+1)*40+2+1]*65+5=216000  ����12MHZ
END						;����