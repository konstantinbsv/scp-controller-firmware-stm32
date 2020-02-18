/*
 * serial.c
 *
 *  Created on: Feb. 18, 2020
 *      Author: Konstantin
 */


#include <serial.h>

static UART_HandleTypeDef *serial_handle = NULL;

HAL_StatusTypeDef InitializeUART (UART_HandleTypeDef _serial_handle) {
	serial_handle = _serial_handle;

	return HAL_OK;
}

HAL_StatusTypeDef
