/*
 * state_machine.c
 *
 *  Created on: Mar. 6, 2020
 *      Author: Konstantin Borissov
 */

#include "state_machine.h"

/* Initialize variables */
static bool 	over_current_state[3] 	= {false};
static bool 	current_limit_state[3]	= {false};
static uint8_t	safe_PWM[3] = {0};
static uint16_t	oc_time[3]	= {0};


/**
 * @param scp_index 	index of SCP fiber
 * @param current temp 	current temperature of scp fiber
 *
 * @return PWM duty cycle output from 0% to 100%
 */
uint8_t controller(uint8_t scp_index, float current_temp) {

	// get PWM output from PID

	// get current, if current > MAX_CURRENT, start count, save safePWM, set OC flag
			// if count start, and MAX_OC_TIME elapsed, go into current_limit mode (set safePWM)
			// if current < MAX_CURRENT, stop count

		// if PWM_output < last_safe_PWM, exit current_limit mode

}
