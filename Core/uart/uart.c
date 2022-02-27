/*
 * uart.c
 *
 *  Created on: Feb 13, 2022
 *      Author: aleksa
 */
#include "uart.h"





void Uart_Ring_Buf_Push(UartRxRingBuff_t *rb, uint8_t data);

UartRxRingBuff_t uartRxRingBuf;
uint8_t rxCharacter[] = {0,1,2,3,4,5};

uint8_t tx_buff[] = {0,1,2,3,4,5,6,7};


void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  	{
  		Error_Handler();
  	}
  HAL_UART_Receive_IT(&huart1, rxCharacter, 1);
  HAL_UART_Transmit_IT(&huart1, tx_buff, 8);


}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

		if (is_time_passed(1000))
		{

		for (int i = 0; i<6; i++)
		{
		Uart_Ring_Buf_Push(&uartRxRingBuf, rxCharacter[i]); // store received character into ring buffer
		}
		HAL_UART_Receive_IT(&huart1, rxCharacter, 6); 		// start uart rx interrupt again
		HAL_UART_Transmit(&huart1, rxCharacter, 6, HAL_MAX_DELAY);

		}

}

void Uart_Ring_Buf_Push(UartRxRingBuff_t *rb, uint8_t data) {
	if (rb->length >= 500) {
		return;
	}

	rb->data[rb->head++] = data;
	rb->length++;

	if (rb->head == 500) {
		rb->head = 0;
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (is_time_passed(1000))
	{
	HAL_UART_Transmit_IT(&huart1, tx_buff, 8);
	}

}


/*void MyUART_Print_String(UART_HandleTypeDef * pHuart, char myString[64])
{
	uint8_t pBuf[64];

	sprintf((char*)pBuf, "%s\r\n",myString);
	HAL_UART_Transmit(pHuart, pBuf, strlen((char*)pBuf), HAL_MAX_DELAY);
	HAL_Delay(100);
}*/
