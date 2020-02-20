/*
 * pwm.c
 *
 *  Created on: Feb 19, 2020
 *      Author: Konstantin Borissov
 */

#include "pwm.h"

static TIM_HandleTypeDef *timer_handle = NULL;

/**
 * @brief Initialize TIM handle
 *
 * @return HAL_OK
 */
HAL_StatusTypeDef InitializeTIM(TIM_HandleTypeDef *handle) {
	timer_handle = handle;

	return HAL_OK;
}

HAL_StatusTypeDef SetPWM(uint32_t channel, uint8_t duty_cycle) {

	HAL_StatusTypeDef status = HAL_TIM_PWM_Start(timer_handle, channel);	// start PWM
	timer_handle->Instance->CCR2 = duty_cycle;								// set PWM duty cycle

	return status;
}
