/*!
 * \file main.c
 */
/*
 * main.cpp
 *
 *  Created on: 29.03.2015
 *      Author: user
 */

#include <stdio.h>
#include "./hal/batteryCheck/batteryCheck.h"


int main (void)
{

	double l_batterLevel_f64=0;

	while(1)
	{
		g_halBatCheck_readBatStatusFromI2C_bl();
		l_batterLevel_f64=g_halBatCheck_getBatteryStatus_f64();
		printf("Measured Voltage: %5.3f\n",l_batterLevel_f64);
		sleep(1);
	}


	return 0;
}



