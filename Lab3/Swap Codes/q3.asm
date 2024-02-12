	AREA RESET,CODE,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA myCode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	 ldr r0,=src
	 ldr r1,=dst
	 ldr r2,[r0];Initial Number
	 mov r3,#0;divisor
	 mov r4,#0;for management of digits in various positions
up	 bl div
	 lsl r2,r4
	 add r6,r2
	 mov r2,r3
	 mov r3,#0
	 add r4,#4
	 cmp r2,#0x0
	 bne up
exit str r6,[r1]	 

stop b stop
div cmp r2,#0x0a
	bcc down
	sub r2,#0x0a
	add r3,#1
	b div
down bx lr

src dcd 0xff
	AREA dataseg,DATA,READWRITE
dst dcd 0x0
	end