	AJMP MAIN			;����MAIN			
	ORG 0100H			;ָ����ַ				
MAIN:MOV A,#00H			;��A��ֵ0			    
	MOV DPTR,#1000H		;�䵱Ƭ��ָ��		
	MOV R7,#49			;ѭ������			
LOOP1:MOVX @DPTR,A		;��A��ֵ����Ƭ��1000H		
	INC A				;A+1		
	INC DPTR			;DPTR+1				
	DJNZ R7,LOOP1		;ѭ��49�Σ���������			
	MOV DPTR,#1000H		;�䵱Ƭ��ָ��	
	MOV R0,#30H			;�䵱Ƭ�ڵ�ַָ��		
	MOV R7,#49			;ѭ������	
LOOP2:MOVX A,@DPTR		;��Ƭ��1000H���ݴ���A				
	MOV @R0,A			;��A�����ݴ���Ƭ��30H				
	INC R0				;R0+1				
	INC DPTR			;DPTR+1				
	DJNZ R7,LOOP2		;ѭ��49�Σ�copy	
	MOV A,#00H			;��A��ֵ0			    
	MOV DPTR,#1000H		;�䵱Ƭ��ָ��		
	MOV R7,#49			;ѭ������		
LOOP3:MOVX @DPTR,A		;��Ƭ��1000H����						
	INC DPTR			;DPTR+1				
	DJNZ R7,LOOP3		;ѭ��49�Σ����Ƭ������			
	SJMP $;				;��ѭ��					
	END;				;����