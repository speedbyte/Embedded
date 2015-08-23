/*!
 * \file batteryCheck.c
 */
/*
 * batteryCheck.c
 *
 *  Created on: May 14, 2015
 *      Author: user
 */

#include "../ADC/HAL_ADC.h"
#include "batteryCheck.h"

//define of ADC input pin
#define M_HAL_BATCHECK_ADC_INPUT_PORT_UI8	1

static double m_batteryLevel_f64;


/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/14
 *
 * \brief Get Voltage from battery watchdog
 * \details Interface of reading voltage from battery watchdog
 * 			which is connected to the ADC input pin ADC0
 *
 * \param[ in ] no parameter
 * \param[ out ] Voltage of battery as float value
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
double g_halBatCheck_getBatteryStatus_f64(void)
{
	return m_batteryLevel_f64;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/14
 *
 * \brief Trigger update of measured battery level
 * \details Interface of reading voltage from battery watchdog
 * 			which is connected to the ADC input pin ADC0
 *
 * \param[ in ] no parameter
 * \param[out]	returns a boolean value, indicating the occurence of
 * 				failures\n
 * 				0 .... indicates success (no errors)\n
 * 				1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
unsigned int  g_halBatCheck_readBatStatusFromI2C_bl(void)
{
	double l_batteryLevel_f64;

	l_batteryLevel_f64=g_halADC_get_ui16(M_HAL_BATCHECK_ADC_INPUT_PORT_UI8);

	if(l_batteryLevel_f64<=0)
	{return M_HAL_BATCHECK_FAILED_BL;}

	m_batteryLevel_f64=l_batteryLevel_f64;

	return M_HAL_BATCHECK_SUCCESS_BL;
}
