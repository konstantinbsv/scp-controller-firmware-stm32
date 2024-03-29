/*
 * ntc.h
 *
 *  Created on: Feb. 19, 2020
 *      Author: Konstantin Borissov
 */

#ifndef INC_NTC_H_
#define INC_NTC_H_

/* Includes */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"
#include <math.h>

/* Constants */
#define ADC_TIMEOUT 	1000 					// maximum delay for ADC conversion
#define SAMPLINGTIME 	ADC_SAMPLETIME_3CYCLES	// sampling time
#define MAX_ADC			4096					// max ADC value = 2^adc_resolution
#define VCC				5.0f					// power supply to NTC in volts
#define R_RESISTOR		18000.0f				// value of SMD resistor in ohms
#define T0				298.15f					// room temperature in Kelvin (25.0 C = 298.15 K)
#define R0				100000.0f				// resistance of NTC at 25C
#define BETA			3950.0f					// beta value of NTC

enum {
	NTC1 = ADC_CHANNEL_4, 	// ADC1_IN4
	NTC2 = ADC_CHANNEL_1,	// ADC1_IN1
	NTC3 = ADC_CHANNEL_0	// ADC1_IN0
};

/* NTC Math Constants */



/* Function Prototypes */
HAL_StatusTypeDef InitializeADC (ADC_HandleTypeDef *handle);
uint32_t ReadNTCRaw(int8_t ntc_channel);
float GetResistance_R(uint8_t ntc_channel);
float GetTemp_C(uint8_t ntc_channel);

#endif /* INC_NTC_H_ */
