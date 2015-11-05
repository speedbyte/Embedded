/*!
 * \file ADCTest.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "../matlab/udpSigLib.h"
#include "../matlab/udpImuLib.h"
#include "../sig/matrixLib/matrixLib.h"
#include "../hal/ADC/HAL_ADC.h"
#include "../hal/BATTERY/batteryCheck.h"
#include "../sig/Orientation/Orientation.h"
#include "../hal/GPS/GPS.h"
#include "../hal/IMU/imu.h"
#include "../hal/IMU/barometer/barometer.h"
#include "../hal/LASER/LIDAR.h"
#include "../hal/LLD_IF/LLD_UART.h"

extern float g_halADC_get_ui16(unsigned char );

int main() {

	int runCommand = 0;
	char testValue[20];
	scanf("%s", testValue);
	printf("Received string is %s\n", testValue);
	if ( strcmp(testValue,"testadc")  == 0 )
		runCommand = 1;
	else if ( strcmp(testValue,"testadc")  == 0 )
		runCommand = 2;
	else if ( strcmp(testValue,"testbattery")  == 0 )
		runCommand = 3;
	else if ( strcmp(testValue,"testgps")  == 0 )
		runCommand = 4;
	else if ( strcmp(testValue,"testimu")  == 0 )
		runCommand = 5;
	else if ( strcmp(testValue,"testlaser")  == 0 )
		runCommand = 6;
	else if ( strcmp(testValue,"testmatlabimu")  == 0 )
		runCommand = 7;
	else if ( strcmp(testValue,"testmatlabkalman")  == 0 )
		runCommand = 8;
	else if ( strcmp(testValue,"testaccmag")  == 0 )
		runCommand = 9;
	else if ( strcmp(testValue,"testgyro")  == 0 )
		runCommand = 10;
	else if ( strcmp(testValue,"testbaro")  == 0 )
		runCommand = 11;
	else if ( strcmp(testValue,"testmatrixlib")  == 0 )
		runCommand = 12;

	switch (runCommand)
	{
		case 1:
		{
			float erg;
			printf("Starting ADC Test\n");
			erg = g_halADC_get_ui16(1);
			if(erg<0)
			{
				printf("Fehler");
				return 1;
			}
			else
			{
				printf("Ergebniss: %f\n",erg);
			}
			break;
		}
		case 2:
		{
			double l_batterLevel_f64=0;
			printf("Starting Battery Test\n");
			while(1)
			{
				g_halBatCheck_readBatStatusFromI2C_bl();
				l_batterLevel_f64=g_halBatCheck_getBatteryStatus_f64();
				printf("Measured Voltage: %5.3f\n",l_batterLevel_f64);
				sleep(1);
			}
			break;
		}
		case 3:
		{
			int i=0;
			struct strPosition main_longitude;
			struct strPosition main_latitude;
			printf("Starting GPS Test\n");
			while(1)
			{
				g_halGps_getData_i32();
			}
			break;
		}
		case 4:
		{
			halImu_orientationValues l_imuMeasurements_st;
			printf("Starting IMU Test\n");
			g_halImu_initImuSensors_bl();
			while(1)
			{
				g_halImu_triggerImuReading_bl();
				g_halImu_triggerBaroReading_bl();
				g_halImu_triggerGyroReading_bl();
				g_halImu_triggerAccReading_bl();

				l_imuMeasurements_st=g_halImu_getImuValues_str();

				printf("Pressure: %5.3f    ;    Temperature:  %5.3f\n",l_imuMeasurements_st.pressure_f64,l_imuMeasurements_st.temperature_f64);
				printf("yaw: %5.3f ; pitch:  %5.3f ; roll:  %5.3f\n",l_imuMeasurements_st.gyro.l_yaw_f64,l_imuMeasurements_st.gyro.l_pitch_f64,l_imuMeasurements_st.gyro.l_roll_f64);
				printf("X: %5.3f ; Y:  %5.3f ; Z:  %5.3f\n",l_imuMeasurements_st.acc.x_f64,l_imuMeasurements_st.acc.y_f64,l_imuMeasurements_st.acc.z_f64);
				printf("X: %5.10f ; Y:  %5.10f ; Z:  %5.10f\n\n\n\n",l_imuMeasurements_st.mag.x_f64,l_imuMeasurements_st.mag.y_f64,l_imuMeasurements_st.mag.z_f64);
			}
			break;
		}
		case 5:
		{
			double dist=0;
			printf("Starting LASER Test\n");
			while(1)
			{
				g_LIDAR_readDistanceFromI2C_i32();
				//usleep(100000);

				dist=g_LIDAR_getDistance_f64();

				printf("Distance: %4.2f m\n",dist);
				usleep(500*1000);
			}
			break;
		}
		case 6:
		{
			char rec_char='z';
			char *ptr_rec_char=&rec_char;
			printf("Starting UART Test\n");
			FILE *fp=(FILE *)-1;
			//open file to write received data from GPS
			fp = (FILE *)open("GPS_logging.txt",100 | 01,400);
			sleep(1);
			while(1)
			{
				rec_char=g_lldUart_readByte_ch();
				//save read values if filestream is opened
				if (fp != (FILE *)-1)
				{
					write((int)fp,ptr_rec_char,1);
				}
			}
			fclose(fp);
			break;
		}
		case 7:
		{
			printf("Starting IMU Matlab Test\n");
			unsigned char	l_remoteHostAddr_rg4ui8[4] 	= {192,168,22,160};
			unsigned short	l_remoteHostPort_ui16		= 5000;
			int				l_udpSocket_i32;
			unsigned int	l_sendState_bl;

			// open udp connection
			l_udpSocket_i32 = g_halMatlab_initConnection_i32( l_remoteHostAddr_rg4ui8, l_remoteHostPort_ui16 );

			halImu_orientationValues l_imuMeasurements_st;
			g_halImu_initImuSensors_bl();

			while(1)
			{
				g_halImu_triggerImuReading_bl();
				g_halImu_triggerBaroReading_bl();
				g_halImu_triggerGyroReading_bl();
				g_halImu_triggerAccReading_bl();

				l_imuMeasurements_st=g_halImu_getImuValues_str();

				l_sendState_bl = g_halMatlab_sendImuState_bl(l_udpSocket_i32, l_imuMeasurements_st);
				if ( l_sendState_bl != M_HAL_MATLAB_SUCCESS_UI8 )
				{
					printf("UDP-Packet error\n");
				}

				usleep( 20000 ); //20ms = 50Hz
			}
			// close udp connection
			g_halMatlab_closeSocket_bl(l_udpSocket_i32);
			break;
		}
		case 8:
		{
			printf("Starting Kalman Orientation Matlab Test\n");
			unsigned char	l_remoteHostAddr_rg4ui8[4] 	= {192,168,22,160};
			unsigned short	l_remoteHostPort_ui16		= 5000;
			int				l_udpSocket_i32;
			unsigned int	l_sendState_bl;

			sigOri_orientationAngles	l_kalmanAngles_st;
			sigOri_orientationAngles	l_compAngles_st;
			halImu_orientationValues	l_imuStates_st;

			// open udp connection
			l_udpSocket_i32 = g_halMatlab_initConnection_i32( l_remoteHostAddr_rg4ui8, l_remoteHostPort_ui16 );

			g_sigOri_initMatrices_bl();
			g_sigOri_initImuSensors_bl();

			while(1)
			{
				g_sigOri_calcKalmanOrientation_bl();
				g_sigOri_calcComplementaryOrientation_bl();

				l_kalmanAngles_st 	= g_sigOri_getAnglesKalman_bl();
				l_compAngles_st		= g_sigOri_getAnglesComplementary_bl();
				l_imuStates_st 		= g_halImu_getImuValues_str();

				printf("Temp%f\nMag%f",l_imuStates_st.temperature_f64, l_imuStates_st.mag.x_f64);
				l_sendState_bl = g_halMatlab_sendSigAllStates_bl(	l_udpSocket_i32,
																	l_imuStates_st,
																	l_kalmanAngles_st,
																	l_compAngles_st);
				if ( l_sendState_bl != M_HAL_MATLAB_SUCCESS_UI8 )
				{
					printf("UDP-Packet error\n");
				}
				else
				{
					printf("Sent packet\n");
				}
				usleep( 20000 ); //20ms = 50Hz
			}
			// close udp connection
			g_halMatlab_closeSocket_bl(l_udpSocket_i32);
			break;
		}
		case 9:
		{
			halAccmag_dataContainer l_sensorData_st;
			printf("IMU Acceleration and Compass Test\n");
			if ( g_halAccmag_initSensor_bl() != M_HAL_ACCMAG_SUCCESS_BL )
			{
				printf( "Init failed!\n" );
				return 1;
			}

			while (1)
			{
				if ( g_halAccmag_triggerAccUpdate_bl() != M_HAL_ACCMAG_SUCCESS_BL )
				{
					printf( "ACC update failed!\n" );
					return 1;
				}
				if ( g_halAccmag_triggerMagUpdate_bl() != M_HAL_ACCMAG_SUCCESS_BL )
				{
					printf( "MAG update failed!\n" );
					return 1;
				}

				l_sensorData_st = g_halAccmag_getAccMagContainer_st();

				printf("Acc - x:%f y:%lf z:%f | Mag - x:%.10f y:%.10f z:%.10f\n",
						l_sensorData_st.acc.x_f64,
						l_sensorData_st.acc.y_f64,
						l_sensorData_st.acc.z_f64,
						l_sensorData_st.mag.x_f64,
						l_sensorData_st.mag.y_f64,
						l_sensorData_st.mag.z_f64
						);

				usleep( 250000 );
			}
			break;
		}
		case 10:
		{
			double pressure=0;
			double temp=0;
			strGyro GyroValues;
			double Gyrotemp=0;
			g_halBaro_initBaro_i32();
			g_halGyro_initGyro_i32();
			printf("IMU Barometer pressure test");
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
			break;
		}
		case 11:
		{
			double pressure=0;
			double temp=0;
			strGyro GyroValues;
			double Gyrotemp=0;
			printf("IMU Gyroscope test\n");
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
			break;
		}
		case 12:
		{
			static	double l_MatrixA_f64[3][3]={{1,2,1},{2,5,4},{1,4,9}};
			//static	double l_MatrixA_f64[3][3]={{4,-14,-2},{-14,65,3},{-2,3,3}};
			//static	double l_MatrixA_f64[2][3]={{1,2,9},{2,5,9}};
			//static	double l_MatrixA_f64[1][3]={{1,2,9}};
			static	double l_MatrixB_f64[3][3]={{3,6,7},{2,5,9},{4,6,8}};
			//static	double l_MatrixB_f64[3][2]={{3,6},{2,5},{4,6}};
			static	double l_outputMatrix_f64[3][3]={{0,0,0},{0,0,0},{0,0,0}};
			//static	double l_outputMatrix_f64[3][2]={{0,0},{0,0},{0,0}};
			printf("matrix lib function test\n");
			while(1)
			{
				g_sigMath_matrixEye_bl((double*)l_outputMatrix_f64,3,3);
				sleep(1);
				g_sigMath_matrixInitialize_bl((double*)l_outputMatrix_f64,3,3,1);
				sleep(1);
				g_sigMath_matrixMultiplikation_bl((double*)l_outputMatrix_f64,(double*)l_MatrixA_f64,3,3,(double*)l_MatrixB_f64,3,3);
				sleep(1);
				g_sigMath_matrixAddition_bl((double*)l_outputMatrix_f64,(double*)l_MatrixA_f64,3,3,(double*)l_MatrixB_f64,3,3);
				sleep(1);
				g_sigMath_matrixSubtraktion_bl((double*)l_outputMatrix_f64,(double*)l_MatrixA_f64,3,3,(double*)l_MatrixB_f64,3,3);
				sleep(1);
				g_sigMath_matrixAssignment_bl((double*)l_outputMatrix_f64,3,3,(double*)l_MatrixA_f64,3,3);
				sleep(1);
				g_sigMath_matrixTransponiert_bl((double*)l_outputMatrix_f64,(double*)l_MatrixA_f64,3,3);
				sleep(1);
				g_sigMath_matrixInverse_bl((double*)l_outputMatrix_f64,(double*)l_MatrixA_f64,3,3);
				sleep(1);
			}
			break;
		}
		default:
		{
			printf("Nothing found");
			break;
		}
	}
	return 0;
}
