/*
 * ina219.c
 *
 *  Created on: Feb 12, 2020
 *      Author: Konstantin Borissov
 */

#include <ina219.h>

const uint8_t INA219_ADDRESSES[3] = {INA219_ADDRESS_1, INA219_ADDRESS_2, INA219_ADDRESS_3};

static I2C_HandleTypeDef *ina219_i2c_handle = NULL;

/**
 * @brief Initialize I2C handle
 *
 * @return HAL_OK
 */
HAL_StatusTypeDef InitializeI2C (I2C_HandleTypeDef *i2c_handle) {
	ina219_i2c_handle = i2c_handle;

	return HAL_OK;
}

/*
 * @brief Reads from specified register of specified device and pieces MSB and LSB to form data.
 *        Note: pass pointer to value into which to read the data.
 *
 * @return HAL_OK if operation successful
 */
HAL_StatusTypeDef ReadRegister (uint8_t device_address, uint8_t reg_address, uint16_t *read_data) {
	uint8_t read_buffer[2];
	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(ina219_i2c_handle, device_address, reg_address, I2C_MEMADD_SIZE_8BIT, read_buffer, INA219_REG_BYTES_SIZE, I2C_TIMEOUT);
	*read_data = read_buffer[0] << 8 | read_buffer[1];

	return status;
}
/*
 * @brief Writes data to specified register of specified device.
 *
 * @return HAL_OK if operation successful.
 */
HAL_StatusTypeDef WriteRegister (uint8_t device_address, uint8_t reg_address, uint16_t write_data) {

	uint8_t write_buffer[2] = { (uint8_t) (write_data >> 8), (uint8_t) (write_data) };

	return HAL_I2C_Mem_Write(ina219_i2c_handle, device_address, reg_address, I2C_MEMADD_SIZE_8BIT, write_buffer, INA219_REG_BYTES_SIZE, I2C_TIMEOUT);
}

/*
 * @brief Sets PGA gain and registers for measuring up to 16V and 1.15A. Calculates and stores current and power LSBs.
 * 		  Calculates calibration value and initializes calibration register.
 *
 * @return HAL_OK if both calibration and configuration initializations are successful.
 * 		   HAL_ERROR if either fails
 */
HAL_StatusTypeDef Set_16V_1A55 (uint8_t device_address) {
	uint16_t config_reg = 	INA219_BRNG_16V | INA219_PGA_160mV |
							INA219_SADC_12BIT_32SMPL | INA219_BADC_12BIT_32SMPL |
							INA219_MODE_S_AND_B_V_CONTINUOUS;
	current_lsb 	= 1.55 / 32768;			// max_current / 2^15
	power_lsb 		= current_lsb * 20;
	cal_reg 		= (uint16_t)(0.04096/(current_lsb*RSHUNT));

	HAL_StatusTypeDef cal_stat 		= WriteRegister(device_address, INA219_REG_CAL, cal_reg);		// Program calibration register
	HAL_StatusTypeDef conf_stat 	= WriteRegister(device_address, INA219_REG_CONFIG, config_reg);	// Set PGA gains and sampling modes in configuration register

	return (cal_stat == conf_stat) ? HAL_OK : HAL_ERROR;
}

/*
 * @brief Sets PGA gain and registers for measuring up to 32V and 2.6A. Calculates and stores current and power LSBs.
 * 		  Calculates calibration value and initializes calibration register.
 *
 * @return HAL_OK if both calibration and configuration initializations are successful.
 * 		   HAL_ERROR if either fails
 */
HAL_StatusTypeDef Set_32V_2A6 (uint8_t device_address) {
	uint16_t config_reg = 	INA219_BRNG_32V | INA219_PGA_320mV |
							INA219_SADC_12BIT_32SMPL | INA219_BADC_12BIT_32SMPL |
							INA219_MODE_S_AND_B_V_CONTINUOUS;
	current_lsb 	= 2.6 / 32768;			// max_current / 2^15
	power_lsb 		= current_lsb * 20;
	cal_reg 		= (uint16_t)(0.04096/(current_lsb*RSHUNT));

	HAL_StatusTypeDef cal_stat 		= WriteRegister(device_address, INA219_REG_CAL, cal_reg);		// Program calibration register
	HAL_StatusTypeDef conf_stat 	= WriteRegister(device_address, INA219_REG_CONFIG, config_reg);	// Set PGA gains and sampling modes in configuration register

	return (cal_stat == conf_stat) ? HAL_OK : HAL_ERROR;
}


/*
 * @brief Retrieves and processes raw bus voltage value from register.
 *
 * @return Bus votlage in volts (V)
 */
float GetBusVoltage_V(uint8_t device_address) {
	uint16_t raw_bus_voltage;
	ReadRegister(device_address, INA219_REG_BUS_V, &raw_bus_voltage); // get raw bus voltage from INA219

	raw_bus_voltage = raw_bus_voltage >> 3;					// bit shift 3 right to remove empty bit, CNVR, and OVF
	int16_t bus_voltage_mV = (int16_t) raw_bus_voltage * 4; // *4mV (bus voltage LSB) to get actual bus voltage measured my device and convert to signed
	float bus_voltage_V = (float)bus_voltage_mV * 0.001;	// multiply by 0.001 to convert mV -> V

	return bus_voltage_V;
}

/*
 * @brief Updates configuration register. Retrieves raw value from current register and performs calculations.
 *
 * @return Current in milliamps (mA)
 */
float GetCurrent_mA(uint8_t device_address){
	uint16_t raw_current;

	WriteRegister(device_address, INA219_REG_CAL, cal_reg); 		// reinitialize calibration register in case of chip reset
	ReadRegister(device_address, INA219_REG_CURRENT, &raw_current); // get raw current value from register

	float current_mA = (float)((int16_t) raw_current) * current_lsb * 1000; 	// convert to signed and multiply by LSB value
																				// and *1000 (register value is in uA) to get current in mA
	return current_mA;
}

/*
 * @brief Updates configuration register. Retrieves raw value from power register and performs calculations.
 *
 * @return Power in milliwatts (mW)
 */
float GetPower_mW(uint8_t device_address) {
	uint16_t raw_power;

	WriteRegister(device_address, INA219_REG_CAL, cal_reg); 	// reinitialize calibration register in case of chip reset
	ReadRegister(device_address, INA219_REG_POWER, &raw_power); // get raw power value from register

	float power_mW = (float)((int16_t) raw_power) * power_lsb * 1000; 	// convert to signed and multiply by LSB value (=20*current_lsb)
																		// and * 1000 (to convert to mW from uW)
	return power_mW;
}

/*
 * @brief Calculates Thevenin equivalent resistance of the load connected.
 *
 * @return Thevenin equivalent resistance in ohms (ohms)
 */
float GetThevenin_R(uint8_t device_address) {
	float voltage_V = GetBusVoltage_V(device_address);		// get voltage in V
	float current_A = GetCurrent_mA(device_address) / 1000; // get current in mA and convert to A

	return voltage_V / current_A;
}
