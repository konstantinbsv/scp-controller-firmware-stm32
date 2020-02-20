/*
 * pwm.h
 *
 *  Created on: Feb 19, 2020
 *      Author: Konstantin Borissov
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

/* Includes */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"

/* Defines */
#define SCP1_CHANNEL TIM_CHANNEL_2
#define

/* Function Prototypes */
HAL_StatusTypeDef InitializeTIM(TIM_HandleTypeDef *handle);
HAL_StatusTypeDef SetPWM(uint32_t channel, uint8_t duty_cycle);

#endif /* INC_PWM_H_ */
