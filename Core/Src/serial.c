/*
 * serial.c
 *
 *  Created on: Feb. 18, 2020
 *      Author: Konstantin Borissov
 */


#include "serial.h"

static UART_HandleTypeDef *serial_handle = NULL;
static char uart_read_buffer[READ_BUFFER_SIZE] = {0}; // create empty read buffer

/**
 * @brief Initialize UART handle
 *
 * @return HAL_OK
 */
HAL_StatusTypeDef InitializeUART(UART_HandleTypeDef *handle) {
	serial_handle = handle;
	// __HAL_UART_ENABLE(serial_handle); // set CE bit in CR1 register to enable UART
	// serial_handle->Init.Mode = UART_MODE_TX_RX; // set UART mode to RX TX by setting CR1 register bits

	InitializeReceiveInterrupt();


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
 *
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	uint16_t new_setpoints[3]; // will store new set points

	// TODO: is there a neater way to do this?
	// extract raw chars from read buffer
	char raw_read_1[3] = {uart_read_buffer[0], uart_read_buffer[1], uart_read_buffer[2]};
	char raw_read_2[3] = {uart_read_buffer[5], uart_read_buffer[6], uart_read_buffer[7]};
	char raw_read_3[3] = {uart_read_buffer[10], uart_read_buffer[11], uart_read_buffer[12]};

	sscanf(raw_read_1, "%hu", &new_setpoints[0]);
	sscanf(raw_read_2, "%hu", &new_setpoints[1]);
	sscanf(raw_read_3, "%hu", &new_setpoints[2]);

	uint8_t setpoints_array_size = sizeof(new_setpoints)/sizeof(new_setpoints[0]); // calculate array size

	for (uint8_t i = 0; i < setpoints_array_size; i++) {
		SetSetpoint(i + 1, new_setpoints[i]);
		UARTPrintFloat(new_setpoints[i], 0);
	}
	// sscanf does not work
	// sscanf(uart_read_buffer, "%hhu\r\n%hhu\r\n%hhu", &new_setpoints[0], &new_setpoints[1], &new_setpoints[3]);

	InitializeReceiveInterrupt(); // restart interrupt

	__NOP();
}

/**
 * Initialized HAL UART RX interrupt
 * @return HAL status
 */
HAL_StatusTypeDef InitializeReceiveInterrupt(){
	return HAL_UART_Receive_IT(serial_handle,(uint8_t *) uart_read_buffer, READ_BUFFER_SIZE);
}

/**
 * @brief Sends standardized data packet over UART
 *
 * @return void
 */
void SendDataPacket(float bus_v1, float current1, float power1, float temp1,
		float bus_v2, float current2, float power2, float temp2, float bus_v3,
		float current3, float power3, float temp3, uint8_t pwm1, uint8_t pwm2, uint8_t pwm3) {

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
	UARTPrintCharArray("PWM1: ");
	UARTPrintFloat(pwm1, 3);
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
	UARTPrintCharArray("PWM2: ");
	UARTPrintFloat(pwm2, 3);
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
	UARTPrintCharArray("PWM3: ");
	UARTPrintFloat(pwm3, 3);
	UARTNewlineRet();
	UARTPrintCharArray("END");
	UARTNewlineRet();

}
