#include "ccs811.h"
#include "IIC.h"
#include "myPrintf.h"
#include "cmsis_os.h"

#define CCS811_Add  0x5A<<1
#define STATUS_REG 0x00
#define MEAS_MODE_REG 0x01
#define ALG_RESULT_DATA 0x02
#define ENV_DATA 0x05
#define NTC_REG 0x06
#define THRESHOLDS 0x10
#define BASELINE 0x11
#define HW_ID_REG 0x20
#define ERROR_ID_REG 0xE0
#define APP_START_REG 0xF4
#define SW_RESET 0xFF
#define CCS_811_ADDRESS 0x5A
#define GPIO_WAKE 0x5
#define DRIVE_MODE_IDLE 0x0
#define DRIVE_MODE_1SEC 0x10
#define DRIVE_MODE_10SEC 0x20
#define DRIVE_MODE_60SEC 0x30
#define INTERRUPT_DRIVEN 0x8
#define THRESHOLDS_ENABLED 0x4


uint8_t BUF[12];
uint8_t Information[10];
uint8_t temp = 0;
uint8_t MeasureMode, Status, Error_ID;

typedef struct {
	uint16_t eco2;
	uint16_t tvoc;
	uint8_t status;
	uint8_t error_id;
	uint16_t raw_data;
} ccs811_measurement_t;
ccs811_measurement_t CCS;

void ccs811Reset() {
	RST_HIGH;
	osDelay(1);
	RST_LOW;
	osDelay(10);
	RST_HIGH;
	osDelay(100);
}

void ccs811Init() {
	ADD_LOW;
	WAK_LOW;
	osDelay(10);
	ccs811Reset();
	
	Single_ReadI2C(CCS811_Add, 0x00, &Status, 1);	   //Firstly the status register is read and the APP_VALID flag is checked.
	Uart_printf("Status=%x\n", Status);
	if (Status & 0x10) {
		Single_MWriteI2C_byte(CCS811_Add, 0xF4, &temp, 0);
		osDelay(100);
	}
	
	Single_ReadI2C(CCS811_Add, 0x00, &Status, 1);
	Uart_printf("Status=%x\n", Status);
	Single_ReadI2C(CCS811_Add, 0x01, &MeasureMode, 1);
	Uart_printf("MeasureMode=%x\n", Status);
	Single_WriteI2C_byte(CCS811_Add, 0x01, 0x10);
	osDelay(3000);
}

void getCcs811() {

	Single_ReadI2C(CCS811_Add, 0x00, &Status, 1);
	Uart_printf("Status=%x\n", Status);
	Single_ReadI2C(CCS811_Add, 0xE0, &Error_ID, 1);
	Uart_printf("Error_ID=%x\n", Error_ID);

	if (Error_ID!=0x00)
	{
		ccs811Init();
	}
	Single_ReadI2C(CCS811_Add, 0x02, BUF, 8);

	CCS.eco2 = (uint16_t)BUF[0] * 256 + BUF[1];
	CCS.tvoc = (uint16_t)BUF[2] * 256 + BUF[3];

	Uart_printf("eco2=%d\n", CCS.eco2);
	Uart_printf("tvoc=%d\n", CCS.tvoc);
	

}