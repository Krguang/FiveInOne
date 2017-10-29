#ifndef __CCS811_H
#define __CCS811_H

#include "stm32f1xx_hal.h"
#include "main.h"

#define ADD_LOW		HAL_GPIO_WritePin(GPIOA , ADD_Pin, GPIO_PIN_RESET)
#define RST_LOW		HAL_GPIO_WritePin(GPIOB, RST_Pin, GPIO_PIN_RESET)
#define RST_HIGH	HAL_GPIO_WritePin(GPIOB, RST_Pin, GPIO_PIN_SET)
#define WAK_LOW		HAL_GPIO_WritePin(WAK_GPIO_Port, WAK_Pin, GPIO_PIN_RESET)


void ccs811Init();
void getCcs811();


#endif // !__CCS811_H
