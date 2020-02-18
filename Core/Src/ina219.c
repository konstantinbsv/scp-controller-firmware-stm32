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
	uint8_t read_buffer[2];
	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(ina219_i2c_handle, device_address, reg_address, I2C_MEMADD_SIZE_8BIT, read_buffer, INA219_REG_BYTES_SIZE, I2C_TIMEOUT);
	*read_data = read_buffer[0] << 8 | read_buffer[1];

	return status;
}

HAL_StatusTypeDef WriteRegister (uint8_t device_address, uint8_t reg_address, uint16_t write_data) {

	uint8_t write_buffer[2] = { (uint8_t) (write_data >> 8), (uint8_t) (write_data) };

	return HAL_I2C_Mem_Write(ina219_i2c_handle, device_address, reg_address, I2C_MEMADD_SIZE_8BIT, write_buffer, INA219_REG_BYTES_SIZE, I2C_TIMEOUT);
}

/*
 * Set PGA gain and registers for measuring up to 16V and 1.15A
 */
HAL_StatusTypeDef Set_16V_1A55 (uint8_t device_address) {
	uint16_t config_reg = 	INA219_BRNG_16V | INA219_PGA_160mV |
							INA219_SADC_12BIT | INA219_BADC_12BIT |
							INA219_MODE_S_AND_B_V_CONTINUOUS;
	current_lsb 	= 1.55 / 32768;			// max_current / 2^15
	power_lsb 		= current_lsb * 20;
	cal_reg 		= (uint16_t)(0.04096/(current_lsb*RSHUNT));

	HAL_StatusTypeDef cal_stat 		= WriteRegister(device_address, INA219_REG_CAL, cal_reg);		// Program calibration register
	HAL_StatusTypeDef conf_stat 	= WriteRegister(device_address, INA219_REG_CONFIG, config_reg);	// Set PGA gains and sampling modes in configuration register

	return (cal_stat == conf_stat) ? HAL_OK : HAL_ERROR;
}

float GetBusVoltage(uint8_t device_address) {
	uint16_t raw_bus_voltage;
	ReadRegister(device_address, INA219_REG_BUS_V, &raw_bus_voltage); // get raw bus voltage from INA219

	raw_bus_voltage = raw_bus_voltage >> 3;					// bit shift 3 right to remove empty bit, CNVR, and OVF
	int16_t bus_voltage_mV = (int16_t) raw_bus_voltage * 4; // *4mV (bus voltage LSB) to get actual bus voltage measured my device
	float bus_voltage_V = (float) raw_bus_voltage * 0.001;	// multiply by 0.001 to convert mV -> V

	return bus_voltage_V;
}


