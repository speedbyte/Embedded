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

#include "./accMag/accMag.h"
#include "./gyro/Gyro.h"
#include "../../sig/Orientation/Orientation.h"


#define M_HAL_IMU_SUCCESS_BL			0
#define M_HAL_IMU_FAILED_BL				1

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
	halAccmag_3dDoubleVector acc;
	halAccmag_3dDoubleVector mag;
	sigOri_orientationAngles gyro;
	double temperature_f64;
	double pressure_f64;
} halImu_orientationValues;


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
halImu_orientationValues g_halImu_getImuValues_str(void);

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
unsigned int g_halImu_initImuSensors_bl(void);


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
unsigned int g_halImu_triggerImuReading_bl(void);
unsigned int g_halImu_triggerBaroReading_bl(void);
unsigned int g_halImu_triggerGyroReading_bl(void);
unsigned int g_halImu_triggerAccReading_bl(void);
unsigned int g_halImu_triggerMagReading_bl(void);



#endif /* HAL_IMU_IMU_H_ */
