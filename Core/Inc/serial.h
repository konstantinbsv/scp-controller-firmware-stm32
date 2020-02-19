/*
 * serial.h
 *
 *  Created on: Feb. 18, 2020
 *      Author: Konstantin
 */

#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

/* Includes */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include <string.h>		// standard C library, contains strcopy and strlen
#include <stdio.h>

/* Constants */
#define SERIAL_TIMEOUT 1000 // used as timeout for HAL UART functions

/* Function Prototypes */
HAL_StatusTypeDef InitializeUART(UART_HandleTypeDef *serial_handle);
HAL_StatusTypeDef UARTPrintCharArray(char data[]);
HAL_StatusTypeDef UARTPrintFloat(float data, uint8_t fractional_digits);

#endif /* INC_SERIAL_H_ */
