	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10004000
	DCD Reset_Handler
	ALIGN
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0,=NUM
	LDR R1,[R0]
	LDR R10,=DST
	LDR R5,=0x4
	
LOOP
	AND R2,R1,#0xF
	LSR R1,R1,#4
	STRB R2,[R10],#1
	SUBS R5,R5,#1
	BNE LOOP
	
STOP
	B STOP

NUM DCD 0x1234
	AREA DATASEG,DATA,READWRITE
	
DST DCD 0x0
	END