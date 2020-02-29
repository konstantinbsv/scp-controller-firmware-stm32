/*
 * pwm.c
 *
 *  Created on: Feb 19, 2020
 *      Author: Konstantin Borissov
 */

#include "pwm.h"

TIM_HandleTypeDef *handleSCP1;
TIM_HandleTypeDef *handleSCP2;
TIM_HandleTypeDef *handleSCP3;

/**
 * @brief Initialize TIM handle
 *
 * @return HAL_OK
 */
HAL_StatusTypeDef InitializeTIM(TIM_HandleTypeDef *handle1, TIM_HandleTypeDef *handle2, TIM_HandleTypeDef *handle3) {
	handleSCP1 = handle1;
	handleSCP2 = handle2;
	handleSCP3 = handle3;

	return HAL_OK;
}

HAL_StatusTypeDef SetPWM_SCP1(uint8_t duty_cycle) {

	HAL_StatusTypeDef status = HAL_TIM_PWM_Start(handleSCP1, SCP1_CHANNEL);	// start PWM
	handleSCP1->Instance->CCR2 = duty_cycle;								// set PWM duty cycle

	return status;
}

HAL_StatusTypeDef SetPWM_SCP2(uint8_t duty_cycle) {

	HAL_StatusTypeDef status = HAL_TIM_PWM_Start(handleSCP2, SCP2_CHANNEL);	// start PWM
	handleSCP2->Instance->CCR1 = duty_cycle;								// set PWM duty cycle

	return status;
}

HAL_StatusTypeDef SetPWM_SCP3(uint8_t duty_cycle) {

	HAL_StatusTypeDef status = HAL_TIM_PWM_Start(handleSCP3, SCP3_CHANNEL);	// start PWM
	handleSCP3->Instance->CCR3 = duty_cycle;								// set PWM duty cycle

	return status;
}

HAL_StatusTypeDef SetPWM(uint8_t scp_index, uint8_t duty_cycle){
	HAL_StatusTypeDef status;

	switch (scp_index)
	{
	case 0:
		status = SetPWM_SCP1(duty_cycle);
		break;
	case 1:
		status = SetPWM_SCP2(duty_cycle);
	  	break;
	case 2:
		status = SetPWM_SCP3(duty_cycle);
		break;
	default:
		// set all PWMs to 0
		SetPWM_SCP1(0);
		SetPWM_SCP2(0);
		SetPWM_SCP3(0);
		status = HAL_ERROR;
		break;
	}

	return status;
}
