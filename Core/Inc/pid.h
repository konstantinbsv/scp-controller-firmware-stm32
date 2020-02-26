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

// Indices for SCPs
enum {
	SCP1_INDEX = 0,
	SCP2_INDEX = 1,
	SCP3_INDEX = 2
};


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

/* Constant lookup arrays */
extern const float P_COEFS[];
extern const float I_COEFS[];
extern const float D_COEFS[];

/* Variables */
extern float setpoints[];

/* Function Prototypes */
uint16_t updatePID(uint8_t SCP_index, float current_temp);

#endif /* INC_PID_H_ */
