	ORG 0000H;指定地址
	AJMP MAIN;转MAIN
	ORG 0003H;外部中断0入口
	AJMP SER_INT0;转中断服务程序
	ORG 0100H;指定地址
MAIN:MOV P1,#0FH;熄灭发光二极管且对开关输入端先输出1
	SETB IT0;脉冲触发方式
	SETB EX0;允许外部0中断
	SETB EA;开中断总开关
	AJMP $;等待中断
SER_INT0:MOV P1,#0FH;熄灭发光二极管且对开关输入端先输出1
	MOV A,P1;输入开关状态
	CPL A;状态取反
	ANL A,#0FH;屏蔽A的高半字节
	SWAP A;A高低半字节交换
	MOV P1,A;开关状态输出
	RETI;中断返回
END ;程序结束