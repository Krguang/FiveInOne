#include "IIC.h"
#include "myPrintf.h"
#include "cmsis_os.h"

#define HDC1080_I2C_ADDR 0x80 //0x40 << 1

#define Temperature 0x00//0x0000 Temperature measurement output
#define Humidity 0x01//0x0000 Relative Humidity measurement output
#define Configuration 0x02// 0x1000 HDC1080 configuration and status
#define Manufacturer_ID 0xFE//0x5449 ID of Texas Instruments
#define Device_ID 0xFF//0x1050 ID of the device


#define Manufacturer_ID_value 0x5449
#define Device_ID_value 0x1050
#define Configuration_1 0x1000 // Heater disabled, Temperature and Humidity are acquired in sequence, Temperature first.,  14-bit  resolution
#define Configuration_2 0x3000 // Heater enabled, Temperature and Humidity are acquired in sequence, Temperature first.,  14-bit  resolution

uint8_t tempAndHumi[4];

void HDC1080_Init()
{
	unsigned int data1, data2;
	unsigned char datax[2];

	Single_ReadI2C(HDC1080_I2C_ADDR, Manufacturer_ID, datax, 2);
	data1 = (unsigned int)(datax[0] << 8);
	data1 += datax[1];
	Uart_printf("HDC1080 Manufacturer_ID = %x\n", data1);

	Single_ReadI2C(HDC1080_I2C_ADDR, Device_ID, datax, 2);
	data2 = (unsigned int)(datax[0] << 8);
	data2 += datax[1];
	Uart_printf("HDC1080 Device_ID = %x\n", data2);

	if (data1 != Manufacturer_ID_value || data2 != Device_ID_value)
	{
		Uart_printf("I2C_Read_HDC1080 Manufacturer_ID or Device_ID_value error\n");
		return;
	}

	data1 = Configuration_1;
	Single_WriteI2C_byte(HDC1080_I2C_ADDR, Configuration, data1);
	//I2C_Write_HDC1080(HDC1080_I2C_ADDR, Configuration, data1);
	//wait  at least  20ms  to readout  temp&humidity  value
	osDelay(30);
	Uart_printf("I2C_Write_HDC1080 register 0x02 = %x\n", data1);

	Single_ReadI2C(HDC1080_I2C_ADDR, Configuration, datax, 2);
	//I2C_Read_HDC1080(HDC1080_I2C_ADDR, Configuration, datax);
	data1 = (unsigned int)(datax[0] << 8);
	data1 += datax[1];

	Uart_printf("I2C_Read_HDC1080 register 0x02 = %x\n", data1);
	//SysTickDelay_ms(2000);
	osDelay(2000);
}
/*
void Convert_HDC1080_TempHumidity(unsigned char *datax)
{
	//100 times of the actural value
	unsigned long  temp, humidity;
	temp = (unsigned long)(datax[0] << 8);
	temp += datax[1];
	temp = (temp * 16500) >> 16;
	temp -= 4000;
	Uart_printf("Temp = %d  C\n", temp);

	humidity = (unsigned long)(datax[2] << 8);
	humidity += datax[3];
	humidity = (humidity * 100) >> 16;


	Uart_printf("humidity = %d RH\n", humidity);
}
*/

void HDC1080_Read_Temper(void)
{
	uint8_t buffer[2];
	uint16_t temp;

	Single_MReadI2C(HDC1080_I2C_ADDR, Temperature, buffer, 2);
	temp = (uint16_t)(buffer[0] << 8);
	temp += buffer[1];
	temp = (temp * 16500) >> 16;
	temp -= 4000;

	tempAndHumi[0] = temp >> 8;
	tempAndHumi[1] = temp & 0xff;

	Uart_printf("temp = %d C\n", temp);
}

void HDC1080_Read_Humidi(void)
{
	uint8_t buffer[2];
	uint16_t humidity;
	Single_MReadI2C(HDC1080_I2C_ADDR, Humidity, buffer, 2);
	humidity = (uint16_t)(buffer[0] << 8);
	humidity += buffer[1];
	humidity = (humidity * 100) >> 16;

	tempAndHumi[2] = humidity >> 8;
	tempAndHumi[3] = humidity & 0xff;

	Uart_printf("humidity = %d RH\n", humidity);
}

void getHdc1080() {
	HDC1080_Read_Temper();
	HDC1080_Read_Humidi();
}