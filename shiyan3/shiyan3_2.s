;f=6MHz，定时器/计数器T1，方式2，实现从P2.0口输出周期为120ms，占空比为（10+作业号58）%的波形。
	ORG 0000H;指定地址
	LJMP MAIN;跳至MAIN          
	ORG 001BH;定时器1中断入口地址
	AJMP SER_T1;跳至中断        
	ORG 0100H;指定地址
MAIN:MOV TMOD,#20H;写入方式控制字
     MOV TH1,#16;写入计数初值
     MOV TL1,#16
     MOV R7,#00H;中断次数初值
     SETB P2.0;P2.0口置1 
     SETB EA;开中断总开关
     SETB ET1;定时器1允许中断
     SETB TR1;启动T1定时       
     SJMP $;等待中断
SER_T1:INC R7;中断次数加1
       CJNE R7,#170,LOOP1;判断高电平时间是否达到
       CLR P2.0;中断次数到170次即高电平时间到，输出0
       AJMP LOOP;重新定时
LOOP1: CJNE R7,#250,LOOP;判断是否达到一个周期
       SETB P2.0;中断次数到250次即周期到，输出1
       MOV R7,#00H;重新计数
LOOP:RETI;中断返回
     END;结束