/*!
 * \file imu.h
 */
/*
 * imu.h
 *
 *  Created on: May 11, 2015
 *      Author: user
 */

#ifndef HAL_IMU_IMU_H_
#define HAL_IMU_IMU_H_

#include "accMag.h"
#include "Gyro.h"
#include "Orientation.h"


#define M_HAL_IMU_SUCCESS_BOOL 		0
#define M_HAL_IMU_FAILED_BOOL 			1

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/13
 *
 * \brief	Inertial measurement unit values
 * \details	Stores all sensor values from the Inertial measurement unit within
 * 			one dedicated type. All values within are floats
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
typedef struct{
#if defined(__host__)
	double 						dummy; // this is to pad, because struct timespec on host ( 64 bit ) > struct timespec on target ( 32 bit )
#endif
	halAccmag_3dDoubleVector acc;
	halAccmag_3dDoubleVector mag;
	HAL_ANGLE_PAYLOAD_ST gyro;
	double temperature_f64;
	double pressure_f64;
} HAL_SENSOR_PAYLOAD_ST;


/* -----------------------------------------------------------------------
 * AUTHOR: Oliver Breuning (olbrgs00)
 * DATE OF CREATION: 2015/05/14
 *
 * DESCRIPTION:
 * Interface reading IMU measured values
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
HAL_SENSOR_PAYLOAD_ST g_halImu_getsensorValues_str(void);

/* -----------------------------------------------------------------------
 * AUTHOR: Oliver Breuning (olbrgs00)
 * DATE OF CREATION: 2015/05/13
 *
 * DESCRIPTION:
 * Trigger initialization of all mounted sensors
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
unsigned int g_halImu_initImuSensors_bool(void);


/* -----------------------------------------------------------------------
 * AUTHOR: Oliver Breuning (olbrgs00)
 * DATE OF CREATION: 2015/05/13
 *
 * DESCRIPTION:
 * Trigger reading of sensors
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
unsigned int g_halImu_triggerImuReading_bool(void);
unsigned int g_halImu_triggerBaroReading_bool(void);
unsigned int g_halImu_triggerGyroReading_bool(void);
unsigned int g_halImu_triggerAccReading_bool(void);
unsigned int g_halImu_triggerMagReading_bool(void);



#endif /* HAL_IMU_IMU_H_ */
