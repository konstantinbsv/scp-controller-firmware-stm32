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

float GetTemp_C(uint8_t ntc_channel) {
	raw_adc_value = Read
}
