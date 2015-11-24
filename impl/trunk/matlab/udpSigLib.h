/*!
 * \file udpSigLib.h
 */
#ifndef HAL_MATLAB_UDPIMULIB_H
#define HAL_MATLAB_UDPIMULIB_H

#include "udpLib.h"
#include "../sig/Orientation/Orientation.h"
#include "../hal/IMU/imu.h"

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/06/01
 *
 * \brief	Container for time-stamped SIGNAL layer state data
 * \details	Since the Udp-Lib is considered to handle a soft realtime
 * 			connection, the SIG state data is considered to be time-
 * 			stamped. This structure encapsulates a precise timestamp
 * 			and SIGNAL layer state vector.
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
typedef struct{
	struct timespec				timestamp_st;
	sigOri_orientationAngles	sigState_st;
} halMatlab_rtSigPayload;


typedef struct{
	struct timespec				timestamp_st;
#if defined(__host__)
	double 						dummy; // this is to pad, because struct timespec on host ( 64 bit ) > struct timespec on target ( 32 bit )
#endif
	halImu_orientationValues	imuState_st;
	sigOri_orientationAngles	kalmanSigState_st;
	sigOri_orientationAngles	complementarySigState_st;
} halMatlab_rtSigAllStatePayload;

typedef struct {
	struct timespec timestamp_st;
#if defined(__host__)
	double 						dummy; // this is to pad, because struct timespec on host ( 64 bit ) > struct timespec on target ( 32 bit )
#endif
	sigOri_orientationAngles    angularVelocityGyroFromImu_st;
	sigOri_orientationAngles    angleFromGyroStepCalculation_st;
	sigOri_orientationAngles    angleFromAccMagCalculation_st;
	sigOri_orientationAngles	angleFromcomplementarySigState_st;
	sigOri_orientationAngles	angleFromkalmanSigState_st;

} halMatlab_rtSigRollPitchYawStatePayload;


/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/06/01
 *
 * DESCRIPTION:
 * Interfaces to access an opened socket (send and receive) with
 * Signal-Layer-specific data.
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
unsigned int g_halMatlab_sendSigState_bl(	int f_socketHandler_i32,
											sigOri_orientationAngles f_sigState_st
											);
unsigned int g_halMatlab_sendSigAllStates_bl(	int f_socketHandler_i32,
												halImu_orientationValues f_rawImuState_st,
												sigOri_orientationAngles f_sigKalmanState_st,
												sigOri_orientationAngles f_sigComplementaryState_st
											);
halMatlab_rtSigPayload g_halMatlab_recvSigState_bl( int f_socketHandler_i32 );

halMatlab_rtSigAllStatePayload g_halMatlab_recvSigAllStates_bl( int f_socketHandler_i32 );

#endif //HAL_MATLAB_UDPIMULIB_H
