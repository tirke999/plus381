/*
 * uart.h
 *
 *  Created on: Feb 12, 2022
 *      Author: aleksa
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#include "stm32f4xx.h"
#include "../lib/timer/timer.h"



typedef struct UartRxRingBuff {
 	uint8_t data[500];
 	uint16_t head;
 	uint16_t tail;
 	uint16_t length;
 } UartRxRingBuff_t;

 UART_HandleTypeDef huart1;




 void MX_USART1_UART_Init(void);
 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
 void Uart_Ring_Buf_Push(UartRxRingBuff_t *rb, uint8_t data);
 void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);





#endif /* UART_UART_H_ */
