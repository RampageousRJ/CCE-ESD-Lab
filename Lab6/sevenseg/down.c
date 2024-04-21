#include <LPC17xx.h>
 #include <stdio.h>

 #define	FIRST_SEG	0<<23
 #define	SECOND_SEG	1<<23
 #define	THIRD_SEG	2<<23
 #define	FOURTH_SEG	3<<23
 #define	DISABLE_ALL 4<<23

 unsigned int digcount=0,flag=0X00,count=0;
 signed int digvalue[5]={9,9,9,9,9};//0,4,3,2,1-->1 2 3 4
 unsigned int selectseg[5]={0,0<<23,1<<23,2<<23,3<<23};
 unsigned char sev_seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
 unsigned long int temp1, temp2,i=0;

 void delay(void);
void Display(void);
 void downcount();

int main(void)
 {    
		SystemInit();
		SystemCoreClockUpdate();
		LPC_PINCON->PINSEL0 &= 0xFF0000FF;	
		LPC_PINCON->PINSEL3 &= 0xFFC03FFF;	
		LPC_GPIO0->FIODIR |= 0x00000FF0;	
		LPC_GPIO1->FIODIR |= 0x07800000;	
	 
		while(1)
		{
			delay();	
			digcount +=1;  
			if(digcount == 0x05)
				{ digcount = 0x01;
					if(flag==0XFF)
					{
					downcount();flag=0x00;
							}
						}
				Display();
						}
					}

 void Display()      
 {        
	
		LPC_GPIO1->FIOPIN = selectseg[digcount];  
		LPC_GPIO0->FIOPIN=sev_seg[digvalue[digcount]]<<4;	
    for(i=0;i<100;i++);	 
	  LPC_GPIO0->FIOCLR=0X00000FF0;
	 


 }	
 void downcount()
 {
	 digvalue[1]--;
	 
	 
	 if(digvalue[1]<0)
	 {digvalue[2]--;
		 digvalue[1]=9;
		 if(digvalue[2]<0)
	 {digvalue[3]--;
		 digvalue[2]=9;
		 if(digvalue[3]<0)
	 {digvalue[4]--;
		 digvalue[3]=9;
		 if(digvalue[4]<0)
	 
	 { digvalue[0]=9;
		 digvalue[1]=9;
		 digvalue[2]=9;
		 digvalue[3]=9;
		 digvalue[4]=9;
	 }
  
 }
 }
 }
 else
	 delay();
 }
 
 
void delay(void)
 {  unsigned int i;
		
	  for(i=0;i<1000;i++);
	 
	 if(count==10000)
	 {
		 flag=0XFF;
		 count=0;
	 }
	 else
		 count++;	
}


