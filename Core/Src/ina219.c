/*
 * ina219.c
 *
 *  Created on: Feb 12, 2020
 *      Author: Konstantin Borissov
 */

#include <ina219.h>

static I2C_HandleTypeDef *ina219_i2c_handle = NULL;

/**
 * Initialize I2C handle
 */
HAL_StatusTypeDef InitializeI2C (I2C_HandleTypeDef *i2c_handle) {
	ina219_i2c_handle = i2c_handle;

	return HAL_OK;
}


HAL_StatusTypeDef ReadRegister (uint8_t device_address, uint8_t reg_address, uint16_t *read_data) {

	return HAL_I2C_Mem_Read(ina219_i2c_handle, device_address, reg_address, I2C_MEMADD_SIZE_8BIT, read_data, INA219_REG_BYTES_SIZE, HAL_MAX_DELAY);
}

HAL_StatusTypeDef WriteRegister (uint8_t device_address, uint8_t reg_address, uint16_t write_data) {

	uint8_t write_buffer[2] = { (uint8_t) (write_data >> 8), (uint8_t) (write_data) };
	return HAL_I2C_Mem_Write(ina219_i2c_handle, device_address, reg_address, I2C_MEMADD_SIZE_8BIT, &write_buffer, INA219_REG_BYTES_SIZE, I2C_TIMEOUT);
}

/*
 * Using 0.1 Ohm shunt resistor and setting the PGA for a max allowed shunt voltage
 * of 320mV will allow a maximum current accross the resistor of 3.2A
 */
HAL_StatusTypeDef Set_32V_3A2 (uint8_t device_address) {
	uint16_t reg_param = 	INA219_BRNG_32V | INA219_PGA_320mV |
							INA219_SADC_12BIT | INA219_BADC_12BIT |
							INA219_MODE_S_AND_B_V_CONTINUOUS;


	return WriteRegister(device_address, INA219_REG_CONFIG, reg_param);
}


HAL_StatusTypeDef Set_32V_1A6 (uint8_t device_address) {
	uint16_t reg_param = 	INA219_BRNG_32V | INA219_PGA_160mV |
							INA219_SADC_12BIT | INA219_BADC_12BIT |
							INA219_MODE_S_AND_B_V_CONTINUOUS;


	return WriteRegister(device_address, INA219_REG_CONFIG, reg_param);
}

