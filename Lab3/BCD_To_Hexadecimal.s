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
	MOV R0,#0xA
	LDR R1,=Num1
	LDR R2,=DST
	LDR R3,[R1]
	AND R4,R3,#0x0F
	AND R5,R3,#0xF0
	MOV R5,R5,ROR #4
	MLA R5,R5,R0,R4
	STR R5,[R2]
	
STOP
	B STOP

Num1 DCD 0x42

	AREA data1,DATA,READWRITE
DST DCD 0

	END