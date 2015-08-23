/*!
 * \file main.c
 */
/*
 * main.cpp
 *
 *  Created on: 29.03.2015
 *      Author: user
 */

#include <stdio.h>
#include "./hal/IMU/imu.h"


int main (void)
{

	halImu_orientationValues l_imuMeasurements_st;
	g_halImu_initImuSensors_bl();

	while(1)
	{
		g_halImu_triggerImuReading_bl();
		g_halImu_triggerBaroReading_bl();
		g_halImu_triggerGyroReading_bl();
		g_halImu_triggerAccReading_bl();

		l_imuMeasurements_st=g_halImu_getImuValues_str();

		printf("Pressure: %5.3f    ;    Temperature:  %5.3f\n",l_imuMeasurements_st.pressure_f64,l_imuMeasurements_st.temperature_f64);
		printf("yaw: %5.3f ; pitch:  %5.3f ; roll:  %5.3f\n",l_imuMeasurements_st.gyro.l_yaw_f64,l_imuMeasurements_st.gyro.l_pitch_f64,l_imuMeasurements_st.gyro.l_roll_f64);
		printf("X: %5.3f ; Y:  %5.3f ; Z:  %5.3f\n",l_imuMeasurements_st.acc.x_f64,l_imuMeasurements_st.acc.y_f64,l_imuMeasurements_st.acc.z_f64);
		printf("X: %5.10f ; Y:  %5.10f ; Z:  %5.10f\n\n\n\n",l_imuMeasurements_st.mag.x_f64,l_imuMeasurements_st.mag.y_f64,l_imuMeasurements_st.mag.z_f64);
	}


	return 0;
}



