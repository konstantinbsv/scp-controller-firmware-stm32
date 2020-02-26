/*
 * pid.c
 *
 *  Created on: Feb. 26, 2020
 *      Author: Konstantin Borissov
 */

#include "pid.h"


// initialize set points with default values
float scp1_setpoint = DEFAULT_SETPOINT_SCP1;
float scp2_setpoint = DEFAULT_SETPOINT_SCP2;
float scp3_setpoint = DEFAULT_SETPOINT_SCP3;


void SetSetpointSCP1(float temp_setpoint) {
	scp1_setpoint = temp_setpoint;
}

void SetSetpointSCP2(float temp_setpoint) {
	scp2_setpoint = temp_setpoint;
}

void SetSetpointSCP3(float temp_setpoint) {
	scp3_setpoint = temp_setpoint;
}

