	ORG 0000H				;指定地址
	AJMP MAIN				;跳转至MAIN
	ORG 0100H				;指定地址
MAIN:MOV R1,#0				;查表次数
	MOV R7,#8				;循环移位次数
	MOV R5,#8				;调整循环移位次数
LOOP1:MOV 07H,05H			;将R5值传给R7
	MOV A,R1				;将R1值传给A
	MOVC A,@A+PC			;查表
	DB 0FEH,0FCH,0F8H,0F0H	;表中对应数值（对应相邻1，2,3,4个灯亮）
LOOP2:MOV P1,A				;将A查表得到的值穿传给P0口
	RL A					;左移，实现跑马灯
	ACALL DELAY				;调用延时0.216ms
	DJNZ R7,LOOP2			;循环移位次数
	INC R1					;R1+1
	DEC R5					;R5-1
	CJNE R5,#4,Q			;确保移位次数调整和表中数据个数一致
	MOV R5,#8				;R5<=4时重置数值为8
	Q:CJNE R1,#4,LOOP1		;判断是否查完表中的4个数据，没查完回到循环1继续
	MOV R1,#0				;R1>=4时，重置为零
	AJMP LOOP1				;跳至循环1，重新开始花式跑马灯
DELAY:MOV R2,#65 			;R2赋值65
D1:MOV R3,#40				;R3赋值40
D2:MOV R4,#16				;R4赋值16
D3: NOP						;空操作
	NOP						;空操作
	NOP						;空操作
	DJNZ R4,D3				;循环16次
	DJNZ R3,D2				;循环40次
	DJNZ R2,D1				;循环65次
    RET						;返回
END							;结束