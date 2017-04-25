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
#include "imu.h"
#include "Imufilter.h"
#include "matrixLib.h"

//define the complementary filter coefficient
#define M_COMP_FILTER_FACTOR_F64    0.888 //<--100Hz // 50Hz --> 0.941 //4Hz --> 0.995    //0 --> only Acc/Mag  1 --> only Gyro
//define the convert value from radiant to degree
#define M_RAD_TO_DEG_F64            (180/PI_F64)
//define the number of values for reference value calculation
#define M_NR_OF_VALUES_OFFSET_I32    1000

static HAL_SENSOR_PAYLOAD_ST sensor_values_st;
static double heightBarometerMetres_f64 =0;
static double referencePressure_f64=0;
static double referenceGravity_f64=0;
static double referenceTemperature_f64=0;
static double heightGpsMetres_f64 =0;
static double heightAccMetres_f64 =0;

static HAL_ANGLE_PAYLOAD_ST arrayOutputAnglesGyroPerStep_st;
static HAL_ANGLE_PAYLOAD_ST arrayOutputAnglesAccMagCalc_st;

static HAL_ANGLE_PAYLOAD_ST arrayAccMagAnglesKalman_st;
static HAL_ANGLE_PAYLOAD_ST arrayGyroAnglesKalman_st;
static HAL_ANGLE_PAYLOAD_ST arrayOutputAnglesKalman_st;


static HAL_ANGLE_PAYLOAD_ST arrayAccMagAnglesComplementary_st={0,0,0};
static HAL_ANGLE_PAYLOAD_ST arrayGyroAnglesComplementary_st={0,0,0};
static HAL_ANGLE_PAYLOAD_ST arrayOutputAnglesComplementary_st={0,0,0};


static double matrixXk_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];
static double matrixXnew_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];
static double matrixUk_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];

static double matrixI_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];
static double matrixPk_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];
static double matrixR_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];
static double matrixQ_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];

static double matrixS_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];
static double matrixK_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];

//for integrating of Gyro
static struct timeval gettime_old;

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Get angles of the IMU
 * \details    This function returns a struct with calculated angles
 *             (pitch, roll, yaw) with the
 *             Complementary-Filter
 *
 * \param[out]    returns the requested angles calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
HAL_ANGLE_PAYLOAD_ST g_getAnglesComplementary_bl()
{
    return arrayOutputAnglesComplementary_st;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Get pitch angle of the IMU
 * \details    This function returns the pitch angle calculated
 *             with the Complementary-Filter
 *
 * \param[out]    returns the pitch angle calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_getPitchComplementary_bl()
{
    return arrayOutputAnglesComplementary_st.pitch_f64;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Get roll angle of the IMU
 * \details    This function returns the roll angle calculated
 *             with the Complementary-Filter
 *
 * \param[out]    returns the roll angle calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_getRollComplementary_bl()
{
    return arrayOutputAnglesComplementary_st.roll_f64;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Get yaw angle of the IMU
 * \details    This function returns the yaw angle calculated
 *             with the Complementary-Filter
 *
 * \param[out]    returns the yaw angle calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_getYawComplementary_bl()
{
    return arrayOutputAnglesComplementary_st.yaw_f64;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Get angles of the IMU
 * \details    This function returns a struct with calculated angles
 *             (pitch, roll, yaw) with the
 *             Kalman-Filter
 *
 * \param[out]    returns the requested angles calculate with the Kalman-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
HAL_ANGLE_PAYLOAD_ST g_getAnglesKalman_bl()
{
    return arrayOutputAnglesKalman_st;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Get pitch angle of the IMU
 * \details    This function returns the pitch angle calculated
 *             with the Kalman-Filter
 *
 * \param[out]    returns the pitch angle calculate with the Kalman-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_getPitchKalman_bl()
{
    return arrayOutputAnglesKalman_st.pitch_f64;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Get roll angle of the IMU
 * \details    This function returns the roll angle calculated
 *             with the Kalman-Filter
 *
 * \param[out]    returns the roll angle calculate with the Kalman-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_getRollKalman_bl()
{
    return arrayOutputAnglesKalman_st.roll_f64;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Get yaw angle of the IMU
 * \details    This function returns the yaw angle calculated
 *             with the Kalman-Filter
 *
 * \param[out]    returns the yaw angle calculate with the Kalman-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
double g_getYawKalman_bl()
{
    return arrayOutputAnglesKalman_st.yaw_f64;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Bypass the initialization of the IMU
 * \details    Bypasses the initialization trigger to the ImuFilter
 *
 * \param[out] returns a boolean value, indicating the occurrence of
 *                failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_initImuSensors_bl()
{
    if( g_SigFil_initImuSensors_bl() != 0 )
    {return 1;}
    else
    {return 0;}
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Initialization of matrices
 * \details    Initialize the needed matrices for the Kalman-Filter
 *
 * \param[out] returns a boolean value, indicating the occurrence of
 *                failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_initMatrices_bl()
{
    //initialize Pk Matrix
    if(g_sigMath_matrixEye_bl((double*)matrixPk_rg9f64,3,3)!=0)
    {return 1;}

    //initialize an Identity matrix
    if(g_sigMath_matrixEye_bl((double*)matrixI_rg9f64,3,3)!=0)
    {return 1;}

/*    //initialize the measurement noise matrix
    matrixR_rg9f64[0][0]=0.5;
    matrixR_rg9f64[1][1]=0.5;
    matrixR_rg9f64[2][2]=0.01;

    //initialize the process noise matrix
    matrixQ_rg9f64[0][0]=0.005;
    matrixQ_rg9f64[1][1]=0.005;
    matrixQ_rg9f64[2][2]=0.0001;*/

    //initialize the measurement noise matrix
        matrixR_rg9f64[0][0]=0.06;
        matrixR_rg9f64[1][1]=0.1;
        matrixR_rg9f64[2][2]=0.07;

        //initialize the process noise matrix
        matrixQ_rg9f64[0][0]=0.005;
        matrixQ_rg9f64[1][1]=0.005;
        matrixQ_rg9f64[2][2]=0.005;


    return 0;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Calculation of reference values
 * \details    Calculates reference values of Gravity, barometer
 *             and temperature
 *
 * \param[out] none
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
void g_initBuildReferenceValues_bl()
{
    double l_barometricValue_f64=0;
    double l_GravityValue_f64=0;
    double l_Temperature_f64=0;
    int l_countVar_i32=0;
    HAL_SENSOR_PAYLOAD_ST l_sensorValues_st;

// create Reference pressure,Gravity and Temperature as mean value over M_NR_OF_VALUES_OFFSET_I32 values
    for(l_countVar_i32=0;l_countVar_i32<M_NR_OF_VALUES_OFFSET_I32;l_countVar_i32++)
    {
        g_sigFil_readImuData_bl();
        l_sensorValues_st=g_sigFil_getsensorValuesUnfiltered_st();
        l_barometricValue_f64+=l_sensorValues_st.pressure_f64;
        l_GravityValue_f64+=l_sensorValues_st.acc.z_f64;
        l_Temperature_f64+=l_sensorValues_st.temperature_f64;
    }
    referencePressure_f64 =l_barometricValue_f64/M_NR_OF_VALUES_OFFSET_I32;
    referenceGravity_f64=l_GravityValue_f64/M_NR_OF_VALUES_OFFSET_I32;
    referenceTemperature_f64=l_Temperature_f64/M_NR_OF_VALUES_OFFSET_I32;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Trigger IMU reading
 * \details    Trigger IMU reading from the ImuFilter Interface
 *
 * \param[out] none
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
void getImuData_bl()
{
    g_sigFil_readImuData_bl();
    sensor_values_st = g_sigFil_getsensorValuesUnfiltered_st();
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Calculation of angles by ACC and Mag
 * \details    This function calculates angles
 *             (pitch, roll, yaw) from values of the Acceleration
 *             and Magnitude sensor. Also a tilt compensation of the magnetic
 *             sensor is done.
 *
 * \param[out]    returns the calculated angles in a struct
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
HAL_ANGLE_PAYLOAD_ST calcAccMagAngle_st()
{
    HAL_ANGLE_PAYLOAD_ST l_angles_f64;
    double l_roll_f64=0;
    double l_pitch_f64=0;
    double l_yaw_f64=0;
    double l_divider_f64=0;

    double ll_minX_f64=MAG_MINX_F64;
    double ll_maxX_f64=MAG_MAXX_F64;
    double ll_minY_f64=MAG_MINY_F64;
    double ll_maxY_f64=MAG_MAXY_F64;
    double ll_minZ_f64=MAG_MINZ_F64;
    double ll_maxZ_f64=MAG_MAXZ_F64;

    halAccmag_3dDoubleVector l_mag_st;
    
    l_mag_st.x_f64=(sensor_values_st.mag.x_f64-ll_minX_f64)/(ll_maxX_f64-ll_minX_f64)*2-1;
    l_mag_st.y_f64=(sensor_values_st.mag.y_f64-ll_minY_f64)/(ll_maxY_f64-ll_minY_f64)*2-1;
    l_mag_st.z_f64=(sensor_values_st.mag.z_f64-ll_minZ_f64)/(ll_maxZ_f64-ll_minZ_f64)*2-1;

    //calculate roll with accelerometer values
    if(sensor_values_st.acc.z_f64!=0)
    {
        l_roll_f64=atan2(sensor_values_st.acc.y_f64,sensor_values_st.acc.z_f64);
        l_angles_f64.roll_f64=-l_roll_f64*M_RAD_TO_DEG_F64;
    }
    //calculate pitch with accelerometer values
    l_divider_f64=sensor_values_st.acc.y_f64*sin(l_roll_f64)+sensor_values_st.acc.z_f64*cos(l_roll_f64);
    if(l_divider_f64!=0)
    {
        l_pitch_f64=atan(-sensor_values_st.acc.x_f64/l_divider_f64);
        l_angles_f64.pitch_f64=-l_pitch_f64*M_RAD_TO_DEG_F64;
    }

    //calculate yaw and make a tilt compensation for the eCompass
    l_divider_f64= sensor_values_st.mag.x_f64*cos(l_pitch_f64)+
                    sensor_values_st.mag.y_f64*sin(l_pitch_f64)*sin(l_roll_f64)+
                    sensor_values_st.mag.z_f64*sin(l_pitch_f64)*cos(l_roll_f64);
    if(l_divider_f64!=0)
    {
        l_yaw_f64=atan2(-(-sensor_values_st.mag.z_f64*sin(l_roll_f64)+sensor_values_st.mag.y_f64*cos(l_roll_f64)),
                    l_divider_f64);
        l_angles_f64.yaw_f64=l_yaw_f64*M_RAD_TO_DEG_F64;    
    }

/*    //calculate yaw and make a tilt compensation for the eCompass
        l_divider_f64= l_mag_st.x_f64*sin(l_pitch_f64)*sin(l_roll_f64)+
                        l_mag_st.y_f64*cos(l_roll_f64)
                        -l_mag_st.z_f64*sin(l_roll_f64)*cos(l_pitch_f64);
        if(l_divider_f64!=0)
        {
            l_yaw_f64=atan2(l_divider_f64,l_mag_st.z_f64*sin(l_pitch_f64)+l_mag_st.x_f64*cos(l_pitch_f64));
            l_angles_f64.yaw_f64=l_yaw_f64*M_RAD_TO_DEG_F64;

        }*/

    arrayOutputAnglesAccMagCalc_st = l_angles_f64;

    return l_angles_f64;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Calculation of angles by Gyro
 * \details    This function calculates angles
 *             (pitch, roll, yaw) from values of the Gyroscope sensor.
 *
 * \param[out]    returns the calculated angles in a struct
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
HAL_ANGLE_PAYLOAD_ST calcGyroAnglePerStep_st()
{
    HAL_ANGLE_PAYLOAD_ST l_angles_f64;
    
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

    l_angles_f64.roll_f64=sensor_values_st.gyro.roll_f64*l_timestep_f64;
    l_angles_f64.pitch_f64=sensor_values_st.gyro.pitch_f64*l_timestep_f64;
    l_angles_f64.yaw_f64=sensor_values_st.gyro.yaw_f64*l_timestep_f64;
    gettimeofday(&gettime_old,(void *)0);

    arrayOutputAnglesGyroPerStep_st = l_angles_f64;

    return l_angles_f64;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Calculation of barometric height
 * \details    This function calculates the height with the
 *             barometric sensor
 *
 * \param[out]    returns the height in meters
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
void calcBarometricHeight_st()
{
    double l_densityOfAir_f64=287.05;    // [J/(Kg°K)]
    double l_Deg2Kelvin_f64=273.15;

    heightBarometerMetres_f64=(l_densityOfAir_f64/referenceGravity_f64)*
            ((sensor_values_st.temperature_f64+l_Deg2Kelvin_f64+referenceTemperature_f64+l_Deg2Kelvin_f64)/2)*
            log(referencePressure_f64/sensor_values_st.pressure_f64);
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Trigger of Kalman-Filter calculation
 * \details    This function calculates angles
 *             (pitch, roll, yaw) with the Kalman-Filter
 *
 * \param[out]    none
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
void g_calcKalmanOrientation_bl()
{
    //create a local matrix for storage
    double l_matrixTemp_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];
    double l_matrixTemp2_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];
    double l_matrixInnovation_rg9f64[SIZEOFARRAY_UI8][SIZEOFARRAY_UI8];

    //read new data from the IMU
    getImuData_bl();

    //calculate angle from Acc/Mag and Gyro
    arrayAccMagAnglesKalman_st=calcAccMagAngle_st();
    arrayGyroAnglesKalman_st=calcGyroAnglePerStep_st();

    //set new calculated angles from the sensors in the matrices
    matrixXnew_rg9f64[0][0]=arrayAccMagAnglesKalman_st.roll_f64;
    matrixXnew_rg9f64[1][1]=arrayAccMagAnglesKalman_st.pitch_f64;
    matrixXnew_rg9f64[2][2]=arrayAccMagAnglesKalman_st.yaw_f64;

    matrixUk_rg9f64[0][0]=arrayGyroAnglesKalman_st.roll_f64;
    matrixUk_rg9f64[1][1]=arrayGyroAnglesKalman_st.pitch_f64;
    matrixUk_rg9f64[2][2]=arrayGyroAnglesKalman_st.yaw_f64;

//PREDICTION
    //state estimation (prediction)
    g_sigMath_matrixAddition_bl((double*) l_matrixTemp_rg9f64,
        (double*) matrixXk_rg9f64, 3,3, 
        (double*) matrixUk_rg9f64,3,3);
    g_sigMath_matrixAssignment_bl((double*) matrixXk_rg9f64,3,3,
        (double*) l_matrixTemp_rg9f64,3,3);


    //covariance estimation (prediction)
    g_sigMath_matrixAddition_bl((double*) l_matrixTemp_rg9f64,
        (double*) matrixPk_rg9f64, 3,3, 
        (double*) matrixQ_rg9f64,3,3);
    g_sigMath_matrixAssignment_bl((double*) matrixPk_rg9f64,3,3,
        (double*) l_matrixTemp_rg9f64,3,3);

//UPDATE
    //Innovation (update)
    g_sigMath_matrixSubtraktion_bl((double*) l_matrixInnovation_rg9f64,
        (double*) matrixXnew_rg9f64,3,3, 
        (double*) matrixXk_rg9f64,3,3);

    //Innovation covariance (update)
    g_sigMath_matrixAddition_bl((double*) matrixS_rg9f64,
        (double*) matrixPk_rg9f64, 3,3, 
        (double*) matrixR_rg9f64,3,3);

    //Kalman Gain calculation (update)
    g_sigMath_matrixInverse_bl((double*) l_matrixTemp_rg9f64,
        (double*) matrixS_rg9f64,3,3);
    g_sigMath_matrixMultiplikation_bl(
        (double*) matrixK_rg9f64, 
        (double*) matrixPk_rg9f64,3,3,
        (double*) l_matrixTemp_rg9f64,3,3);

    //State estimation (update)
    g_sigMath_matrixMultiplikation_bl(
        (double*) l_matrixTemp_rg9f64, 
        (double*) matrixK_rg9f64,3,3,
        (double*) l_matrixInnovation_rg9f64,3,3);
    g_sigMath_matrixAddition_bl((double*) l_matrixTemp2_rg9f64,
        (double*) matrixXk_rg9f64, 3,3, 
        (double*) l_matrixTemp_rg9f64,3,3);
    g_sigMath_matrixAssignment_bl((double*) matrixXk_rg9f64,3,3,
        (double*) l_matrixTemp2_rg9f64,3,3);

    //Covariance estimation (update)
    g_sigMath_matrixSubtraktion_bl((double*) l_matrixTemp_rg9f64,
        (double*) matrixI_rg9f64,3,3, 
        (double*) matrixK_rg9f64,3,3);
    g_sigMath_matrixMultiplikation_bl(
        (double*) l_matrixTemp2_rg9f64, 
        (double*) l_matrixTemp_rg9f64,3,3,
        (double*) matrixPk_rg9f64,3,3);
    g_sigMath_matrixAssignment_bl((double*) matrixPk_rg9f64,3,3,
        (double*) l_matrixTemp2_rg9f64,3,3);

//set calculate within this module global
    arrayOutputAnglesKalman_st.roll_f64=matrixXk_rg9f64[0][0];
    arrayOutputAnglesKalman_st.pitch_f64=matrixXk_rg9f64[1][1];
    arrayOutputAnglesKalman_st.yaw_f64=matrixXk_rg9f64[2][2];
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Trigger of Complementary-Filter calculation
 * \details    This function calculates angles
 *             (pitch, roll, yaw) with the Complementary-Filter
 *
 * \param[out]    none
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
void g_calcComplementaryOrientation_bl()
{
    //read new data from the IMU
    getImuData_bl();
    //calculate angle from Acc/Mag and Gyro
    arrayAccMagAnglesComplementary_st=calcAccMagAngle_st();
    arrayGyroAnglesComplementary_st=calcGyroAnglePerStep_st();

    arrayOutputAnglesComplementary_st.pitch_f64=
            M_COMP_FILTER_FACTOR_F64*(arrayOutputAnglesComplementary_st.pitch_f64+arrayGyroAnglesComplementary_st.pitch_f64) +
            (1-M_COMP_FILTER_FACTOR_F64)*arrayAccMagAnglesComplementary_st.pitch_f64;

    arrayOutputAnglesComplementary_st.roll_f64=
            M_COMP_FILTER_FACTOR_F64*(arrayOutputAnglesComplementary_st.roll_f64+arrayGyroAnglesComplementary_st.roll_f64) +
            (1-M_COMP_FILTER_FACTOR_F64)*arrayAccMagAnglesComplementary_st.roll_f64;

    arrayOutputAnglesComplementary_st.yaw_f64=
        M_COMP_FILTER_FACTOR_F64*(arrayOutputAnglesComplementary_st.yaw_f64+arrayGyroAnglesComplementary_st.yaw_f64) +
        (1-M_COMP_FILTER_FACTOR_F64)*arrayAccMagAnglesComplementary_st.yaw_f64;
}


/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Get angles of the IMU
 * \details    This function returns a struct with calculated angles
 *             (pitch, roll, yaw) with the
 *             Complementary-Filter
 *
 * \param[out]    returns the requested angles calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
HAL_ANGLE_PAYLOAD_ST g_getAnglesAccMagCalc_bl()
{
    return arrayOutputAnglesAccMagCalc_st;
}


/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Get angles of the IMU
 * \details    This function returns a struct with calculated angles
 *             (pitch, roll, yaw) with the
 *             Complementary-Filter
 *
 * \param[out]    returns the requested angles calculate with the Complementary-Filter
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
HAL_ANGLE_PAYLOAD_ST g_getAnglesGyroPerStep_bl()
{
    return arrayOutputAnglesGyroPerStep_st;
}



