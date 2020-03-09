/*
 * ina219.h
 *
 *  Created on: Feb 12, 2020
 *      Author: Konstantin Borissov
 *
 *      This library was created by using the STM32 HAL documentation, Adafruit's INA219 library as reference,
 *      and the TI INA219 data sheet.
 */

#ifndef INC_INA219_H_
#define INC_INA219_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

#define RSHUNT 		0.100 		// value of shunt resistor in ohms (used for programming calibration register)
#define I2C_TIMEOUT 1000		// used as timeout for HAL I2C functions
#define INA219_REG_BYTES_SIZE 2 // All INA219 16-bit registers are two 8-bit bytes through I2C. Used to tell HAL to transmit 2 bytes

/* Variables for storing calculated LSB values and calibration register value */
float current_lsb;
float power_lsb;
uint16_t cal_reg;


/* I2C Addresses */
enum {
	INA219_ADDRESS_1 =	(0x40 << 1), // 1000000 (A0=GND, A1=GND)
	INA219_ADDRESS_2 =	(0x41 << 1), // 1000001 (A0=VCC, A1=GND)
	INA219_ADDRESS_3 =	(0x42 << 1)  // 1000010 (A0=SDA, A1=GND)
};
const uint8_t INA219_ADDRESSES[3];

/*
 * Registers - page 19 of data sheet
 */
#define INA219_REG_CONFIG 	(0x00) // R/W, default: 0x399F
#define INA219_REG_SHUNT_V 	(0x01) // read only
#define INA219_REG_BUS_V 	(0x02) // read only
#define INA219_REG_POWER 	(0x03) // read only
#define INA219_REG_CURRENT 	(0x04) // read only
#define INA219_REG_CAL 		(0x05) // calibration register, R/W, default: 0x00

/* Configuration Reset */
#define INA219_CONFIG_RESET (0x8000) // write to configuration register to perform software reset

/* Bus Voltage Range */
enum {
	INA219_BRNG_16V = (0x0000), // 0-16V
	INA219_BRNG_32V = (0x2000)  // 0-32V	(default)
};

/* Programmable Gain Amplifier Gain (Shunt Voltage) */
enum {
	INA219_PGA_40mV  = (0x0000), // /1 gain
	INA219_PGA_80mV  = (0x0800), // /2 gain
	INA219_PGA_160mV = (0x1000), // /4 gain
	INA219_PGA_320mV = (0x1800), // /8 gain (default)
};

// Note: BADC and SADC averaging uses 12-bit ADC resolution. Unless specified all other configurations take 1 sample.

/* Bus ADC Resolution/Averaging */
enum {
	INA219_BADC_9BIT 			= (0x0000), // 9-bit 	0-512		84us
	INA219_BADC_10BIT 			= (0x0080), // 10-bit	0-1024		148us
	INA219_BADC_11BIT 			= (0x0100), // 11-bit	0-2048		276us
	INA219_BADC_12BIT 			= (0x0180), // 12-bit	0-4096		532us 	(default)
	INA219_BADC_12BIT_2SMPL 	= (0x0480), // 12-bit	2 samples	1.06ms
	INA219_BADC_12BIT_4SMPL 	= (0x0500), // 12-bit	4 samples	2.13ms
	INA219_BADC_12BIT_8SMPL 	= (0x0580), // 12-bit	8 samples	4.26ms
	INA219_BADC_12BIT_16SMPL 	= (0x0600), // 12-bit	16 samples	8.51ms
	INA219_BADC_12BIT_32SMPL 	= (0x0680), // 12-bit	32 samples	17.02ms
	INA219_BADC_12BIT_64SMPL 	= (0x0700), // 12-bit	64 samples	34.05ms
	INA219_BADC_12BIT_128SMPL 	= (0x0780)  // 12-bit	128 samples	68.10ms
};

/* Shunt ADC Resolution/Averaging */
enum {
	INA219_SADC_9BIT 			= (0x0000), // 9-bit 	0-512		84us
	INA219_SADC_10BIT 			= (0x0008), // 10-bit	0-1024		148us
	INA219_SADC_11BIT 			= (0x0010), // 11-bit	0-2048		276us
	INA219_SADC_12BIT 			= (0x0018), // 12-bit	0-4096		532us	(default)
	INA219_SADC_12BIT_2SMPL 	= (0x0048), // 12-bit	2 samples	1.06ms
	INA219_SADC_12BIT_4SMPL 	= (0x0050), // 12-bit	4 samples	2.13ms
	INA219_SADC_12BIT_8SMPL 	= (0x0058), // 12-bit	8 samples	4.26ms
	INA219_SADC_12BIT_16SMPL 	= (0x0060), // 12-bit	16 samples	8.51ms
	INA219_SADC_12BIT_32SMPL 	= (0x0068), // 12-bit	32 samples	17.02ms
	INA219_SADC_12BIT_64SMPL 	= (0x0070), // 12-bit	64 samples	34.05ms
	INA219_SADC_12BIT_128SMPL 	= (0x0078)  // 12-bit	128 samples	68.10ms
};

/* Operating Modes */
enum {
	INA219_MODE_POWERDOWN				= (0x0000),	// power down
	INA219_MODE_SHUNT_V_TRIGGERED		= (0x0001),	// shunt voltage, triggered
	INA219_MODE_BUS_V_TRIGGERED			= (0x0002),	// bus voltage, triggered
	INA219_MODE_S_AND_B_V_TRIGGERED		= (0x0003),	// shunt and bus voltage, triggered
	INA219_MODE_ADC_OFF					= (0x0004),	// ADC off (disabled)
	INA219_MODE_SHUNT_V_CONTINUOUS		= (0x0005),	// shunt voltage, continuous
	INA219_MODE_BUS_V_CONTINUOUS		= (0x0006),	// bus voltage, continuous
	INA219_MODE_S_AND_B_V_CONTINUOUS	= (0x0007),	// shunt and bus voltage, continuous	(default)
};

/* Function Prototypes */

HAL_StatusTypeDef InitializeI2C (I2C_HandleTypeDef *i2c_handle);
HAL_StatusTypeDef ReadRegister (uint8_t device_address, uint8_t reg_address, uint16_t *read_data);
HAL_StatusTypeDef Set_16V_1A55 (uint8_t device_address);
HAL_StatusTypeDef Set_32V_1A55 (uint8_t device_address);
float GetBusVoltage_V(uint8_t device_address);
float GetCurrent_mA(uint8_t device_address);
float GetPower_mW(uint8_t device_address);
float GetThevenin_R(uint8_t device_address);

#endif /* INC_INA219_H_ */
