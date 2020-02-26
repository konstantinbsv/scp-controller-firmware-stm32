/*
 * pid.h
 *
 *  Created on: Feb. 26, 2020
 *      Author: Konstantin Borissov
 */

#ifndef INC_PID_H_
#define INC_PID_H_

/* Includes */
#include "pwm.h"

/* Constants */
// Default temperature set points
#define DEFAULT_SETPOINT_SCP1	35.0f
#define DEFAULT_SETPOINT_SCP2	35.0f
#define DEFAULT_SETPOINT_SCP3	40.0f


/* PID Constant Definitions */
// P (Proportional) - constant
enum {
	SCP1_P = 75,
	SCP2_P = 20,
	SCP3_P = 75
};

// I (Integral) - constant
enum {
	SCP1_I = 0,
	SCP2_I = 0,
	SCP3_I = 0,
};

// D (Derivative) - constant
enum {
	SCP1_D = 0,
	SCP2_D = 0,
	SCP3_D = 0,
};

/* Variables */
extern float scp1_setpoint;
extern float scp2_setpoint;
extern float scp3_setpoint;

/* Function Prototypes */
void SetSetpointSCP1(float);
void SetSetpointSCP2(float);
void SetSetpointSCP3(float);

#endif /* INC_PID_H_ */
