/*
 * serial.c
 *
 *  Created on: Feb. 18, 2020
 *      Author: Konstantin Borissov
 */


#include <serial.h>

static UART_HandleTypeDef *serial_handle = NULL;

HAL_StatusTypeDef InitializeUART(UART_HandleTypeDef *handle) {
	serial_handle = handle;

	return HAL_OK;
}

HAL_StatusTypeDef UARTPrintCharArray(char data[]) {
	HAL_StatusTypeDef status = HAL_UART_Transmit(serial_handle, (uint8_t*) data, strlen(data), SERIAL_TIMEOUT);

	return status;
}
