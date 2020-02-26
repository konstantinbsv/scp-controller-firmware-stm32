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

/* Function Prototypes */


#endif /* INC_PID_H_ */
