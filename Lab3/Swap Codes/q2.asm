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
	 mov r3,#0x0a
	 and r4,r2,#0x0f
	 and r5,r2,#0x0f0
	 lsr r5,#4
	 mla r6,r5,r3,r4
	 str r6,[r1]
stop b stop
src dcd 0x21
	AREA dataseg,DATA,READWRITE
dst dcd 0x0
	end