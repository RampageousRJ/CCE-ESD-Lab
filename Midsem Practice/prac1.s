	AREA RESET,DATA,READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0x10000000
	DCD Reset_Handler
	ALIGN
	AREA myCode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
	LDR R13, =0x10000000 ;Ascending Stack
	LDR R2, = 0x32547698
	LDR R4, =0xFEFFFFFF
	LDR R6, = 0x12345678
	STM R13!, {R4,R2,R6}
	LDMDB R13!, {R2,R4,R6}
	
	LDR R13, =0x1000000C ;Descending Stack
	LDR R2, = 0x32547698
	LDR R4, =0xFEFFFFFF
	LDR R6, = 0x12345678
	STMDB R13!, {R4,R6,R2}
	LDM R13!, {R2,R4,R6}
	
STOP
	B STOP


	AREA data1,DATA,READWRITE
DST DCD 0

	END