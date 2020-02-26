/*
 * serial.c
 *
 *  Created on: Feb. 18, 2020
 *      Author: Konstantin Borissov
 */


#include "serial.h"

static UART_HandleTypeDef *serial_handle = NULL;

/**
 * @brief Initialize UART handle
 *
 * @return HAL_OK
 */
HAL_StatusTypeDef InitializeUART(UART_HandleTypeDef *handle) {
	serial_handle = handle;

	return HAL_OK;
}

/**
 * @brief Transmits character array over UART
 *
 * @return HAL_OK if operation successful
 */
HAL_StatusTypeDef UARTPrintCharArray(char data[]) {
	HAL_StatusTypeDef status = HAL_UART_Transmit(serial_handle, (uint8_t *) data, strlen(data), SERIAL_TIMEOUT);

	return status;
}

/**
 * @brief Transmits float over UART with number of fractional digits specified.
 *
 * @return HAL_OK if operation successful
 */
HAL_StatusTypeDef UARTPrintFloat(float data, uint8_t fractional_digits) {
	uint8_t write_buffer[8];
	uint32_t conversion_multiplier = 1;

	// conversion_multiplier = 10^fractional_digits
	for (uint8_t i = 0; i < fractional_digits; i++) {
		conversion_multiplier *= 10;
	}

	// separate integer from decimal part
	uint32_t integer_part 	 = (uint32_t) data;
	uint32_t fractional_part = (uint32_t) (data * conversion_multiplier) % conversion_multiplier;

	// copy into write_buffer with decimal point
	if (fractional_digits == 0) {
		sprintf((char*)write_buffer, "%lu", integer_part); // do not print decimal point
	} else {
		sprintf((char*)write_buffer, "%lu.%lu", integer_part, fractional_part);
	}

	HAL_StatusTypeDef status = HAL_UART_Transmit(serial_handle, write_buffer, strlen((char 	*)write_buffer), SERIAL_TIMEOUT);

	return status;
}

/**
 * @brief Transmits newline and return character over UART: "\n\r"
 *
 * @return HAL_OK if operation successful
 */
HAL_StatusTypeDef UARTNewlineRet() {
	char newline_ret[] = "\n\r";

	return UARTPrintCharArray(newline_ret);
}

/**
 * @brief Sends standardized data packet over UART
 *
 * @return void
 */

void SendDataPacket(float bus_v1, float current1, float power1, float temp1,
		float bus_v2, float current2, float power2, float temp2, float bus_v3,
		float current3, float power3, float temp3) {

	// send START signal
	UARTPrintCharArray("START");
	UARTNewlineRet();

	/* Data Set 1 */
	UARTPrintCharArray("Voltage1: ");
	UARTPrintFloat(bus_v1, 3);
	UARTNewlineRet();
	UARTPrintCharArray("Current1: ");
	UARTPrintFloat(current1, 3);
	UARTNewlineRet();
	UARTPrintCharArray("Power1: ");
	UARTPrintFloat(power1, 3);
	UARTNewlineRet();
	UARTPrintCharArray("NTC1: ");
	UARTPrintFloat(temp1, 3);
	UARTNewlineRet();

	/* Data Set 2 */
	UARTPrintCharArray("Voltage2: ");
	UARTPrintFloat(bus_v2, 3);
	UARTNewlineRet();
	UARTPrintCharArray("Current2: ");
	UARTPrintFloat(current2, 3);
	UARTNewlineRet();
	UARTPrintCharArray("Power2: ");
	UARTPrintFloat(power2, 3);
	UARTNewlineRet();
	UARTPrintCharArray("NTC2: ");
	UARTPrintFloat(temp2, 3);
	UARTNewlineRet();

	/* Data Set 3 */
	UARTPrintCharArray("Voltage3: ");
	UARTPrintFloat(bus_v3, 3);
	UARTNewlineRet();
	UARTPrintCharArray("Current3: ");
	UARTPrintFloat(current3, 3);
	UARTNewlineRet();
	UARTPrintCharArray("Power3: ");
	UARTPrintFloat(power3, 3);
	UARTNewlineRet();
	UARTPrintCharArray("NTC3: ");
	UARTPrintFloat(temp3, 3);
	UARTNewlineRet();
	UARTPrintCharArray("END");
	UARTNewlineRet();
}
