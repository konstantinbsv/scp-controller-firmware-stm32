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
#define ADC_TIMEOUT 	1000 			// maximum delay for ADC conversion
#define SAMPLINGTIME 	ADC_SAMPLETIME_3CYCLES
#define NTC1_CHANNEL	ADC_CHANNEL_4 	// ADC1_IN4
#define NTC2_CHANNEL 	ADC_CHANNEL_1	// ADC1_IN1
#define NTC3_CHANNEL 	ADC_CHANNEL_0	// ADC1_IN0


/* Function Prototypes */
HAL_StatusTypeDef InitializeADC (ADC_HandleTypeDef *handle);
uint32_t ReadNTC(int8_t ntc_channel);

#endif /* INC_NTC_H_ */
