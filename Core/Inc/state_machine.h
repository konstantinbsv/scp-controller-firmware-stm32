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
#define MAX_CURRENT_MA	750		// max allowable current before over-current state is entered
#define MAX_OC_TIME_MS	500		// max allowable time in over-current state before current limiting state is entered

/* Variables */
static bool 	over_current_state[3];
static bool 	current_limit_state[3];
static uint8_t	safe_PWM[3];			// to store max safe PWM duty cycle at point of entry into over-current state
static uint16_t	oc_time[3];				// to store time spent in over-current state

#endif /* INC_STATE_MACHINE_H_ */
