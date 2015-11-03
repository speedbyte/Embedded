/*!
 * \file batteryCheck.h
 */
/*
 * batteryCheck.h
 *
 *  Created on: May 14, 2015
 *      Author: user
 */

#ifndef HAL_BATTERYCHECK_BATTERYCHECK_H_
#define HAL_BATTERYCHECK_BATTERYCHECK_H_


#define M_HAL_BATCHECK_SUCCESS_BL			0
#define M_HAL_BATCHECK_FAILED_BL			1

/* ---------------------------------------------
AUTHOR: Oliver Breuning (olbrgs00)
DATE OF CREATION: 2015/05/14

INPUT PARAMS: --
OUTPUT: --

DESCRIPTION:
Get interface for measured battery value
Return is a float value of the voltage
CHANGELOG:
none
--------------------------------------------- */
double g_halBatCheck_getBatteryStatus_f64(void);


/* ---------------------------------------------
AUTHOR: Oliver Breuning (olbrgs00)
DATE OF CREATION: 2015/05/14

INPUT PARAMS: --
OUTPUT: --

DESCRIPTION:
Trigger reading from ADC over I2C
CHANGELOG:
none
--------------------------------------------- */
unsigned int  g_halBatCheck_readBatStatusFromI2C_i32(void);

#endif /* HAL_BATTERYCHECK_BATTERYCHECK_H_ */
