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
	HAL_StatusTypeDef status = HAL_UART_Transmit(serial_handle, (uint8_t *) data, strlen(data), SERIAL_TIMEOUT);

	return status;
}

HAL_StatusTypeDef UARTPrintFloat(float data, uint8_t fractional_digits) {
	uint8_t write_buffer[8];
	uint8_t conversion_multiplier = 1;

	// conversion_multiplier = 10^fractional_digits
	for (uint8_t i = 0; i < fractional_digits; i++) {
		conversion_multiplier *= 10;
	}

	// separate integer from decimal part
	data *= conversion_multiplier;
	uint16_t integer_part	 = (uint16_t) data / conversion_multiplier;
	uint16_t fractional_part = (uint16_t) data % conversion_multiplier;

	// copy into write_buffer with decimal point
	if (fractional_digits == 0) {
		sprintf((char*)write_buffer, "%u", integer_part); // do not print decimal point
	} else {
		sprintf((char*)write_buffer, "%u.%u", integer_part, fractional_part);
	}

	HAL_StatusTypeDef status = HAL_UART_Transmit(serial_handle, write_buffer, strlen((char 	*)write_buffer), SERIAL_TIMEOUT);

	return status;
}
