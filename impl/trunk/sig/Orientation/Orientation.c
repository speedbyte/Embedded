/*!
 * \file Orientation.c
 */
/*
 * Orientation.c
 *
 *  Created on: May 17, 2015
 *      Author: user
 */


#include <math.h>
#include <sys/time.h>
#include "Orientation.h"
#include "OrientationDefines.h"
#include "../../hal/IMU/imu.h"
#include "../ImuFilter/Imufilter.h"
#include "../matrixLib/matrixLib.h"

//define the complementary filter coefficient
#define M_COMP_FILTER_FACTOR_F64	0.888 //<--100Hz // 50Hz --> 0.941 //4Hz --> 0.995	//0 --> only Acc/Mag  1 --> only Gyro
//define the convert value from radiant to degree
#define M_RAD_TO_DEG_F64			(180/M_SIGORI_PI_F64)
//define the number of values for reference value calculation
#define M_NR_OF_VALUES_OFFSET_I32	1000

static halImu_orientationValues m_sigori_imuValues_st;
static double m_SIGORI_heightBarometerMetres_f64 =0;
static double m_sigOri_referencePressure_f64=0;
static double m_sigOri_referenceGravity_f64=0;
static double m_sigOri_referenceTemperature_f64=0;
static double m_SIGORI_heightGpsMetres_f64 =0;
static double m_SIGORI_heightAccMetres_f64 =0;

static sigOri_orientationAngles m_sigOri_arrayOutputAnglesGyroPerStep_st;
static sigOri_orientationAngles m_sigOri_arrayOutputAnglesAccMagCalc_st;

static sigOri_orientationAngles m_sigOri_arrayAccMagAnglesKalman_st;
static sigOri_orientationAngles m_sigOri_arrayGyroAnglesKalman_st;
static sigOri_orientationAngles m_sigOri_arrayOutputAnglesKalman_st;


static sigOri_orientationAngles m_sigOri_arrayAccMagAnglesComplementary_st={0,0,0};
static sigOri_orientationAngles m_sigOri_arrayGyroAnglesComplementary_st={0,0,0};
static sigOri_orientationAngles m_sigOri_arrayOutputAnglesComplementary_st={0,0,0};


static double m_sigOri_matrixXk_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];
static double m_sigOri_matrixXnew_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];
static double m_sigOri_matrixUk_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];

static double m_sigOri_matrixI_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];
static double m_sigOri_matrixPk_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];
static double m_sigOri_matrixR_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];
static double m_sigOri_matrixQ_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];

static double m_sigOri_matrixS_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];
static double m_sigOri_matrixK_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];

//for integrating of Gyro
static struct timeval gettime_old;

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Get angles of the IMU
 * \details	This function returns a struct with calculated angles
 * 			(pitch, roll, yaw) with the
 * 			Complementary-Filter
 *
 * \param[out]	returns the requested angles calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
sigOri_orientationAngles g_sigOri_getAnglesComplementary_bl()
{
	return m_sigOri_arrayOutputAnglesComplementary_st;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Get pitch angle of the IMU
 * \details	This function returns the pitch angle calculated
 * 			with the Complementary-Filter
 *
 * \param[out]	returns the pitch angle calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_sigOri_getPitchComplementary_bl()
{
	return m_sigOri_arrayOutputAnglesComplementary_st.pitch_f64;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Get roll angle of the IMU
 * \details	This function returns the roll angle calculated
 * 			with the Complementary-Filter
 *
 * \param[out]	returns the roll angle calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_sigOri_getRollComplementary_bl()
{
	return m_sigOri_arrayOutputAnglesComplementary_st.roll_f64;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Get yaw angle of the IMU
 * \details	This function returns the yaw angle calculated
 * 			with the Complementary-Filter
 *
 * \param[out]	returns the yaw angle calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_sigOri_getYawComplementary_bl()
{
	return m_sigOri_arrayOutputAnglesComplementary_st.yaw_f64;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Get angles of the IMU
 * \details	This function returns a struct with calculated angles
 * 			(pitch, roll, yaw) with the
 * 			Kalman-Filter
 *
 * \param[out]	returns the requested angles calculate with the Kalman-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
sigOri_orientationAngles g_sigOri_getAnglesKalman_bl()
{
	return m_sigOri_arrayOutputAnglesKalman_st;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Get pitch angle of the IMU
 * \details	This function returns the pitch angle calculated
 * 			with the Kalman-Filter
 *
 * \param[out]	returns the pitch angle calculate with the Kalman-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_sigOri_getPitchKalman_bl()
{
	return m_sigOri_arrayOutputAnglesKalman_st.pitch_f64;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Get roll angle of the IMU
 * \details	This function returns the roll angle calculated
 * 			with the Kalman-Filter
 *
 * \param[out]	returns the roll angle calculate with the Kalman-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_sigOri_getRollKalman_bl()
{
	return m_sigOri_arrayOutputAnglesKalman_st.roll_f64;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Get yaw angle of the IMU
 * \details	This function returns the yaw angle calculated
 * 			with the Kalman-Filter
 *
 * \param[out]	returns the yaw angle calculate with the Kalman-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_sigOri_getYawKalman_bl()
{
	return m_sigOri_arrayOutputAnglesKalman_st.yaw_f64;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Bypass the initialization of the IMU
 * \details	Bypasses the initialization trigger to the ImuFilter
 *
 * \param[out] returns a boolean value, indicating the occurrence of
 * 			   failures\n
 * 				0 .... indicates success (no errors)\n
 * 				1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_sigOri_initImuSensors_bl()
{
	if( g_SigFil_initImuSensors_bl() != 0 )
	{return 1;}
	else
	{return 0;}
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Initialization of matrices
 * \details	Initialize the needed matrices for the Kalman-Filter
 *
 * \param[out] returns a boolean value, indicating the occurrence of
 * 			   failures\n
 * 				0 .... indicates success (no errors)\n
 * 				1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_sigOri_initMatrices_bl()
{
	//initialize Pk Matrix
	if(g_sigMath_matrixEye_bl((double*)m_sigOri_matrixPk_rg9f64,3,3)!=0)
	{return 1;}

	//initialize an Identity matrix
	if(g_sigMath_matrixEye_bl((double*)m_sigOri_matrixI_rg9f64,3,3)!=0)
	{return 1;}

/*	//initialize the measurement noise matrix
	m_sigOri_matrixR_rg9f64[0][0]=0.5;
	m_sigOri_matrixR_rg9f64[1][1]=0.5;
	m_sigOri_matrixR_rg9f64[2][2]=0.01;

	//initialize the process noise matrix
	m_sigOri_matrixQ_rg9f64[0][0]=0.005;
	m_sigOri_matrixQ_rg9f64[1][1]=0.005;
	m_sigOri_matrixQ_rg9f64[2][2]=0.0001;*/

	//initialize the measurement noise matrix
		m_sigOri_matrixR_rg9f64[0][0]=0.06;
		m_sigOri_matrixR_rg9f64[1][1]=0.1;
		m_sigOri_matrixR_rg9f64[2][2]=0.07;

		//initialize the process noise matrix
		m_sigOri_matrixQ_rg9f64[0][0]=0.005;
		m_sigOri_matrixQ_rg9f64[1][1]=0.005;
		m_sigOri_matrixQ_rg9f64[2][2]=0.005;


	return 0;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Calculation of reference values
 * \details	Calculates reference values of Gravity, barometer
 * 			and temperature
 *
 * \param[out] none
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
void g_sigOri_initBuildReferenceValues_bl()
{
	double l_barometricValue_f64=0;
	double l_GravityValue_f64=0;
	double l_Temperature_f64=0;
	int l_countVar_i32=0;
	halImu_orientationValues l_imuValues_st;

// create Reference pressure,Gravity and Temperature as mean value over M_NR_OF_VALUES_OFFSET_I32 values
	for(l_countVar_i32=0;l_countVar_i32<M_NR_OF_VALUES_OFFSET_I32;l_countVar_i32++)
	{
		g_sigFil_readImuData_bl();
		l_imuValues_st=g_sigFil_getImuValuesUnfiltered_st();
		l_barometricValue_f64+=l_imuValues_st.pressure_f64;
		l_GravityValue_f64+=l_imuValues_st.acc.z_f64;
		l_Temperature_f64+=l_imuValues_st.temperature_f64;
	}
	m_sigOri_referencePressure_f64 =l_barometricValue_f64/M_NR_OF_VALUES_OFFSET_I32;
	m_sigOri_referenceGravity_f64=l_GravityValue_f64/M_NR_OF_VALUES_OFFSET_I32;
	m_sigOri_referenceTemperature_f64=l_Temperature_f64/M_NR_OF_VALUES_OFFSET_I32;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Trigger IMU reading
 * \details	Trigger IMU reading from the ImuFilter Interface
 *
 * \param[out] none
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
void m_sigOri_getImuData_bl()
{
	g_sigFil_readImuData_bl();
	m_sigori_imuValues_st = g_sigFil_getImuValuesUnfiltered_st();
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Calculation of angles by ACC and Mag
 * \details	This function calculates angles
 * 			(pitch, roll, yaw) from values of the Acceleration
 * 			and Magnitude sensor. Also a tilt compensation of the magnetic
 * 			sensor is done.
 *
 * \param[out]	returns the calculated angles in a struct
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
sigOri_orientationAngles m_sigOri_calcAccMagAngle_st()
{
	sigOri_orientationAngles l_angles_f64;
	double l_roll_f64=0;
	double l_pitch_f64=0;
	double l_yaw_f64=0;
	double l_divider_f64=0;

	double ll_minX_f64=M_SIGORI_MAG_MINX_F64;
	double ll_maxX_f64=M_SIGORI_MAG_MAXX_F64;
	double ll_minY_f64=M_SIGORI_MAG_MINY_F64;
	double ll_maxY_f64=M_SIGORI_MAG_MAXY_F64;
	double ll_minZ_f64=M_SIGORI_MAG_MINZ_F64;
	double ll_maxZ_f64=M_SIGORI_MAG_MAXZ_F64;

	halAccmag_3dDoubleVector l_mag_st;
	
	l_mag_st.x_f64=(m_sigori_imuValues_st.mag.x_f64-ll_minX_f64)/(ll_maxX_f64-ll_minX_f64)*2-1;
	l_mag_st.y_f64=(m_sigori_imuValues_st.mag.y_f64-ll_minY_f64)/(ll_maxY_f64-ll_minY_f64)*2-1;
	l_mag_st.z_f64=(m_sigori_imuValues_st.mag.z_f64-ll_minZ_f64)/(ll_maxZ_f64-ll_minZ_f64)*2-1;

	//calculate roll with accelerometer values
	if(m_sigori_imuValues_st.acc.z_f64!=0)
	{
		l_roll_f64=atan2(m_sigori_imuValues_st.acc.y_f64,m_sigori_imuValues_st.acc.z_f64);
		l_angles_f64.roll_f64=-l_roll_f64*M_RAD_TO_DEG_F64;
	}
	//calculate pitch with accelerometer values
	l_divider_f64=m_sigori_imuValues_st.acc.y_f64*sin(l_roll_f64)+m_sigori_imuValues_st.acc.z_f64*cos(l_roll_f64);
	if(l_divider_f64!=0)
	{
		l_pitch_f64=atan(-m_sigori_imuValues_st.acc.x_f64/l_divider_f64);
		l_angles_f64.pitch_f64=-l_pitch_f64*M_RAD_TO_DEG_F64;
	}

	//calculate yaw and make a tilt compensation for the eCompass
	l_divider_f64= m_sigori_imuValues_st.mag.x_f64*cos(l_pitch_f64)+
					m_sigori_imuValues_st.mag.y_f64*sin(l_pitch_f64)*sin(l_roll_f64)+
					m_sigori_imuValues_st.mag.z_f64*sin(l_pitch_f64)*cos(l_roll_f64);
	if(l_divider_f64!=0)
	{
		l_yaw_f64=atan2(-(-m_sigori_imuValues_st.mag.z_f64*sin(l_roll_f64)+m_sigori_imuValues_st.mag.y_f64*cos(l_roll_f64)),
					l_divider_f64);
		l_angles_f64.yaw_f64=l_yaw_f64*M_RAD_TO_DEG_F64;	
	}

/*	//calculate yaw and make a tilt compensation for the eCompass
		l_divider_f64= l_mag_st.x_f64*sin(l_pitch_f64)*sin(l_roll_f64)+
						l_mag_st.y_f64*cos(l_roll_f64)
						-l_mag_st.z_f64*sin(l_roll_f64)*cos(l_pitch_f64);
		if(l_divider_f64!=0)
		{
			l_yaw_f64=atan2(l_divider_f64,l_mag_st.z_f64*sin(l_pitch_f64)+l_mag_st.x_f64*cos(l_pitch_f64));
			l_angles_f64.yaw_f64=l_yaw_f64*M_RAD_TO_DEG_F64;

		}*/

	m_sigOri_arrayOutputAnglesAccMagCalc_st = l_angles_f64;

	return l_angles_f64;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Calculation of angles by Gyro
 * \details	This function calculates angles
 * 			(pitch, roll, yaw) from values of the Gyroscope sensor.
 *
 * \param[out]	returns the calculated angles in a struct
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
sigOri_orientationAngles m_sigOri_calcGyroAnglePerStep_st()
{
	sigOri_orientationAngles l_angles_f64;
	
	long int time_difference;
	struct timeval gettime_now;
	double l_timestep_f64=0;

	gettimeofday(&gettime_now,(void *)0);

	time_difference=gettime_now.tv_usec-gettime_old.tv_usec;
	if(time_difference<0)
	{
		time_difference=1000000-gettime_old.tv_usec+gettime_now.tv_usec;
	}

	l_timestep_f64=(double)(time_difference)*0.000001;

	l_angles_f64.roll_f64=m_sigori_imuValues_st.gyro.roll_f64*l_timestep_f64;
	l_angles_f64.pitch_f64=m_sigori_imuValues_st.gyro.pitch_f64*l_timestep_f64;
	l_angles_f64.yaw_f64=m_sigori_imuValues_st.gyro.yaw_f64*l_timestep_f64;
	gettimeofday(&gettime_old,(void *)0);

	m_sigOri_arrayOutputAnglesGyroPerStep_st = l_angles_f64;

	return l_angles_f64;
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Calculation of barometric height
 * \details	This function calculates the height with the
 * 			barometric sensor
 *
 * \param[out]	returns the height in meters
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
void m_sigOri_calcBarometricHeight_st()
{
	double l_densityOfAir_f64=287.05;	// [J/(Kg°K)]
	double l_Deg2Kelvin_f64=273.15;

	m_SIGORI_heightBarometerMetres_f64=(l_densityOfAir_f64/m_sigOri_referenceGravity_f64)*
			((m_sigori_imuValues_st.temperature_f64+l_Deg2Kelvin_f64+m_sigOri_referenceTemperature_f64+l_Deg2Kelvin_f64)/2)*
			log(m_sigOri_referencePressure_f64/m_sigori_imuValues_st.pressure_f64);
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Trigger of Kalman-Filter calculation
 * \details	This function calculates angles
 * 			(pitch, roll, yaw) with the Kalman-Filter
 *
 * \param[out]	none
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
void g_sigOri_calcKalmanOrientation_bl()
{
	//create a local matrix for storage
	double l_matrixTemp_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];
	double l_matrixTemp2_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];
	double l_matrixInnovation_rg9f64[M_SIGORI_SIZEOFARRAY_UI8][M_SIGORI_SIZEOFARRAY_UI8];

	//read new data from the IMU
	m_sigOri_getImuData_bl();

	//calculate angle from Acc/Mag and Gyro
	m_sigOri_arrayAccMagAnglesKalman_st=m_sigOri_calcAccMagAngle_st();
	m_sigOri_arrayGyroAnglesKalman_st=m_sigOri_calcGyroAnglePerStep_st();

	//set new calculated angles from the sensors in the matrices
	m_sigOri_matrixXnew_rg9f64[0][0]=m_sigOri_arrayAccMagAnglesKalman_st.roll_f64;
	m_sigOri_matrixXnew_rg9f64[1][1]=m_sigOri_arrayAccMagAnglesKalman_st.pitch_f64;
	m_sigOri_matrixXnew_rg9f64[2][2]=m_sigOri_arrayAccMagAnglesKalman_st.yaw_f64;

	m_sigOri_matrixUk_rg9f64[0][0]=m_sigOri_arrayGyroAnglesKalman_st.roll_f64;
	m_sigOri_matrixUk_rg9f64[1][1]=m_sigOri_arrayGyroAnglesKalman_st.pitch_f64;
	m_sigOri_matrixUk_rg9f64[2][2]=m_sigOri_arrayGyroAnglesKalman_st.yaw_f64;

//PREDICTION
	//state estimation (prediction)
	g_sigMath_matrixAddition_bl((double*) l_matrixTemp_rg9f64,
		(double*) m_sigOri_matrixXk_rg9f64, 3,3, 
		(double*) m_sigOri_matrixUk_rg9f64,3,3);
	g_sigMath_matrixAssignment_bl((double*) m_sigOri_matrixXk_rg9f64,3,3,
		(double*) l_matrixTemp_rg9f64,3,3);


	//covariance estimation (prediction)
	g_sigMath_matrixAddition_bl((double*) l_matrixTemp_rg9f64,
		(double*) m_sigOri_matrixPk_rg9f64, 3,3, 
		(double*) m_sigOri_matrixQ_rg9f64,3,3);
	g_sigMath_matrixAssignment_bl((double*) m_sigOri_matrixPk_rg9f64,3,3,
		(double*) l_matrixTemp_rg9f64,3,3);

//UPDATE
	//Innovation (update)
	g_sigMath_matrixSubtraktion_bl((double*) l_matrixInnovation_rg9f64,
		(double*) m_sigOri_matrixXnew_rg9f64,3,3, 
		(double*) m_sigOri_matrixXk_rg9f64,3,3);

	//Innovation covariance (update)
	g_sigMath_matrixAddition_bl((double*) m_sigOri_matrixS_rg9f64,
		(double*) m_sigOri_matrixPk_rg9f64, 3,3, 
		(double*) m_sigOri_matrixR_rg9f64,3,3);

	//Kalman Gain calculation (update)
	g_sigMath_matrixInverse_bl((double*) l_matrixTemp_rg9f64,
		(double*) m_sigOri_matrixS_rg9f64,3,3);
	g_sigMath_matrixMultiplikation_bl(
		(double*) m_sigOri_matrixK_rg9f64, 
		(double*) m_sigOri_matrixPk_rg9f64,3,3,
		(double*) l_matrixTemp_rg9f64,3,3);

	//State estimation (update)
	g_sigMath_matrixMultiplikation_bl(
		(double*) l_matrixTemp_rg9f64, 
		(double*) m_sigOri_matrixK_rg9f64,3,3,
		(double*) l_matrixInnovation_rg9f64,3,3);
	g_sigMath_matrixAddition_bl((double*) l_matrixTemp2_rg9f64,
		(double*) m_sigOri_matrixXk_rg9f64, 3,3, 
		(double*) l_matrixTemp_rg9f64,3,3);
	g_sigMath_matrixAssignment_bl((double*) m_sigOri_matrixXk_rg9f64,3,3,
		(double*) l_matrixTemp2_rg9f64,3,3);

	//Covariance estimation (update)
	g_sigMath_matrixSubtraktion_bl((double*) l_matrixTemp_rg9f64,
		(double*) m_sigOri_matrixI_rg9f64,3,3, 
		(double*) m_sigOri_matrixK_rg9f64,3,3);
	g_sigMath_matrixMultiplikation_bl(
		(double*) l_matrixTemp2_rg9f64, 
		(double*) l_matrixTemp_rg9f64,3,3,
		(double*) m_sigOri_matrixPk_rg9f64,3,3);
	g_sigMath_matrixAssignment_bl((double*) m_sigOri_matrixPk_rg9f64,3,3,
		(double*) l_matrixTemp2_rg9f64,3,3);

//set calculate within this module global
	m_sigOri_arrayOutputAnglesKalman_st.roll_f64=m_sigOri_matrixXk_rg9f64[0][0];
	m_sigOri_arrayOutputAnglesKalman_st.pitch_f64=m_sigOri_matrixXk_rg9f64[1][1];
	m_sigOri_arrayOutputAnglesKalman_st.yaw_f64=m_sigOri_matrixXk_rg9f64[2][2];
}

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Trigger of Complementary-Filter calculation
 * \details	This function calculates angles
 * 			(pitch, roll, yaw) with the Complementary-Filter
 *
 * \param[out]	none
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
void g_sigOri_calcComplementaryOrientation_bl()
{
	//read new data from the IMU
	m_sigOri_getImuData_bl();
	//calculate angle from Acc/Mag and Gyro
	m_sigOri_arrayAccMagAnglesComplementary_st=m_sigOri_calcAccMagAngle_st();
	m_sigOri_arrayGyroAnglesComplementary_st=m_sigOri_calcGyroAnglePerStep_st();

	m_sigOri_arrayOutputAnglesComplementary_st.pitch_f64=
			M_COMP_FILTER_FACTOR_F64*(m_sigOri_arrayOutputAnglesComplementary_st.pitch_f64+m_sigOri_arrayGyroAnglesComplementary_st.pitch_f64) +
			(1-M_COMP_FILTER_FACTOR_F64)*m_sigOri_arrayAccMagAnglesComplementary_st.pitch_f64;

	m_sigOri_arrayOutputAnglesComplementary_st.roll_f64=
			M_COMP_FILTER_FACTOR_F64*(m_sigOri_arrayOutputAnglesComplementary_st.roll_f64+m_sigOri_arrayGyroAnglesComplementary_st.roll_f64) +
			(1-M_COMP_FILTER_FACTOR_F64)*m_sigOri_arrayAccMagAnglesComplementary_st.roll_f64;

	m_sigOri_arrayOutputAnglesComplementary_st.yaw_f64=
		M_COMP_FILTER_FACTOR_F64*(m_sigOri_arrayOutputAnglesComplementary_st.yaw_f64+m_sigOri_arrayGyroAnglesComplementary_st.yaw_f64) +
		(1-M_COMP_FILTER_FACTOR_F64)*m_sigOri_arrayAccMagAnglesComplementary_st.yaw_f64;
}


/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Get angles of the IMU
 * \details	This function returns a struct with calculated angles
 * 			(pitch, roll, yaw) with the
 * 			Complementary-Filter
 *
 * \param[out]	returns the requested angles calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
sigOri_orientationAngles g_sigOri_getAnglesAccMagCalc_bl()
{
	return m_sigOri_arrayOutputAnglesAccMagCalc_st;
}


/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Get angles of the IMU
 * \details	This function returns a struct with calculated angles
 * 			(pitch, roll, yaw) with the
 * 			Complementary-Filter
 *
 * \param[out]	returns the requested angles calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
sigOri_orientationAngles g_sigOri_getAnglesGyroPerStep_bl()
{
	return m_sigOri_arrayOutputAnglesGyroPerStep_st;
}



