#include "LPC17xx.h"

typedef enum {F,T} boolean;
boolean t = T;

void EINT1_init ()
{
	LPC_PINCON->PINSEL4|=(0x01<<22);     //To set pin2.11 as EINT1
	LPC_SC->EXTMODE|=(1<<1);                 //To make edge sensetive
	LPC_SC->EXTPOLAR|=((1<<1));             //To make rising edge sensetive
	NVIC_EnableIRQ(EINT1_IRQn);
}
void EINT1_IRQHandler(){
  if(t==T){
		LPC_SC->EXTPOLAR=(~(1<<1));
		LPC_GPIO0->FIODIR2=0xFF;
    t=F;	
	}
	else{
		LPC_SC->EXTPOLAR=((1<<1));
	  LPC_GPIO0->FIODIR2=0;
		t=T;	
	}
	LPC_SC->EXTINT = (1<<1);      //To clear flag
}

int main()
{
	EINT1_init();
	while(1){}	
} 