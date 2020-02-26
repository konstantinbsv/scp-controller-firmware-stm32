/*
 * pid.c
 *
 *  Created on: Feb. 26, 2020
 *      Author: Konstantin Borissov
 */

#include "pid.h"

// initialize constant PID lookup arrays
const float P_COEFS[] = {SCP1_P, SCP2_P, SCP3_P};
const float I_COEFS[] = {SCP1_I, SCP2_I, SCP3_I};
const float D_COEFS[] = {SCP1_D, SCP2_D, SCP3_D};

// initialize set points to default values
float setpoints[] = {DEFAULT_SETPOINT_SCP1, DEFAULT_SETPOINT_SCP2, DEFAULT_SETPOINT_SCP3};

// initialize last errors and integral terms to zero
float last_error[3]	= {0};
float integral[3]	= {0};


void SetSetpoint_SCP1(uint8_t SCP_index, float new_temp_setpoint) {
	setpoints[SCP_index] = new_temp_setpoint;
}

uint16_t updatePID(uint8_t SCP_index, float current_temp) {
	uint8_t PWM_output = 0;
	float error = setpoints[SCP_index] - current_temp; // calculate error

	// calculate p response
	float p_response = P_COEFS[SCP_index] * ( error );

	// TODO: calculate i response
	float i_response = 0;

	// TODO: calculate d response
	float d_response = D_COEFS[SCP_index] * ( last_error[SCP_index] - error );

	// final PWM output is sum of all responses
	PWM_output = (uint8_t)( p_response + i_response + d_response);

	// limit duty cycle to [0%; 100%]
	if ( PWM_output > 100 ) {
		PWM_output = 100;
	}
	if ( PWM_output < 0 ) {
		PWM_output = 0;
	}

	switch (SCP_index)
	{
	case SCP1_INDEX:
		SetPWM_SCP1(PWM_output);
		break;
	case SCP2_INDEX:
		SetPWM_SCP2(PWM_output);
	  	break;
	case SCP3_INDEX:
		SetPWM_SCP3(PWM_output);
		break;
	default:
		// set all PWMs to 0
		SetPWM_SCP1(0);
		SetPWM_SCP2(0);
		SetPWM_SCP3(0);
		break;
	}

	// update last error (error that will be used next time for integral)
	// to be error we just calculated
	last_error[SCP_index] = error;

	return PWM_output;
}

