#ifndef _IIC_H
#define _IIC_H

#include "stm32f1xx_hal.h"
#include "main.h"


#define SCL_H         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET)
#define SCL_L         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET)
   
#define SDA_H         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET)
#define SDA_L         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)


#define SCL_read      HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)
#define SDA_read      HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)

void I2C_Stop(void);
uint8_t Single_WriteI2C_byte(uint8_t Slave_Address, uint8_t REG_Address, uint8_t data);
uint8_t Single_MWriteI2C_byte(uint8_t Slave_Address, uint8_t REG_Address, uint8_t const *data, uint8_t length);
uint8_t Single_ReadI2C(uint8_t Slave_Address, uint8_t REG_Address, uint8_t *REG_data, uint8_t length);
uint8_t Single_MReadI2C(uint8_t Slave_Address, uint8_t REG_Address, uint8_t *REG_data, uint8_t length);
#endif
