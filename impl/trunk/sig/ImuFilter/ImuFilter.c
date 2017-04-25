/*!
 * \file Imufilter.c
 */
/*
 * ImuFilter.c
 *
 *  Created on: May 28, 2015
 *      Author: user
 */

#include "../../hal/IMU/imu.h"

//define the number off values which are regarded for the mean value calculation
#define M_NR_OF_VALUES_FOR_OFFSET_UI8        1000

static HAL_SENSOR_PAYLOAD_ST m_sigFil_sensorValues_st;
static HAL_ANGLE_PAYLOAD_ST m_offsetGyro_st;

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Get unfiltered state of the IMU
 * \details    This function returns a struct with all measured IMU values
 *             (Barometer, AccMag, Gyro).
 *             The Gyro value is offset corrected.
 *             The magnitude value is changed in its unit from Tesla to µTesla.
 *             The Z-axis from Acceleration sensor and magnitude sensor is 180° rotated.
 *             Attention:     Initialization of the IMU and
 *                         Triggering of a new measurement of all chips
 *                         according to their update rate has to be done before
 *                         reading
 *                         1.) g_SigFil_initImuSensors_bl()
 *                         2.) g_sigFil_readImuData_bl()
 *
 * \param[out]    returns the requested IMU data
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
HAL_SENSOR_PAYLOAD_ST g_sigFil_getsensorValuesUnfiltered_st()
{
    return m_sigFil_sensorValues_st;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Offset correction of the Gyroscope
 * \details    Function gets called by g_SigFil_initImuSensors_bl()
 *             which then calculates the Offset of the Gyros
 *
 * \param[out]    returns the Offset of the Gyroscopes
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
HAL_ANGLE_PAYLOAD_ST m_sigFil_offsetCorrectionGyro_st()
{
    int i=0;
    HAL_ANGLE_PAYLOAD_ST l_measuredGyroValue_st={0,0,0};
    HAL_SENSOR_PAYLOAD_ST l_sigFil_sensorValues_st;

    for(i=0;i<M_NR_OF_VALUES_FOR_OFFSET_UI8;i++)
    {
        g_halImu_triggerImuReading_bl();
        l_sigFil_sensorValues_st = g_halImu_getsensorValues_str();

        l_measuredGyroValue_st.roll_f64+=l_sigFil_sensorValues_st.gyro.roll_f64;
        l_measuredGyroValue_st.pitch_f64+=l_sigFil_sensorValues_st.gyro.pitch_f64;
        l_measuredGyroValue_st.yaw_f64+=l_sigFil_sensorValues_st.gyro.yaw_f64;
    }

    l_measuredGyroValue_st.roll_f64=l_measuredGyroValue_st.roll_f64/M_NR_OF_VALUES_FOR_OFFSET_UI8;
    l_measuredGyroValue_st.pitch_f64=l_measuredGyroValue_st.pitch_f64/M_NR_OF_VALUES_FOR_OFFSET_UI8;
    l_measuredGyroValue_st.yaw_f64=l_measuredGyroValue_st.yaw_f64/M_NR_OF_VALUES_FOR_OFFSET_UI8;

    return l_measuredGyroValue_st;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Bypass the initialization of the IMU
 * \details    Bypasses the initialization trigger and calls the
 *             Offset calculation function
 *
 * \param[out]    none
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_SigFil_initImuSensors_bl()
{
    unsigned int l_initState_bl;

    l_initState_bl = g_halImu_initImuSensors_bl();
    m_offsetGyro_st=m_sigFil_offsetCorrectionGyro_st();

    return l_initState_bl;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/31
 *
 * \brief    Trigger IMU reading
 * \details    Trigger IMU reading, correct the read value with the
 *             offset of the Gyroscope and convert magnitude
 *             from Tesla to µTesla.
 *             The Z-axis from Acceleration sensor and magnitude sensor gets 180° rotated.
 *
 * \param[out]    none
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
void g_sigFil_readImuData_bl()
{
    g_halImu_triggerImuReading_bl();
    m_sigFil_sensorValues_st = g_halImu_getsensorValues_str();

    m_sigFil_sensorValues_st.acc.z_f64=-m_sigFil_sensorValues_st.acc.z_f64;
    m_sigFil_sensorValues_st.mag.x_f64=m_sigFil_sensorValues_st.mag.x_f64*1000000;
    m_sigFil_sensorValues_st.mag.y_f64=m_sigFil_sensorValues_st.mag.y_f64*1000000;
    m_sigFil_sensorValues_st.mag.z_f64=-m_sigFil_sensorValues_st.mag.z_f64*1000000;
    m_sigFil_sensorValues_st.gyro.roll_f64=m_sigFil_sensorValues_st.gyro.roll_f64-m_offsetGyro_st.roll_f64;
    m_sigFil_sensorValues_st.gyro.pitch_f64=m_sigFil_sensorValues_st.gyro.pitch_f64-m_offsetGyro_st.pitch_f64;
    m_sigFil_sensorValues_st.gyro.yaw_f64=m_sigFil_sensorValues_st.gyro.yaw_f64-m_offsetGyro_st.yaw_f64;

}



/*
halAccmag_3dDoubleVector m_sigFil_TPFilterAcc_st(halAccmag_3dDoubleVector f_inputArray_st, unsigned int f_nrOfValues)
{

}

halAccmag_3dDoubleVector m_sigFil_HPFilterAcc_st(halAccmag_3dDoubleVector f_inputArray_st, unsigned int f_nrOfValues)
{

}

halAccmag_3dDoubleVector m_sigFil_TPFilterMag_st(halAccmag_3dDoubleVector f_inputArray_st, unsigned int f_nrOfValues)
{

}

halAccmag_3dDoubleVector m_sigFil_HPFilterMag_st(halAccmag_3dDoubleVector f_inputArray_st, unsigned int f_nrOfValues)
{

}

halAccmag_3dDoubleVector m_sigFil_TPFilterGyro_st(halAccmag_3dDoubleVector f_inputArray_st, unsigned int f_nrOfValues)
{

}

halAccmag_3dDoubleVector m_sigFil_HPFilterGyro_st(halAccmag_3dDoubleVector f_inputArray_st, unsigned int f_nrOfValues)
{

}

double m_sigFil_TPFilterBaro_st(double f_inputArray_st, unsigned int f_nrOfValues)
{

}

double m_sigFil_HPFilterBaro_st(double f_inputArray_st, unsigned int f_nrOfValues)
{

}

double m_sigFil_TPFilterTemp_st(double f_inputArray_st, unsigned int f_nrOfValues)
{

}

double m_sigFil_HPFilterTemp_st(double f_inputArray_st, unsigned int f_nrOfValues)
{

}
*/
