	AREA RESET,DATA,READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA myCode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
	

Reset_Handler
	MOV R10,#1
	LDR R12,=SRC
	LDR R0,=DST
	LDR R1,[R12]
	MOV R2,#0
	MOV R5,#0
	LDR R3,=0x0000000F
	BL HEX2DEC
	B STOP

HEX2DEC
	AND R4,R1,R3
	MOV R1,R1,ROR #4
	MUL R4,R4,R10
	ADD R5,R5,R4
	MOV R10,R10,LSL #4
	ADD R2,R2,#1
	CMP R2,#8
	BNE HEX2DEC
	BX LR


EXIT
	BX LR
	
ARMSTRONG
	

STOP
	B STOP
	
SRC DCD 153

	AREA data1,DATA,READWRITE
DST DCD 0

	END