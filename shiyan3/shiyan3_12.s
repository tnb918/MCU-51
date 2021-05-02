;f=12MHz，定时器/计数器T0，方式1，实现从P1.0口输出周期为（20+作业号58）ms的方波。【查询方式】
	ORG 0000H;指定地址
	LJMP MAIN;跳至MAIN
	ORG 0100H;指定地址
MAIN:MOV TMOD,#01H;写入方式控制字 
     MOV TH0,#67H;写入计数初值       
     MOV TL0,#0A8H;12MHz 65536-39000=26536(ox67A8)
     SETB TR0;启动T0定时              
LOOP:JBC TF0,NEXT;查询是否溢出
     SJMP LOOP;未溢出继续查询
NEXT:MOV TH0,#67H;重新写入计数初值
     MOV TL0,#0A8H
     CPL P1.0;输出取反 
     SJMP LOOP;重新定时 
     END;结束