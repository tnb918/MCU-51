	ORG 0000H			;指定地址
	AJMP MAIN			;跳至MAIN
	ORG 0100H			;指定地址
MAIN:MOV A,#0FEH		;规定初始状态11111110
LOOP:MOV P1,A			;将A中值传给P1
	RL A				;左移实现跑马灯
 	ACALL DELAY			;调用延时函数216ms
	AJMP LOOP			;继续循环
DELAY:MOV R3,#65		;给R3赋值65   
D1:MOV R4,#40			;给R4赋值40
D2:MOV R5,#16			;给R5赋值16
D3: NOP					;空操作
	NOP					;空操作
	NOP					;空操作
	DJNZ R5,D3			;循环16次
	DJNZ R4,D2			;循环40次
	DJNZ R3,D1			;循环65次
    RET					;返回
						;[(5*16+2+1)*40+2+1]*65+5=216000  晶振12MHZ
END						;结束