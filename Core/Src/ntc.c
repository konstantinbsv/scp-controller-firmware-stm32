/*
 * ntc.c
 *
 *  Created on: Feb. 19, 2020
 *      Author: Konstantin Borissov
 */

#include "ntc.h"

static ADC_HandleTypeDef *adc_handle = NULL;

/**
 * @brief Initialize ADC handle
 *
 * @return HAL_OK
 */
HAL_StatusTypeDef InitializeADC (ADC_HandleTypeDef *handle) {
	adc_handle = handle;

	return HAL_OK;
}

uint32_t ReadNTCRaw(int8_t ntc_channel) {
	uint32_t adc_value;

	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel 		= ntc_channel;
	sConfig.SamplingTime 	= SAMPLINGTIME;
	sConfig.Rank			= 1;

	HAL_ADC_ConfigChannel(adc_handle, &sConfig); 		// Configure channel
	HAL_ADC_Start(adc_handle);							// start ADC
	HAL_ADC_PollForConversion(adc_handle, ADC_TIMEOUT);	// wait for conversion to complete

	adc_value = HAL_ADC_GetValue(adc_handle);			// get value from ADC
	HAL_ADC_Stop(adc_handle);							// stop ADC

	return adc_value;
}

float GetResistance_R(uint8_t ntc_channel) {
	uint32_t raw_adc_value = ReadNTCRaw(ntc_channel); // get raw value from ADC

	// calculate voltage at NTC terminal
	float ntc_voltage = ((float)raw_adc_value / MAX_ADC) * 3.3;

	// calculate resistance of NTC
	float r_ntc = R_RESISTOR * (VCC/ntc_voltage - 1);

	return r_ntc;
}

float GetTemp_C(uint8_t ntc_channel) {
	// get resistance calculated from ADC
	float r_ntc = GetResistance_R(ntc_channel);

	// calculate temperature in Kelvin using Steinhart-Hart beta-parameter equation
	float temp_kelvin = 1.0 / ( 1.0/T0 + (1.0/BETA)*log(r_ntc/R0) );

	// convert to Celsius
	float temp_c = temp_kelvin - 273.15;

	return temp_c;
}
