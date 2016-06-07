/*!
 * \file Gyro.c
 */
/*
 * Gyro.c
 *
 *  Created on: 05.05.2015
 *      Author: user
 */
#include "../../../sig/Orientation/Orientation.h"

#include "../../LLD_IF/LLD_I2C.h"
#include "../Lib/Hal_Lib.h"
#include "Gyro.h"
#include <unistd.h>


#define M_HAL_GYRO_TEMP_OFFSET_UI8		27

// Variables which can be read later
static sigOri_orientationAngles m_rotation_str;
static double m_halGyro_temperature_f64;

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/05
 *
 * \brief Initialize Gyroscope chip
 * \details Initialize all necessary register of the gyroscope chip.
 *
 * \param[ in ] no parameter
 * \param[ out ] succeded
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
int g_halGyro_initGyro_i32(void)
{
	static unsigned char l_WriteBuffer_ui8[3];

	//Bypass mode -> maybe Dynamic Stream if enough bandwidth on I2C is left

	//CTRL1 (20h)= 0b11101111 ODR=800Hz Cut-Off frequency=not used
	//CTRL2 (21h)= 0b00100000 HPF=normal mode; Cut-Off frequency=56Hz
	l_WriteBuffer_ui8[0]=M_HAL_GYRO_MULTIPLE_READ_FLAG_UI8 | M_HAL_GYRO_CTRL1_UI8;
	l_WriteBuffer_ui8[1]=M_HAL_GYRO_CTRL1_DR0_DR1_UI8 | M_HAL_GYRO_CTRL1_BW1_UI8 | M_HAL_GYRO_CTRL1_NORMAL_UI8;
	l_WriteBuffer_ui8[2]=M_HAL_GYRO_CTRL2_HPF_NORMAL_MODE_UI8;
	if(g_lldI2c_WriteI2c_bl(M_I2C_SLAVE_ADDRESS_GYRO_UI8, l_WriteBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_THREE_UI8)!=0)
	{return -1;}

	usleep(100000);

	//CTRL4 (23h)= 0b00010000
	l_WriteBuffer_ui8[0]=M_HAL_GYRO_SINGLE_READ_FLAG_UI8 | M_HAL_GYRO_CTRL4_UI8;
	l_WriteBuffer_ui8[1]=M_HAL_GYRO_CTRL4_SCALE_500DPS_UI8;
	if(g_lldI2c_WriteI2c_bl(M_I2C_SLAVE_ADDRESS_GYRO_UI8, l_WriteBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_TWO_UI8)!=0)
	{return -1;}

	return 0;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/05
 *
 * \brief Get rotation from gyroscope
 * \details Interface of reading rotational speed which is measured by the gyroscope.
 *
 * \param[ in ] no parameter
 * \param[ out ] struct sigOri_orientationAngles with roll, pitch, yaw
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
sigOri_orientationAngles g_halGyro_getGyroscope_st(void)
{
	return m_rotation_str;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/05
 *
 * \brief Get Temperature from gyroscope
 * \details Interface of reading Temperature which is measured by the gyroscope.
 *
 * \param[ in ] no parameter
 * \param[ out ] Temperature
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
double g_halGyro_getTemperature_f64(void)
{
	return m_halGyro_temperature_f64;
}


/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/05
 *
 * \brief Trigger I2C transfer
 * \details Trigger rotational speed transfer from gyroscope to HAL
 *
 * \param[ in ] no parameter
 * \param[ out ] succeeded
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
int g_halGyro_readGyroscopeFromI2C_i32(void)
{
	unsigned char l_ReadBuffer_ui8[6]={0,0,0,0,0,0};
	unsigned char l_xRegister_ui8[2]={0,0};
	unsigned char l_yRegister_ui8[2]={0,0};
	unsigned char l_zRegister_ui8[2]={0,0};
	double l_xValue_ui8=0;
	double l_yValue_ui8=0;
	double l_zValue_ui8=0;
	unsigned char l_WriteBuffer_ui8[3];
	int l_countVariable_i32=0;
	//500dps in init set
	double l_factorRaw2Out_f64=(double)500.0/32767.0;


	//maybe check if new value is available; STATUS (27h) -->ZYXDA

	//set SUB Address to X register OUT_X_L and activate multiple read
	l_WriteBuffer_ui8[0]=M_HAL_GYRO_MULTIPLE_READ_FLAG_UI8 | M_HAL_GYRO_OUT_X_L_UI8;
	if(g_lldI2c_WriteI2c_bl(M_I2C_SLAVE_ADDRESS_GYRO_UI8, l_WriteBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_ONE_UI8)!=0)
	{return -1;}

	//Read from OUT_X_L (28h), OUT_X_H (29h), OUT_Y_L (2Ah), OUT_Y_H (2Bh), OUT_Z_L (2Ch), OUT_Z_H (2Dh)
	if(g_lldI2c_ReadI2c_bl(M_I2C_SLAVE_ADDRESS_GYRO_UI8, l_ReadBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_SIX_UI8)!=0)
	{return -1;}
	else
	{
		//move MSB to position 0
		for(l_countVariable_i32=0;l_countVariable_i32<2;l_countVariable_i32++)
		{
			l_xRegister_ui8[l_countVariable_i32]=l_ReadBuffer_ui8[1-l_countVariable_i32];
			l_yRegister_ui8[l_countVariable_i32]=l_ReadBuffer_ui8[3-l_countVariable_i32];
			l_zRegister_ui8[l_countVariable_i32]=l_ReadBuffer_ui8[5-l_countVariable_i32];
		}

		l_xValue_ui8=(double)g_halLib_twoComplement2Int(l_xRegister_ui8,2);
		l_yValue_ui8=(double)g_halLib_twoComplement2Int(l_yRegister_ui8,2);
		l_zValue_ui8=(double)g_halLib_twoComplement2Int(l_zRegister_ui8,2);

		l_xValue_ui8=l_xValue_ui8*l_factorRaw2Out_f64;
		l_yValue_ui8=l_yValue_ui8*l_factorRaw2Out_f64;
		l_zValue_ui8=l_zValue_ui8*l_factorRaw2Out_f64;

		m_rotation_str.roll_f64=l_xValue_ui8;
		m_rotation_str.pitch_f64=l_yValue_ui8;
		m_rotation_str.yaw_f64=l_zValue_ui8;
	}

	return 0;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/05
 *
 * \brief Trigger I2C transfer
 * \details Trigger Temperature transfer from gyroscope to HAL
 *
 * \param[ in ] no parameter
 * \param[ out ] succeeded
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
int g_halGyro_readTemperatureFromI2C_i32(void)
{
	unsigned char l_ReadBuffer_ui8[2]={0,0};
	unsigned char l_WriteBuffer_ui8[3];

	//set SUB Address to OUT_TEMP register and activate single read
	l_WriteBuffer_ui8[0]=M_HAL_GYRO_SINGLE_READ_FLAG_UI8 | M_HAL_GYRO_OUT_TEMP_UI8;
	if(g_lldI2c_WriteI2c_bl(M_I2C_SLAVE_ADDRESS_GYRO_UI8, l_WriteBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_ONE_UI8)!=0)
	{return -1;}

	//Read from OUT_TEMP (26h)
	if(g_lldI2c_ReadI2c_bl(M_I2C_SLAVE_ADDRESS_GYRO_UI8, l_ReadBuffer_ui8, M_HAL_BARO_NR_OF_BYTES_ONE_UI8)!=0)
	{return -1;}
	else
	{
		m_halGyro_temperature_f64=(double)(M_HAL_GYRO_TEMP_OFFSET_UI8)-(double)(g_halLib_twoComplement2Int(l_ReadBuffer_ui8,1));
	}

	return 0;
}
