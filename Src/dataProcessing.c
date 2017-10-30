#include "dataProcessing.h"
#include "ccs811.h"
#include "hdc1080.h"
#include "usart.h"

uint8_t localArray[10];
//0			1			2			3			4			5			6			7			8			9
//pm2.5高	pm2.5低		co2高		co2低		tvoc高		tvoc低		温度高		温度低		湿度高		湿度低	


void getPM25() {
	if (Usart2ReceiveState)
	{
		Usart2ReceiveState = 0;
		for (size_t i = 0; i < Usart2ReceiveBuffer.BufferLen; i++)
		{
			if (Usart2ReceiveBuffer.BufferArray[0]!=0x42|| Usart2ReceiveBuffer.BufferArray[1] != 0x4d)
			{
				return;
			}
			uint16_t temp = 0;

			for (uint8_t i = 0; i < 22; i++)
			{
				temp = temp + Usart2ReceiveBuffer.BufferArray[i];
			}
			if ((Usart2ReceiveBuffer.BufferArray[22]!=(temp>>8))||(Usart2ReceiveBuffer.BufferArray[23]!=(temp&0xff)))
			{
				return;
			}
			localArray[0] = Usart2ReceiveBuffer.BufferArray[12];
			localArray[1] = Usart2ReceiveBuffer.BufferArray[13];
		}
		Usart2ReceiveBuffer.BufferLen = 0;
	}
}

void getCO2AndTVOC() {
	for (uint8_t i = 2,j=0; i < 6; i++,j++)
	{
		localArray[i] = gasValue[j];
	}
}

void getTempAndHumi() {
	for (uint8_t i = 6,j=0; i < 10; i++,j++)
	{
		localArray[i] = tempAndHumi[j];
	}
}

void dataProcessing() {
	getPM25();
	getCO2AndTVOC();
	getTempAndHumi();
}
