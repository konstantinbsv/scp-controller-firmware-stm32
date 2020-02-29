/*
 * pwm.h
 *
 *  Created on: Feb 19, 2020
 *      Author: Konstantin Borissov
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

/* Includes */
#include "stm32f446xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"

/* Defines */

enum {	// SCP Timer Channels
	SCP1_CHANNEL = TIM_CHANNEL_2,
	SCP2_CHANNEL = TIM_CHANNEL_1,
	SCP3_CHANNEL = TIM_CHANNEL_3
};


/* Function Prototypes */
HAL_StatusTypeDef InitializeTIM(TIM_HandleTypeDef *handle1, TIM_HandleTypeDef *handle2, TIM_HandleTypeDef *handle3);
HAL_StatusTypeDef SetPWM(uint8_t scp_index, uint8_t duty_cycle);
HAL_StatusTypeDef SetPWM_SCP1(uint8_t duty_cycle);
HAL_StatusTypeDef SetPWM_SCP2(uint8_t duty_cycle);
HAL_StatusTypeDef SetPWM_SCP3(uint8_t duty_cycle);

#endif /* INC_PWM_H_ */
