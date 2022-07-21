#include "stm32f4xx.h"
#include "gpio.h"

void GPIO_Init (GPIO_TypeDef * GPIOx,char pin,char dir,char enable_pin)
{
	//Enable clock to GBIOx
	RCC->AHB1ENR |= (1u<<enable_pin);
	if(dir == 0)
		{
			// input mode
			GPIOx->MODER &=~(1u<<(2*pin));
			GPIOx->MODER &=~(1u<<(2*pin+1));
		}
		else if(dir == 1)
		{
			// output mode
			GPIOx->MODER |= (1u<<(2*pin));
			GPIOx->MODER &=~(1u<<(2*pin+1));
		}
		else if(dir == 2)
		{
			// alternate mode
			GPIOx->MODER &=~(1u<<(2*pin));
			GPIOx->MODER |= (1u<<(2*pin+1));
		}
		else if(dir == 3)
		{
			// analog mode
			GPIOx->MODER |= (1u<<(2*pin));
			GPIOx->MODER |= (1u<<(2*pin+1));
		}

}

char GPIO_Write(GPIO_TypeDef * GPIOx,char pin,char state)
{
	if (GPIOx->MODER & (1u<<(2*pin)))
	{
		if(state)
			{
				GPIOx->ODR |=(1u<<pin);
			}
			else
			{
				GPIOx->ODR &=~(1u<<pin);
			}
		return 0;
	}
	else
	{
		return 1;
	}
}
char GPIO_ReadPin(GPIO_TypeDef * GPIOx,char pin){
	if((GPIOx->MODER &(2*pin)) && (GPIOx->MODER &~((2*pin)+1))){
		return GPIOx->ODR;
	}
	if((GPIOx->MODER &~(2*pin)) && (GPIOx->MODER &~((2*pin)+1))){
		return GPIOx->IDR;
	}

}

