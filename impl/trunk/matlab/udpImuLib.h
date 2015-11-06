/*!
 * \file udpImuLib.h
 */
#ifndef HAL_MATLAB_UDPIMULIB_H
#define HAL_MATLAB_UDPIMULIB_H

#include "udpLib.h"
#include "../hal/IMU/imu.h"

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/20
 *
 * \brief	Container for time-stamped IMU state data
 * \details	Since the Udp-Lib is considered to handle a soft realtime
 * 			connection, the IMU state data is considered to be time-
 * 			stamped. This structure encapsulates a precise timestamp
 * 			and IMU state vector.
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
typedef struct{
	struct timespec				timestamp_st;
	halImu_orientationValues	imuState_st;
} halMatlab_rtImuPayload;

/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/05/16
 *
 * DESCRIPTION:
 * Interfaces to access an opened socket (send and receive) with
 * IMU-specific data.
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
unsigned int g_halMatlab_sendImuState_bl(	int f_socketHandler_i32,
											halImu_orientationValues f_imuState_st
											);

halMatlab_rtImuPayload g_halMatlab_recvImuState_bl( int f_socketHandler_i32 );

#endif //HAL_MATLAB_UDPIMULIB_H
