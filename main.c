///**
//  ******************************************************************************
//  * @file    main.c
//  * @author  Ac6
//  * @version V1.0
//  * @date    01-December-2013
//  * @brief   Default main function.
//  ******************************************************************************
//*/
//

#include "stm32f4xx.h"
#include "gpio.h"
#include "adc.h"
#include "lcd.h"

unsigned short int data;
int main(void)
{  //LCD
		LCD_Init();
//		LCD_ClearScreen();


	//GPIO configuration
		//Enable port A clock
		RCC->AHB1ENR |= (1<<0);
		//Enable port B clock
		RCC->AHB1ENR |= (1<<1);

		//enable GPIOA port 0 input
		GPIO_Init(GPIOA,0,3,0);
		GPIOA->PUPDR &= ~(1<<0);
		GPIOA->PUPDR &= ~(1<<1);

		ADCConfigType configure = {twelve_bits , cont , 0};


		// initialize the ADC
		ADC_Init(&configure);

		for(int i=0;i<8;i++){
		GPIO_Init(GPIOB,i,1,1);
		}
		u8 valid=0;

		char error[11] = {"ADC ERROR!"};
		ADC_StartConv(0);

if (USE_POLLING){
		while(1){
			ADC_StartConv(0);
			LCD_ClearScreen();
			valid = ADC_ReadData(&data);
			if(~valid){
//				valid = ADC_ReadData(&data);
				LCD_IntToStr(data);
				for(int i=0;i<1000000;i++);
			}
			else{
				LCD_DisplayString(error);
			}
	}


}else{
//	LCD_ClearScreen();
//	LCD_IntToStr(data);
//	for(int i=0;i<1000000;i++);
//	ADC_StartConv(0);

}
}
void ADC_IRQHandler(void){
	LCD_ClearScreen();
	ADC_ReadData(&data);
	LCD_IntToStr(data);
	for(int i=0;i<1000000;i++);
	ADC_StartConv(0);

}
