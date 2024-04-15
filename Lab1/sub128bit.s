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
	ldr r0,=num1
	ldr r1,=num2
	ldr r2,=ans
	mov r6,#4;
up	ldr r3,[r0],#4
	ldr r4,[r1],#4
	sbcs r5,r3,r4
	str r5,[r2],#4
	sub r6,#1
	teq r6,#0
	bne up
	sbc r7,#0
	str r7,[r2]
stop b stop
num1 dcd 0xffffffff,0xffffffff,0xffffffff,0xfffff
num2 dcd 0x00000001,0x11111111,0x12345678,0x01
	AREA dataseg,DATA,READWRITE
ans dcd 0x0
	end