#include<lpc17xx.h>

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 = 0;
	LPC_GPIO0->FIODIR = (1<<22);
	while(1){
		LPC_GPIO0->FIOSET = (1<<22);
	}
}
