/*!
 * \file udpSensorLib.h
 */
#ifndef HAL_MATLAB_UDPIMULIB_H
#define HAL_MATLAB_UDPIMULIB_H

#include "udpLib.h"
#include "Orientation.h"
#include "../hal/IMU/imu.h"

typedef struct{
	struct timespec				timestamp_st;
	HAL_ANGLE_PAYLOAD_ST	sigState_st;
} HAL_RT_ANGLE_PAYLOAD_ST;


typedef struct{
	struct timespec				timestamp_st;
	HAL_SENSOR_PAYLOAD_ST	sensorValues_st;
	HAL_ANGLE_PAYLOAD_ST	kalmanSigState_st;
	HAL_ANGLE_PAYLOAD_ST	complementarySigState_st;
} HAL_RT_SENSOR_PAYLOAD_FUSION_ST;

typedef struct {
	struct timespec timestamp_st;
	HAL_ANGLE_PAYLOAD_ST    angularVelocityGyroFromImu_st;
	HAL_ANGLE_PAYLOAD_ST    angleFromGyroStepCalculation_st;
	HAL_ANGLE_PAYLOAD_ST    angleFromAccMagCalculation_st;
	HAL_ANGLE_PAYLOAD_ST	angleFromcomplementarySigState_st;
	HAL_ANGLE_PAYLOAD_ST	angleFromkalmanSigState_st;

} HAL_RT_ANGLE_CALCULATED_ST;

typedef struct{
	struct timespec				timestamp_st;
	HAL_SENSOR_PAYLOAD_ST	sensorValues_st;
} HAL_RT_SENSOR_PAYLOAD_ST;


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
unsigned int g_hal_send_angles_raw_bool( int f_socketHandler_i32,
					  HAL_ANGLE_PAYLOAD_ST f_sigState_st
					  );

unsigned int g_hal_send_all_angles_calculated_bool( int f_socketHandler_i32,
					      HAL_SENSOR_PAYLOAD_ST f_rawsensorValues_st,
					      HAL_ANGLE_PAYLOAD_ST f_sigKalmanState_st,
					      HAL_ANGLE_PAYLOAD_ST f_sigComplementaryState_st
					      );
HAL_RT_ANGLE_PAYLOAD_ST g_hal_receive_angles_raw_bool( int f_socketHandler_i32 );

HAL_RT_SENSOR_PAYLOAD_FUSION_ST g_hal_receive_angles_calculated_bool( int f_socketHandler_i32 );


unsigned int g_hal_send_sensor_raw_bool(int f_socketHandler_i32,
					     HAL_SENSOR_PAYLOAD_ST f_sensorValues_st);

HAL_RT_SENSOR_PAYLOAD_ST g_hal_receive_sensor_raw_bool( int f_socketHandler_i32 );

HAL_SENSOR_PAYLOAD_ST g_hal_receive_sensor_raw_no_time_bool( int f_socketHandler_i32 );


#endif //HAL_MATLAB_UDPIMULIB_H
