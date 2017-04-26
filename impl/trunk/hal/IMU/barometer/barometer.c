/*!
 * \file barometer.c
 */
/*
 * barometer.c
 *
 *  Created on: 05.05.2015
 *      Author: user
 */

#include <unistd.h>
#include "../../LLD_IF/LLD_I2C.h"
#include "barometer.h"
#include "Hal_Lib.h"

// Variables which can be read later
static double m_temperature_f64;
static double m_pressure_f64;

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/05
 *
 * \brief Initialize Barometer chip
 * \details Initialize all necessary register of the barometer chip
 *
 * \param[ in ] no parameter
 * \param[ out ] succeded
 *
 * \internal
 * CHANGELOG:
 * 2015/05/19 juscgs00:
 * - removed unused local variable 'l_ReadBuffer_ui8' (compiler warning)
 * \endinternal
 ********************************************************************** */
int g_halBaro_initBaro_i32(void)
{
    static unsigned char l_WriteBuffer_ui8[3];

    //RES_CONF(0x10)
    l_WriteBuffer_ui8[0]=M_HAL_BARO_SINGLE_FLAG_UI8 | M_HAL_BARO_RES_CONF_UI8;
    l_WriteBuffer_ui8[1]= M_HAL_BARO_TEMP_RES_CONF_128_UI8 | M_HAL_BARO_PRES_RES_CONF_512_UI8;
    if(g_lldI2c_WriteI2c_bool(M_I2C_SLAVE_ADDRESS_BARO_UI8, l_WriteBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_TWO_UI8)!=0)
    {return -1;}

    usleep(100000);

    //CTRL_REG1(0x20) = 0b11000100        setting Speed of Pressure to 25Hz and Temperature to 1Hz
                                        //REMARK: setting both Sensors to the same value did not work!!!
    //CTRL_REG2(0x21) = 0b10000000
    l_WriteBuffer_ui8[0]=M_HAL_BARO_MULTIPLE_FLAG_UI8 | M_HAL_BARO_CTRL_REG1_UI8;
    l_WriteBuffer_ui8[1]=M_HAL_BARO_CTRL_REG1_PD_UI8|M_HAL_BARO_CTRL_REG1_DATARATE_P25HZ_T1HZ_UI8;
    l_WriteBuffer_ui8[2]=M_HAL_BARO_CTRL_REG2_BOOT_UI8;
    if(g_lldI2c_WriteI2c_bool(M_I2C_SLAVE_ADDRESS_BARO_UI8, l_WriteBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_THREE_UI8)!=0)
    {return -1;}

    return 0;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/05
 *
 * \brief Get Pressure from barometer
 * \details Interface of reading Pressure which is measured by the barometer.
 *
 * \param[ in ] no parameter
 * \param[ out ] Pressure of the barometer
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
double g_halBaro_getPressure_f64(void)
{
    return m_pressure_f64;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/05
 *
 * \brief Get Temperature from GPS module
 * \details Interface of reading Temperature which is measured by the barometer.
 *
 * \param[ in ] no parameter
 * \param[ out ] Temperature of GPS receiver
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
double g_halBaro_getTemperature_f64(void)
{
    return m_temperature_f64;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/05
 *
 * \brief Trigger I2C transfer
 * \details Trigger Pressure transfer from barometer to HAL
 *
 * \param[ in ] no parameter
 * \param[ out ] succeeded
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
int g_halBaro_readPressureFromI2C_i32(void)
{
    unsigned char l_ReadBuffer_ui8[3]={0,0,0};
    unsigned char l_rotatedReadBuffer_ui8[3]={0,0,0};
    unsigned char l_WriteBuffer_ui8[3];
    int l_countVariable_i32=0;

    //maybe check STATUS_REG if new value is available

    //set SUB Address to Pressure register PRESS_OUT_XL and activate multiple read
    l_WriteBuffer_ui8[0]=M_HAL_BARO_MULTIPLE_FLAG_UI8 | M_HAL_BARO_PRESS_OUT_XL_UI8;
    if(g_lldI2c_WriteI2c_bool(M_I2C_SLAVE_ADDRESS_BARO_UI8, l_WriteBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_ONE_UI8)!=0)
    {return -1;}


    //Read from PRESS_OUT_XL(0x28),PRESS_OUT_L(0x29),PRESS_OUT_H(0x2A)
    if(g_lldI2c_ReadI2c_bool(M_I2C_SLAVE_ADDRESS_BARO_UI8, l_ReadBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_THREE_UI8)!=0)
    {return -1;}
    else
    {
        //move MSB to position 0
        for(l_countVariable_i32=0;l_countVariable_i32<3;l_countVariable_i32++)
        {
            l_rotatedReadBuffer_ui8[l_countVariable_i32]=l_ReadBuffer_ui8[2-l_countVariable_i32];
        }

        m_pressure_f64=(double)g_halLib_twoComplement2Int(l_rotatedReadBuffer_ui8,3);
        m_pressure_f64=m_pressure_f64/4096;
    }

    return 0;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/05
 *
 * \brief Trigger I2C transfer
 * \details Trigger Temperature transfer from barometer to HAL
 *
 * \param[ in ] no parameter
 * \param[ out ] succeeded
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
int g_halBaro_readTemperatureFromI2C_i32(void)
{
    unsigned char l_ReadBuffer_ui8[2]={0,0};
    unsigned char l_rotatedReadBuffer_ui8[2]={0,0};
    unsigned char l_WriteBuffer_ui8[3];
    int l_countVariable_i32=0;

    //maybe check STATUS_REG if new value is available

    //set SUB Address to Temperature register PRESS_OUT_XL and activate multiple read
    l_WriteBuffer_ui8[0]=M_HAL_BARO_MULTIPLE_FLAG_UI8 | M_HAL_BARO_TEMP_OUT_L_UI8;
    if(g_lldI2c_WriteI2c_bool(M_I2C_SLAVE_ADDRESS_BARO_UI8, l_WriteBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_ONE_UI8)!=0)
    {return -1;}


    //Read from TEMP_OUT_L (2Bh), TEMP_OUT_H (2Ch)
    if(g_lldI2c_ReadI2c_bool(M_I2C_SLAVE_ADDRESS_BARO_UI8, l_ReadBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_TWO_UI8)!=0)
    {return -1;}
    else
    {
        //move MSB to position 0
        for(l_countVariable_i32=0;l_countVariable_i32<2;l_countVariable_i32++)
        {
            l_rotatedReadBuffer_ui8[l_countVariable_i32]=l_ReadBuffer_ui8[1-l_countVariable_i32];
        }

        m_temperature_f64=(double)g_halLib_twoComplement2Int(l_rotatedReadBuffer_ui8,2);
        m_temperature_f64=42.5+m_temperature_f64/480;
    }

    return 0;
}
