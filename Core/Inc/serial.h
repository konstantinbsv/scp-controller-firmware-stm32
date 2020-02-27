/*
 * serial.h
 *
 *  Created on: Feb. 18, 2020
 *      Author: Konstantin Borissov
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
HAL_StatusTypeDef UARTNewlineRet();
void SendDataPacket(float bus_v1, float current1, float power1, float temp1,
		float bus_v2, float current2, float power2, float temp2, float bus_v3,
		float current3, float power3, float temp3, uint8_t pwm1, uint8_t pwm2, uint8_t pwm3);


#endif /* INC_SERIAL_H_ */
