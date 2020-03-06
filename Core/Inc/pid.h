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
#define DEFAULT_SETPOINT_SCP1	35
#define DEFAULT_SETPOINT_SCP2	45
#define DEFAULT_SETPOINT_SCP3	45

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
#define	SCP3_P	10

// I (Integral) - constant
#define	SCP1_I  0.5f
#define	SCP2_I	0.08f
#define	SCP3_I	0.08f
//integrator wind-up prevention
#define MAX_I 	50


// D (Derivative) - constant
#define	SCP1_D	30
#define	SCP2_D	5
#define	SCP3_D	10


/* Constant lookup arrays */
static const float P_COEFS[];
static const float I_COEFS[];
static const float D_COEFS[];

/* Variables */
static uint16_t setpoints[];
static float last_error[];
static float integral[];

/* Function Prototypes */
void SetSetpoint(uint8_t SCP_index, uint16_t new_temp_setpoint);
uint16_t updatePID(uint8_t SCP_index, float current_temp);

#endif /* INC_PID_H_ */
