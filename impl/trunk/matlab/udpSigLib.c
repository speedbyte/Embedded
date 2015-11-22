/*!
 * \file udpSigLib.c
 */
#include <string.h>

#ifdef __linux__
	#include<time.h>
#endif

#include "udpSigLib.h"

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/06/01
 *
 * \brief	Sends a packet of IMU data with the current unuix-timestamp
 * 			via a given UDP-Socket
 * \details	This function sends a data packet with the given IMU state
 * 			via a given UDP-Socket. The	current timestamp is added to
 * 			the payload to get some sort of	realtime behavior.\n
 * 			This can be used to perform	a Software-in -the-Loop setup
 * 			or test specific filter	algorithms in MATLAB.\n
 * 			It is recommended to open the neccessary UDP-socket with
 * 			g_halMatlab_initSocket_i32() or
 * 			g_halMatlab_initConnection_i32().
 *
 * 	\param[in]	f_socketHandler_i32 specifies socket handler number used
 * 				for the data transmission
 * 	\param[in]	f_imuState_st is a the IMU state packed into a custom
 * 				struct type (type: halImu_orientationValues)
 * 	\param[out] returns a boolean value, indicating the occurrence of
 * 				failures\n
 * 				0 .... indicates success (no errors)\n
 * 				1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halMatlab_sendSigState_bl(	int f_socketHandler_i32,
											sigOri_orientationAngles f_sigState_st )
{

	halMatlab_rtSigPayload	l_rtSigPayload_st;
	struct timespec			l_timestamp_st;

	/*
	 * first of all: get an accurate timestamp for this data telegram
	 * Hint: ensure that 'librt' is also linked in the project!
	 *       Eclipse: Goto Project->Properties.
	 *                Select C/C++-Build->Settings
	 *                Select tab view 'Tool Settings'.
	 *                Select 'Cross G++ Linker'->Libraries
	 *                and add the entry 'rt' to 'Libraries (-l)'
	 *
	 *       GCC on the commandline: simply add '-lrt' to your gcc options
	 */
	if ( clock_gettime(CLOCK_REALTIME, &l_timestamp_st) != M_HAL_MATLAB_SUCCESS_UI8)
	{
		return M_HAL_MATLAB_FAILED_UI8;
	}

	//assmeble timestamp and
	l_rtSigPayload_st.timestamp_st 	= l_timestamp_st;
	l_rtSigPayload_st.sigState_st	= f_sigState_st;

	return g_halMatlab_sendPacket_bl( 	f_socketHandler_i32,
										(unsigned char*)&l_rtSigPayload_st,
										sizeof( l_rtSigPayload_st ) );
}

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/06/01
 *
 * \brief	Sends a packet of IMU data with the current unuix-timestamp
 * 			via a given UDP-Socket
 * \details	This function sends a data packet with the given IMU state
 * 			via a given UDP-Socket. The	current timestamp is added to
 * 			the payload to get some sort of	realtime behavior.\n
 * 			This can be used to perform	a Software-in -the-Loop setup
 * 			or test specific filter	algorithms in MATLAB.\n
 * 			It is recommended to open the neccessary UDP-socket with
 * 			g_halMatlab_initSocket_i32() or
 * 			g_halMatlab_initConnection_i32().
 *
 * 	\param[in]	f_socketHandler_i32 specifies socket handler number used
 * 				for the data transmission
 * 	\param[in]	f_imuState_st is a the IMU state packed into a custom
 * 				struct type (type: halImu_orientationValues)
 * 	\param[out] returns a boolean value, indicating the occurrence of
 * 				failures\n
 * 				0 .... indicates success (no errors)\n
 * 				1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halMatlab_sendSigAllStates_bl(	int f_socketHandler_i32,
												halImu_orientationValues f_rawImuState_st,
												sigOri_orientationAngles f_sigKalmanState_st,
												sigOri_orientationAngles f_sigComplementaryState_st )
{

	halMatlab_rtSigAllStatePayload	l_rtCompleteSigPayload_st;
	struct timespec					l_timestamp_st;

	/*
	 * first of all: get an accurate timestamp for this data telegram
	 * Hint: ensure that 'librt' is also linked in the project!
	 *       Eclipse: Goto Project->Properties.
	 *                Select C/C++-Build->Settings
	 *                Select tab view 'Tool Settings'.
	 *                Select 'Cross G++ Linker'->Libraries
	 *                and add the entry 'rt' to 'Libraries (-l)'
	 *
	 *       GCC on the commandline: simply add '-lrt' to your gcc options
	 */
	if ( clock_gettime(CLOCK_REALTIME, &l_timestamp_st) != M_HAL_MATLAB_SUCCESS_UI8)
	{
		return M_HAL_MATLAB_FAILED_UI8;
	}

	//assmeble timestamp and
	l_rtCompleteSigPayload_st.timestamp_st 				= l_timestamp_st;
	l_rtCompleteSigPayload_st.imuState_st				= f_rawImuState_st;
	l_rtCompleteSigPayload_st.kalmanSigState_st 		= f_sigKalmanState_st;
	l_rtCompleteSigPayload_st.complementarySigState_st	= f_sigComplementaryState_st;

	return g_halMatlab_sendPacket_bl( 	f_socketHandler_i32,
										(unsigned char*)&l_rtCompleteSigPayload_st,
										sizeof( l_rtCompleteSigPayload_st ) );
}

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/06/01
 *
 * \brief	Receives a packet of SIG data with the current via a given
 * 			UDP-Socket
 * \details	This function receives a data packet with a synthetic SIG
 * 			state via a given UDP-Socket. This can be used to perform
 * 			a Software-in -the-Loop setup or test specific filter
 * 			algorithms in MATLAB.\n
 * 			It is recommended to open the neccessary UDP-socket with
 * 			g_halMatlab_initSocket_i32() or
 * 			g_halMatlab_initConnection_i32().
 *
 * 	\param[in]	f_socketHandler_i32 specifies socket handler number used
 * 				for the data transmission
 * 	\param[out] returns the received synthetic SIG state packed into a
 * 				custom struct type with timestamp
 * 				(type: halMatlab_rtSigPayload)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
halMatlab_rtSigPayload g_halMatlab_recvSigState_bl( int f_socketHandler_i32 ) {
	halMatlab_rtSigPayload 		l_recvSigState_st;
	unsigned char				l_recvBuffer_rgXui8[ sizeof(halMatlab_rtSigPayload) ];
	unsigned int				l_recvBytesNumber_ui32;

	// zero all values
	l_recvSigState_st.timestamp_st.tv_sec 	= 0;
	l_recvSigState_st.timestamp_st.tv_nsec 	= 0;

	l_recvSigState_st.sigState_st.pitch_f64 = 0;
	l_recvSigState_st.sigState_st.roll_f64 	= 0;
	l_recvSigState_st.sigState_st.yaw_f64 	= 0;


	// receive packet
	l_recvBytesNumber_ui32 = g_halMatlab_recvPacket_ui32(	f_socketHandler_i32,
															l_recvBuffer_rgXui8,
															sizeof(halMatlab_rtSigPayload) );

	if ( l_recvBytesNumber_ui32 == sizeof(halMatlab_rtSigPayload) )
	{
		memcpy( &l_recvSigState_st, &l_recvBuffer_rgXui8, sizeof(halMatlab_rtSigPayload));
	}

	return l_recvSigState_st;
}

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/06/01
 *
 * \brief	Receives a packet of SIG data with the current via a given
 * 			UDP-Socket
 * \details	This function receives a data packet with a synthetic SIG
 * 			state via a given UDP-Socket. This can be used to perform
 * 			a Software-in -the-Loop setup or test specific filter
 * 			algorithms in MATLAB.\n
 * 			It is recommended to open the neccessary UDP-socket with
 * 			g_halMatlab_initSocket_i32() or
 * 			g_halMatlab_initConnection_i32().
 *
 * 	\param[in]	f_socketHandler_i32 specifies socket handler number used
 * 				for the data transmission
 * 	\param[out] returns the received synthetic SIG state packed into a
 * 				custom struct type with timestamp
 * 				(type: halMatlab_rtSigPayload)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
halMatlab_rtSigAllStatePayload g_halMatlab_recvSigAllStates_bl( int f_socketHandler_i32 ) {
	halMatlab_rtSigAllStatePayload 		l_recvSigAllStates_st;
	unsigned char				              l_recvBuffer_rgXui8[ sizeof(halMatlab_rtSigAllStatePayload) ];
	unsigned int				              l_recvBytesNumber_ui32;

	// zero all values
	l_recvSigAllStates_st.timestamp_st.tv_sec 	= 0;
	l_recvSigAllStates_st.timestamp_st.tv_nsec 	= 0;

    l_recvSigAllStates_st.imuState_st.acc.x_f64       = 0;
    l_recvSigAllStates_st.imuState_st.acc.y_f64       = 0;
    l_recvSigAllStates_st.imuState_st.acc.z_f64       = 0;
  
    l_recvSigAllStates_st.imuState_st.mag.x_f64       = 0;
    l_recvSigAllStates_st.imuState_st.mag.y_f64       = 0;
    l_recvSigAllStates_st.imuState_st.mag.z_f64       = 0;
  
    l_recvSigAllStates_st.imuState_st.gyro.l_pitch_f64  = 0;
	l_recvSigAllStates_st.imuState_st.gyro.l_roll_f64 	= 0;
	l_recvSigAllStates_st.imuState_st.gyro.l_yaw_f64 	  = 0;
  
    l_recvSigAllStates_st.imuState_st.temperature_f64 = 0;
    l_recvSigAllStates_st.imuState_st.pressure_f64    = 0;
  
	l_recvSigAllStates_st.kalmanSigState_st.pitch_f64 = 0;
	l_recvSigAllStates_st.kalmanSigState_st.roll_f64 	= 0;
	l_recvSigAllStates_st.kalmanSigState_st.yaw_f64 	= 0;

    l_recvSigAllStates_st.complementarySigState_st.pitch_f64 = 0;
	l_recvSigAllStates_st.complementarySigState_st.roll_f64 	= 0;
	l_recvSigAllStates_st.complementarySigState_st.yaw_f64 	= 0;

	// receive packet
	l_recvBytesNumber_ui32 = g_halMatlab_recvPacket_ui32(	f_socketHandler_i32,
															l_recvBuffer_rgXui8,
															sizeof(halMatlab_rtSigAllStatePayload) );

	if ( l_recvBytesNumber_ui32 == sizeof(halMatlab_rtSigAllStatePayload) )
	{
		memcpy( &l_recvSigAllStates_st, &l_recvBuffer_rgXui8, sizeof(halMatlab_rtSigAllStatePayload));
	}

	return l_recvSigAllStates_st;
}
