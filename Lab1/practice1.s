; QUESTION 1
; Load four 32-bit hexadecimal numbers in R0-R3
; Move two 8-bit hexadecimal in R4 and R5
; Load -13h, 30, 35, -2Fh in registers R7-R10


	AREA RESET, DATA, READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0, Num1
	LDR R1, Num2
	LDR R2, Num3
	LDR R3, Num4
	MOV R4, #0xAA
	MOV R5, #-0xF9
	LDR R7, =-0x13
	LDR R8, =30
	LDR R9, =35
	LDR R10, =-0x2F
	
STOP
	B STOP
	
Num1 DCD 0x1234567A
Num2 DCD 0xFFFAB001
Num3 DCD 0x10010010
Num4 DCD -0x40823743

	END