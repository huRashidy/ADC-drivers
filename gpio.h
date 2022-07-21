/*
 * gpio.h
 *
 */
#include "stm32f4xx.h"
#ifndef INCLUDE_GPIO_H_
#define INCLUDE_GPIO_H_

void GPIO_Init (GPIO_TypeDef * GPIOx,char pin,char dir,char enable_pin);
char GPIO_WritePin(GPIO_TypeDef * GPIOx,char pin,char state);
char GPIO_ReadPin(GPIO_TypeDef * GPIOx,char pin);

#endif /* INCLUDE_GPIO_H_ */
