	AREA RESET,CODE,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x40001000
	DCD Reset_Handler
	ALIGN
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	ldr r0,=num1
	ldr r1,=num2
	ldr r5,=DST
	mov r6,#4
up	ldr r2,[r0],#4
	ldr r3,[r1],#4
	adcs r4,r2,r3
	str r4,[r5],#4
	sub r6,#1
	teq r6,#0
	bne up
	adc r7,#0
	str r7,[r5]
stop b stop
num1 DCD 0x2,0x1,-0x1,0x6
num2 DCD 0x3,0x3,0x7,0x4
	AREA mydata,DATA,READWRITE
DST DCD 0
	END