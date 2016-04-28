/*!
 * \file Imufilter.h
 */
/*
 * Imufilter.h
 *
 *  Created on: May 28, 2015
 *      Author: user
 */

#ifndef SIG_IMUFILTER_IMUFILTER_H_
#define SIG_IMUFILTER_IMUFILTER_H_


#include "../../hal/IMU/imu.h"


/* -----------------------------------------------------------------------
 * AUTHOR: Oliver Breuning (olbrgs00)
 * DATE OF CREATION: 2015/05/31
 *
 * DESCRIPTION:
 * Interface reading filtered or unfiltered IMU measured values
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
halImu_orientationValues g_sigFil_getImuValuesUnfiltered_st(void);

/* -----------------------------------------------------------------------
 * AUTHOR: Oliver Breuning (olbrgs00)
 * DATE OF CREATION: 2015/05/31
 *
 * DESCRIPTION:
 * Bypass the initialization trigger to the IMU
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
unsigned int g_SigFil_initImuSensors_bl(void);

/* -----------------------------------------------------------------------
 * AUTHOR: Oliver Breuning (olbrgs00)
 * DATE OF CREATION: 2015/05/31
 *
 * DESCRIPTION:
 * Trigger reading of IMU values, correct the Offset of the Gyroscope
 * and convert magnetic values from Tesla to µTesla
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
void g_sigFil_readImuData_bl(void);

#endif /* SIG_IMUFILTER_IMUFILTER_H_ */
