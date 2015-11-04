/*!
 * \file main.c
 */
/*
 * main.cpp
 *
 *  Created on: 29.03.2015
 *      Author: user
 */
#include <unistd.h>
#include <stdio.h>
#include "./hal/IMU/imu.h"
#include "./matlab/udpImuLib.h"

int main (void)
{
	unsigned char	l_remoteHostAddr_rg4ui8[4] 	= {192,168,22,160};
	unsigned short	l_remoteHostPort_ui16		= 5000;
	int				l_udpSocket_i32;
	unsigned int	l_sendState_bl;

  // open udp connection
	l_udpSocket_i32 = g_halMatlab_initConnection_i32( l_remoteHostAddr_rg4ui8, l_remoteHostPort_ui16 );

	halImu_orientationValues l_imuMeasurements_st;
	g_halImu_initImuSensors_bl();

	while(1)
	{
		g_halImu_triggerImuReading_bl();
		g_halImu_triggerBaroReading_bl();
		g_halImu_triggerGyroReading_bl();
		g_halImu_triggerAccReading_bl();

		l_imuMeasurements_st=g_halImu_getImuValues_str();

		l_sendState_bl = g_halMatlab_sendImuState_bl(l_udpSocket_i32, l_imuMeasurements_st);
		if ( l_sendState_bl != M_HAL_MATLAB_SUCCESS_UI8 )
		{
			printf("UDP-Packet error\n");
		}

		usleep( 20000 ); //20ms = 50Hz
	}

  // close udp connection
  g_halMatlab_closeSocket_bl(l_udpSocket_i32);

	return 0;
}



