#ifndef __USART_H
#define __USART_H

#include "stm32f1xx_hal.h"
#include "mb4_1sf_driver.h"
#include "stdio.h"
	 				    
int fputc(int ch, FILE *f);

extern UART_HandleTypeDef huart1;
		 
#endif

