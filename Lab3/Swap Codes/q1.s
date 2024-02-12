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
	ldr r2,[r0]
	cmp r2,#09
	ble next
	add r2,#7
next add r2,#30
	str r2,[r1]
stop b stop
src dcd 0x21
	AREA dataseg,DATA,READWRITE
dst dcd 0x0
	end