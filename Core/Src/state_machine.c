/*
 * state_machine.c
 *
 *  Created on: Mar. 6, 2020
 *      Author: Konstantin Borissov
 */

#include "state_machine.h"

/* Initialize variables */
static bool 	over_current_state[3]	= {false};
static bool 	current_limit_state[3]	= {false};
static uint8_t	max_safe_PWM[3] 		= {0};
static uint32_t	oc_start_time[3]		= {0};


/**
 * @brief Finite state machine controller
 *
 * @param scp_index 	index of SCP fiber
 * @param current temp 	current temperature of scp fiber
 *
 * @retval PWM duty cycle output from 0% to 100%
 */
uint8_t fsm_controller(uint8_t scp_index, float current_temp) {

	// get PWM duty cycle output from PID
	uint8_t duty_cycle = updatePID(scp_index, current_temp); // read duty cycle commanded by PID algorithm

	// get current
	float current = GetCurrent_mA(INA219_ADDRESSES[scp_index]); // get INA219 address from address array in ina219 library

	// if exceeding maximum allowable current and in normal state
	if (current > MAX_CURRENT_MA && !over_current_state[scp_index] && !current_limit_state[scp_index]) {
			max_safe_PWM[scp_index] = (MAX_CURRENT_MA / current ) * duty_cycle;		// calculate max safe PWM
			oc_start_time[scp_index] = HAL_GetTick();								// save start time
			over_current_state[scp_index] = true; 									// enter over-current state
	}
	// if maximum over-current time has elapsed, go into current limit state
	if (( HAL_GetTick() - oc_start_time[scp_index] ) > MAX_OC_TIME_MS && over_current_state[scp_index]) {
		// duty_cycle = max_safe_PWM[scp_index];	// set duty cycle as last safe duty cycle
		over_current_state[scp_index] = false; 	// exit over-current state
		current_limit_state[scp_index] = true; 	// enter current limit state
	}

	// if not in normal state
	if (over_current_state[scp_index] || current_limit_state[scp_index]) {
		// and if PID commands PWM duty cycle below last safe PWM minus hysteresis
		if (duty_cycle < max_safe_PWM[scp_index] - HYSTERESIS || duty_cycle == 0) {
			over_current_state[scp_index]	= false;	// exit over-current state
			current_limit_state[scp_index]	= false;	// exit current limit state
			// FSM will now be in normal state
		}
	}

	// set duty cycle according to state
	duty_cycle = current_limit_state[scp_index] ? max_safe_PWM[scp_index] : duty_cycle;
	// output duty cycle
	SetPWM(scp_index, duty_cycle);

	return duty_cycle;
}
