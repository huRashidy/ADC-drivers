/////*
//// * adc.c
//// *
//// *  Created on: ??þ/??þ/????
//// *      Author: hosen
//// */
#include "stm32f4xx.h"
#include "adc.h"
#include "gpio.h"

void ADC_Init(ADCConfigType* ConfigParamPtr){

	//ADC configuration
	//enable ADC clock
	RCC->APB2ENR|=(1<<8);
	//enable ADC
	ADC1->CR2 |=(1<<0);

	//select clock prescaler, divided by 2
	ADC ->CCR &= (0<<16);
	ADC ->CCR &= (0<<17);

	//select 12bit resolution
	ADC1->CR1 =(ADC1->CR1&0xFCFFFFFF) |((ConfigParamPtr->res & 0x03)<<24);
	//mode of convergence
	ADC1->CR2=(ADC1->CR2 & 0xFFFFFFFD)|((ConfigParamPtr->conv & (1<<0) )<<1);
	//right alignment
	ADC1->CR2 &=~(1<<11);
	//select 1 conversion  for regular channel
	ADC1->SQR1 &=~(1<<20);
	ADC1->SQR1 &=~ (1<<21);
	ADC1->SQR1 &=~ (1<<22);
	ADC1->SQR1 &=~ (1<<23);

//enable EOC interrupt for regular channel

#if USE_POLLING
	ADC1->CR1 &=~(1<<5);
#else
	ADC1->CR1 |=(1<<5);
	NVIC->ISER[0] |=(1<<18);
#endif
	// enable EOC to set a bit and enable overrun detection
	ADC1 -> CR2 |= (1 << 10);


}
void ADC_StartConv(unsigned char ChannelNum){

		 //choose channel number
		 ADC1->SQR3 |=(ChannelNum<<0);

		 // start conversion of regular channels
		 ADC1->CR2 |= (1<<30);

}


void ADC_GetConversionState(unsigned char* ConversionStatePtr){
#if USE_POLLING
	if ((ADC1->SR &(1<<1))){
		//conversion is done
		*ConversionStatePtr = 1;
	}
    else if (~(ADC1->SR &(1<<1))){
		//conversion is not done yet
		*ConversionStatePtr = 0;
	}
#endif

}
unsigned char ADC_ReadData(unsigned short int* DataPtr){
	//check overrun in SR
	if(ADC1->SR |=(1<<5) ==0){
		//no overrun occured
		//there is a value in ADC
		*DataPtr = (ADC1->DR*150*5)/(1.5*4096);
		return 0;
	}
	else if(ADC1->SR |=(1<<5) ==1){
			//overrun occured
			//there is no value in ADC
			return 1;
		}

}










