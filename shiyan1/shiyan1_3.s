	ORG 0000H				;ָ����ַ
	AJMP MAIN				;��ת��MAIN
	ORG 0100H				;ָ����ַ
MAIN:MOV R1,#0				;������
	MOV R7,#8				;ѭ����λ����
	MOV R5,#8				;����ѭ����λ����
LOOP1:MOV 07H,05H			;��R5ֵ����R7
	MOV A,R1				;��R1ֵ����A
	MOVC A,@A+PC			;���
	DB 0FEH,0FCH,0F8H,0F0H	;���ж�Ӧ��ֵ����Ӧ����1��2,3,4��������
LOOP2:MOV P1,A				;��A���õ���ֵ������P0��
	RL A					;���ƣ�ʵ�������
	ACALL DELAY				;������ʱ0.216ms
	DJNZ R7,LOOP2			;ѭ����λ����
	INC R1					;R1+1
	DEC R5					;R5-1
	CJNE R5,#4,Q			;ȷ����λ���������ͱ������ݸ���һ��
	MOV R5,#8				;R5<=4ʱ������ֵΪ8
	Q:CJNE R1,#4,LOOP1		;�ж��Ƿ������е�4�����ݣ�û����ص�ѭ��1����
	MOV R1,#0				;R1>=4ʱ������Ϊ��
	AJMP LOOP1				;����ѭ��1�����¿�ʼ��ʽ�����
DELAY:MOV R2,#65 			;R2��ֵ65
D1:MOV R3,#40				;R3��ֵ40
D2:MOV R4,#16				;R4��ֵ16
D3: NOP						;�ղ���
	NOP						;�ղ���
	NOP						;�ղ���
	DJNZ R4,D3				;ѭ��16��
	DJNZ R3,D2				;ѭ��40��
	DJNZ R2,D1				;ѭ��65��
    RET						;����
END							;����