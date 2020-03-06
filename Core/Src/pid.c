/*
 * pid.c
 *
 *  Created on: Feb. 26, 2020
 *      Author: Konstantin Borissov
 */

#include "pid.h"
#include "serial.h"

// initialize constant PID lookup arrays
static float Kp[] = {SCP1_P, SCP2_P, SCP3_P};
static float Ki[] = {SCP1_I, SCP2_I, SCP3_I};
static float Kd[] = {SCP1_D, SCP2_D, SCP3_D};

// initialize set points to default values
static uint16_t setpoints[] = {DEFAULT_SETPOINT_SCP1, DEFAULT_SETPOINT_SCP2, DEFAULT_SETPOINT_SCP3};

// initialize last errors and integral terms to zero
static float last_error[3]	= {0};
static float integral[3]	= {0};


void SetSetpoint(uint8_t SCP_index, uint16_t new_temp_setpoint) {
	setpoints[SCP_index] = new_temp_setpoint;
}

uint16_t updatePID(uint8_t scp_index, float current_temp) {
	uint8_t PWM_output = 0;
	uint16_t setpoint = setpoints[scp_index];	// get setpoint from array

	// if channel is disabled, skip it
	if (setpoint == 0) {
		return SetPWM(scp_index, 0); // PWM set to 0 for that SCP
	}

	float error = setpoint - current_temp; // calculate error

	// calculate p response
	float p_response = Kp[scp_index] * ( error );

	// update integral calculation
	integral[scp_index] = integral[scp_index] + error;
	// TODO: calculate i response
	float i_response = Ki[scp_index] * ( integral[scp_index] );
	// prevent integrator wind-up
	if (integral[scp_index] > MAX_I) {
		integral[scp_index] = MAX_I;
	}
	if (integral[scp_index] < -MAX_I) {
		integral[scp_index] = -MAX_I;
	}

	// TODO: calculate d response
	float d_response = Kd[scp_index] * ( error - last_error[scp_index] );

	// final PWM output is sum of all responses
	PWM_output = (uint8_t)( p_response + i_response + d_response);

	// limit duty cycle to [0%; 100%]
	if ( PWM_output > 100 ) {
		PWM_output = 100;
	}
	if ( PWM_output < 0 ) {
		PWM_output = 0;
	}

	SetPWM(scp_index, PWM_output);

	// update last error (error that will be used next time for integral)
	// to be error we just calculated
	last_error[scp_index] = error;

	return PWM_output;
}

