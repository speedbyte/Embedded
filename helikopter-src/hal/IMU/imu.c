/*!
 * \file imu.c
 */
/*
 * imu.c
 *
 *  Created on: May 11, 2015
 *      Author: user
 */

#include "accMag.h"
#include "barometer.h"
#include "Gyro.h"
#include "imu.h"

//storage for IMU values
static HAL_SENSOR_PAYLOAD_ST m_halImu_sensorValues_st;


/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/14
 *
 * \brief    Get state of the IMU
 * \details    This function returns a struct with all measured IMU values
 *             (Barometer, AccMag, Gyro)
 *             Attention:     Triggering of a new measurement of all chips
 *                         according to their update rate has to be done before
 *                         reading
 *                         1.) g_halImu_triggerBaroReading_bool()
 *                         2.) g_halImu_triggerGyroReading_bool()
 *                         3.) g_halImu_triggerAccReading_bool()
 *                         4.) g_halImu_triggerMagReading_bool()
 *                         or
 *                         1.) g_halImu_triggerImuReading_bool()
 *
 * \param[out]    returns the requested IMU data
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
HAL_SENSOR_PAYLOAD_ST g_halImu_getsensorValues_str(void)
{
    return m_halImu_sensorValues_st;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/13
 *
 * \brief    Initialize all sensors
 * \details    Calls the initialization functions of all mounted sensors.
 *             Over the I2C interface the acceleration, electrical compass,
 *             gyroscope and barometer sensors are initialized
 *
 * \param[out]    boolean value indicating the success of initialization\n
 *                 1:        error occured
 *                 0:        initialization succeeded
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halImu_initImuSensors_bool(void)
{
    // initialize Acceleration and electrical Compass chip
    if(g_halAccmag_initSensor_bool()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    // initialize Barometer chip
    if(g_halBaro_initBaro_i32()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    // initialize Gyroscope chip
    if(g_halGyro_initGyro_i32()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    return M_HAL_IMU_SUCCESS_BOOL;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/14
 *
 * \brief    Trigger Barometer reading
 * \details    Triggers the Barometer to measure a new pressure
 *             and temperature value and then it is saved locally
 *
 * \param[out]    boolean value indicating the success of initialization\n
 *                 1:        error occured
 *                 0:        initialization succeeded
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halImu_triggerBaroReading_bool(void)
{
    if(g_halBaro_readPressureFromI2C_i32()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    if(g_halBaro_readTemperatureFromI2C_i32()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    m_halImu_sensorValues_st.pressure_f64=g_halBaro_getPressure_f64();
    m_halImu_sensorValues_st.temperature_f64=g_halBaro_getTemperature_f64();

    return M_HAL_IMU_SUCCESS_BOOL;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/14
 *
 * \brief    Trigger Gyroscope reading
 * \details    Triggers the Gyroscope to measure new rotation rates
 *             and then it is saved locally
 *
 * \param[out]    boolean value indicating the success of initialization\n
 *                 1:        error occured
 *                 0:        initialization succeeded
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halImu_triggerGyroReading_bool(void)
{
    if(g_halGyro_I2C_readRawValue_i32()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    m_halImu_sensorValues_st.gyro=g_halGyro_getGyroscope_st();

    return M_HAL_IMU_SUCCESS_BOOL;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/14
 *
 * \brief    Trigger Acceleration reading
 * \details    Triggers the Acceleration sensor to measure new acceleration
 *             and then it is saved locally
 *
 * \param[out]    boolean value indicating the success of initialization\n
 *                 1:        error occured
 *                 0:        initialization succeeded
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halImu_triggerAccReading_bool(void)
{
    if(g_halAccmag_triggerAccUpdate_bool()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    m_halImu_sensorValues_st.acc=g_halAccmag_getAccVector_st();

    return M_HAL_IMU_SUCCESS_BOOL;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/14
 *
 * \brief    Trigger magnitude reading
 * \details    Triggers the electrical compass sensor to measure
 *             new magnetic field strengths and then it is saved locally
 *
 * \param[out]    boolean value indicating the success of initialization\n
 *                 1:        error occured
 *                 0:        initialization succeeded
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halImu_triggerMagReading_bool(void)
{
    if(g_halAccmag_triggerMagUpdate_bool()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    m_halImu_sensorValues_st.mag=g_halAccmag_getMagVector_st();

    return M_HAL_IMU_SUCCESS_BOOL;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/14
 *
 * \brief    Trigger IMU reading
 * \details    Triggers all sensors to measure    new values
 *             and then it is saved locally
 *
 * \param[out]    boolean value indicating the success of initialization\n
 *                 1:        error occured
 *                 0:        initialization succeeded
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halImu_triggerImuReading_bool(void)
{
    if(g_halBaro_readPressureFromI2C_i32()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    if(g_halBaro_readTemperatureFromI2C_i32()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    if(g_halGyro_I2C_readRawValue_i32()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    if(g_halAccmag_triggerAccUpdate_bool()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    if(g_halAccmag_triggerMagUpdate_bool()!=0)
    {return M_HAL_IMU_FAILED_BOOL;}

    m_halImu_sensorValues_st.mag=g_halAccmag_getMagVector_st();
    m_halImu_sensorValues_st.acc=g_halAccmag_getAccVector_st();
    m_halImu_sensorValues_st.gyro=g_halGyro_getGyroscope_st();
    m_halImu_sensorValues_st.pressure_f64=g_halBaro_getPressure_f64();
    m_halImu_sensorValues_st.temperature_f64=g_halBaro_getTemperature_f64();

    return M_HAL_IMU_SUCCESS_BOOL;
}
