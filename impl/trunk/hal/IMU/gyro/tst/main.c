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
#include "./hal/gps/GPS.h"
#include "./hal/IMU/barometer/barometer.h"
#include "./hal/IMU/gyro/Gyro.h"



int main (void)
{

	double pressure=0;
	double temp=0;
	strGyro GyroValues;
	double Gyrotemp=0;


//	char rec_char='z';
//	char *ptr_rec_char=&rec_char;
//	FILE * fp=-1;
//
//	//open file to write received data from GPS
//	fp = open ("GPS_logging.txt",100 | 01,400);
//	//fp = open ("GPS_logging.txt","a");
//	sleep(1);
//
//	while(1)
//	{
//		rec_char=LLD_UART_READBYTE();
//		//save read values if filestream is opened
//		if (fp != -1)
//		{
//			write(fp,ptr_rec_char,1);
//		}
//	}
//
//	fclose(fp);

	g_halBaro_initBaro_i32();
	g_halGyro_initGyro_i32();

	while(1)
	{
		g_halBaro_readPressureFromI2C_i32();
		//usleep(100000);
		g_halBaro_readTemperatureFromI2C_i32();
		//usleep(100000);
		pressure=g_halBaro_getPressure_f64();
		temp=g_halBaro_getTemperature_f64();
		printf("Pressure: %5.3f    ;    Temperature:  %5.3f\n",pressure,temp);
		//usleep(100000);


		g_halGyro_readGyroscopeFromI2C_i32();
		//usleep(100000);
		g_halGyro_readTemperatureFromI2C_i32();
		//usleep(100000);
		GyroValues=g_halGyro_getGyroscope_st();
		Gyrotemp=g_halGyro_getTemperature_f64();
		printf("yaw: %5.3f    ;    pitch:  %5.3f    ;    roll:  %5.3f\n",GyroValues.l_yaw_f64,GyroValues.l_pitch_f64,GyroValues.l_roll_f64);
		//usleep(100000);


	}


	return 0;
}



