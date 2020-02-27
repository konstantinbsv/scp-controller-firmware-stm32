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
#define	SCP1_P	75
#define	SCP2_P	10
#define	SCP3_P	75

// I (Integral) - constant
#define	SCP1_I  0.5f
#define	SCP2_I	0.08f
#define	SCP3_I	0.3f


// D (Derivative) - constant
#define	SCP1_D	30
#define	SCP2_D	5
#define	SCP3_D	50


/* Constant lookup arrays */
extern const float P_COEFS[];
extern const float I_COEFS[];
extern const float D_COEFS[];

/* Variables */
extern float setpoints[];
extern float last_error[];
extern float integral[];

/* Function Prototypes */
uint16_t updatePID(uint8_t SCP_index, float current_temp);

#endif /* INC_PID_H_ */
