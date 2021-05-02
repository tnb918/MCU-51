;f=12MHz，定时器/计数器T0，方式1，实现从P1.0口输出周期为（20+作业号58）ms的方波。【中断方式】
	ORG 0000H;指定地址
	LJMP MAIN;跳至MAIN     
	ORG 000BH;定时器0中断入口地址
	AJMP SER_T0;跳至中断         
	ORG 0100H;指定地址
MAIN:MOV TMOD,#01H;写入方式控制字        
     MOV TH0,#67H;写入计数初值        
     MOV TL0,#0A8H;12MHz 65536-39000=26536(ox67A8)
     SETB EA;开中断总开关                
     SETB ET0;定时器0允许中断               
     SETB TR0;启动T0定时              
     SJMP $;等待中断                          
SER_T0:MOV TH0,#67H;重新写入计数初值        
      MOV TL0,#0A8H
      CPL P1.0;输出取反               
	  RETI;中断返回
      END;结束 