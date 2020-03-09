/*
 * state_machine.h
 *
 *  Created on: Mar. 6, 2020
 *      Author: Konstantin Borissov
 */

#ifndef INC_STATE_MACHINE_H_
#define INC_STATE_MACHINE_H_

/* Includes */
#include "stdbool.h"
#include "pid.h"
#include "pwm.h"
#include "ina219.h"

/* Constants */
#define MAX_CURRENT_MA	350		// max allowable current before over-current state is entered
#define MAX_OC_TIME_MS	500		// max allowable time in over-current state before current limiting state is entered
#define HYSTERESIS		5		// percent duty cycle commanded by PID under last safe PWM to return to normal state

/* Variables */
static bool 	over_current_state[3];
static bool 	current_limit_state[3];
static uint8_t	max_safe_PWM[3];			// to store calculated maximum PWM duty cycle at point of entry into over-current state
static uint32_t	oc_start_time[3];		// to store time when over-current state started

/* Function prototypes */
uint8_t fsm_controller(uint8_t scp_index, float current_temp);

#endif /* INC_STATE_MACHINE_H_ */
