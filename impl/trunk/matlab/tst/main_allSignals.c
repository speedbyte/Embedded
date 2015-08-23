/*!
 * \file main.c
 */
#include <unistd.h>
#include <stdio.h>
#include "sig/Orientation/Orientation.h"
#include "matlab/udpSigLib.h"

int main (void)
{
	unsigned char	l_remoteHostAddr_rg4ui8[4] 	= {192,168,22,160};
	unsigned short	l_remoteHostPort_ui16		= 5000;
	int				l_udpSocket_i32;
	unsigned int	l_sendState_bl;

	sigOri_orientationAngles	l_kalmanAngles_st;
	sigOri_orientationAngles	l_compAngles_st;
	halImu_orientationValues	l_imuStates_st;

	l_udpSocket_i32 = g_halMatlab_initConnection_i32( l_remoteHostAddr_rg4ui8, l_remoteHostPort_ui16 );

	g_sigOri_initMatrices_bl();
	g_sigOri_initImuSensors_bl();

	while(1)
	{
		g_sigOri_calcKalmanOrientation_bl();
		g_sigOri_calcComplementaryOrientation_bl();

		l_kalmanAngles_st 	= g_sigOri_getAnglesKalman_bl();
		l_compAngles_st		= g_sigOri_getAnglesComplementary_bl();
		l_imuStates_st 		= g_halImu_getImuValues_str();

		l_sendState_bl = g_halMatlab_sendSigAllStates_bl(	l_udpSocket_i32,
															l_imuStates_st,
															l_kalmanAngles_st,
															l_compAngles_st);
		if ( l_sendState_bl != M_HAL_MATLAB_SUCCESS_UI8 )
		{
			printf("UDP-Packet error\n");
		}else{
			printf("Sent packet\n");
		}

		usleep( 20000 ); //20ms = 50Hz
	}


	return 0;
}



