/*!
 * \file ADCTest.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
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
#include "../hal/MOTOR/MOTOR.h"

extern float g_halADC_get_ui16(unsigned char );

#define REMOTE_PORT 5000
#define REMOTE_ADDR "192.168.22.159"

typedef enum enumTestCases
{
    TESTADC=1,
    TESTBATTERY,
    TESTGPS,
    TESTIMU,
    TESTLASER,
    TESTUART,
    TESTMATLABIMU,
    TESTMATLABKALMAN,
    TESTACCMAG,
    TESTGYRO,
    TESTBARO,
    TESTMATRIXLIB,
    TESTUDP,
    TESTUDPTRANSFER,
    ALLANGLES,
    TESTALLSENSORDATA,
    TESTMOTORPWM,
    TESTMOTORISR,
    TESTMOTORTXT,
    TESTGUI,
    TESTEND
} enumTestcases;


static char str[500];
static char str2[500];

int main(char *argv, int argc) {
    while(1){
        enumTestcases runCommand = 0;
        int testValueLength =20;
        char testValue[testValueLength];
        int isSelected = 0;
        scanf("%s",testValue);
//        do{
//            sleep(2);
//            isSelected = readTestcaseFile(&testValue[0] ,testValueLength);
//        }while (isSelected != 1);

        printf("Received string is %s\n", testValue);
        if ( strcmp(testValue,"testadc")  == 0 )
            runCommand = TESTADC;
        else if ( strcmp(testValue,"testbattery")  == 0 )
            runCommand = TESTBATTERY;
        else if ( strcmp(testValue,"testgps")  == 0 )
            runCommand = TESTGPS;
        else if ( strcmp(testValue,"testimu")  == 0 )
            runCommand = TESTIMU;
        else if ( strcmp(testValue,"testlaser")  == 0 )
            runCommand = TESTLASER;
        else if ( strcmp(testValue,"testuart")  == 0 )
            runCommand = TESTUART;
        else if ( strcmp(testValue,"testmatlabimu")  == 0 )
            runCommand = TESTMATLABIMU;
        else if ( strcmp(testValue,"testmatlabkalman")  == 0 )
            runCommand = TESTMATLABKALMAN;
        else if ( strcmp(testValue,"testaccmag")  == 0 )
            runCommand = TESTACCMAG;
        else if ( strcmp(testValue,"testgyro")  == 0 )
            runCommand = TESTGYRO;
        else if ( strcmp(testValue,"testbaro")  == 0 )
            runCommand = TESTBARO;
        else if ( strcmp(testValue,"testmatrixlib")  == 0 )
            runCommand = TESTMATRIXLIB;
        else if ( strcmp(testValue,"testudp")  == 0 )
            runCommand = TESTUDP;
        else if ( strcmp(testValue,"testudptransfer")  == 0 )
            runCommand = TESTUDPTRANSFER;
        else if ( strcmp(testValue,"testallangles")  == 0 )
            runCommand = ALLANGLES;
        else if ( strcmp(testValue,"testallsensordata")  == 0 )
                runCommand = TESTALLSENSORDATA;
        else if ( strcmp(testValue,"testmotorpwm")  == 0 )
                runCommand = TESTMOTORPWM;
        else if ( strcmp(testValue,"testmotorisr")  == 0 )
                runCommand = TESTMOTORISR;
        else if ( strcmp(testValue,"testmotortxt")  == 0 )
                    runCommand = TESTMOTORTXT;
        else if( strcmp(testValue,"testgui") == 0 )
                    runCommand = TESTGUI;

        switch (runCommand)
        {
            case TESTADC:
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
            case TESTBATTERY:
            {
                double l_batterLevel_f64=0;
                printf("Starting Battery Test\n");
                int i = kbhit();
                while(i != 'q')
                {
                    g_halBatCheck_readBatStatusFromI2C_bl();
                    l_batterLevel_f64=g_halBatCheck_getBatteryStatus_f64();
                    printf("Measured Voltage: %5.3f\n",l_batterLevel_f64);
                    sleep(1);
                }
                break;
            }
            case TESTGPS:
            {
                struct strPosition main_longitude;
                struct strPosition main_latitude;
                printf("Starting GPS Test\n");
                int i = kbhit();
                while(i != 'q')
                {
                    g_halGps_getData_i32();
                }
                break;
            }
            case TESTIMU:
            {
                halImu_orientationValues l_imuMeasurements_st;
                printf("Starting IMU Test\n");
                g_halImu_initImuSensors_bl();
                int i = kbhit();
                while(i != 'q')
                {
                    g_halImu_triggerImuReading_bl();
                    g_halImu_triggerBaroReading_bl();
                    g_halImu_triggerGyroReading_bl();
                    g_halImu_triggerAccReading_bl();

                    l_imuMeasurements_st=g_halImu_getImuValues_str();

                    printf("Pressure: %5.3f    ;    Temperature:  %5.3f\n",l_imuMeasurements_st.pressure_f64,l_imuMeasurements_st.temperature_f64);
                    printf("roll: %5.3f    ;    pitch:  %5.3f    ;    yaw:  %5.3f\n",l_imuMeasurements_st.gyro.roll_f64, l_imuMeasurements_st.gyro.pitch_f64, l_imuMeasurements_st.gyro.yaw_f64);
                    printf("X: %5.3f ; Y:  %5.3f ; Z:  %5.3f\n",l_imuMeasurements_st.acc.x_f64,l_imuMeasurements_st.acc.y_f64,l_imuMeasurements_st.acc.z_f64);
                    printf("X: %5.10f ; Y:  %5.10f ; Z:  %5.10f\n\n\n\n",l_imuMeasurements_st.mag.x_f64,l_imuMeasurements_st.mag.y_f64,l_imuMeasurements_st.mag.z_f64);
                }
                break;
            }
            case TESTLASER:
            {
                double dist=0;
                printf("Starting LASER Test\n");
                int i = kbhit();
                while(i != 'q')
                {
                    g_LIDAR_readDistanceFromI2C_i32();
                    //usleep(100000);

                    dist=g_LIDAR_getDistance_f64();

                    printf("Distance: %4.2f m\n",dist);
                    usleep(500*1000);
                }
                break;
            }
            case TESTUART:
            {
                char rec_char='z';
                char *ptr_rec_char=&rec_char;
                printf("Starting UART Test\n");
                FILE *fp=(FILE *)-1;
                //open file to write received data from GPS
                fp = (FILE *)open("GPS_logging.txt",100 | 01,400);
                sleep(1);
                int i = kbhit();
                while(i != 'q')
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
            case TESTMATLABIMU:
            {
                printf("Starting IMU Matlab Test\n");
                unsigned char    l_remoteHostAddr_rg4ui8[4]     = {192,168,22,160};
                unsigned short    l_remoteHostPort_ui16        = 5000;
                int                l_udpSocket_i32;
                unsigned int    l_sendState_bl;

                // open udp connection
                l_udpSocket_i32 = g_halMatlab_initConnection_i32( l_remoteHostAddr_rg4ui8, l_remoteHostPort_ui16 );

                halImu_orientationValues l_imuMeasurements_st;
                g_halImu_initImuSensors_bl();

                int i = kbhit();
                while(i != 'q')
                {
                    g_halImu_triggerImuReading_bl();
                    g_halImu_triggerBaroReading_bl();
                    g_halImu_triggerGyroReading_bl();
                    g_halImu_triggerAccReading_bl();

                    l_imuMeasurements_st=g_halImu_getImuValues_str();

                    l_sendState_bl = g_halMatlab_sendImuState_bl(l_udpSocket_i32, l_imuMeasurements_st);
                    printf("Temp %f\n", l_imuMeasurements_st.temperature_f64);
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
            case TESTMATLABKALMAN:
            {
                printf("Starting Kalman Orientation Matlab Test\n");
                unsigned char    l_remoteHostAddr_rg4ui8[4]     = {192,168,22,160};
                unsigned short    l_remoteHostPort_ui16        = 5000;
                int                l_udpSocket_i32;
                unsigned int    l_sendState_bl;

                sigOri_orientationAngles    l_kalmanAngles_st;
                sigOri_orientationAngles    l_compAngles_st;
                halImu_orientationValues    l_imuStates_st;

                // open udp connection
                l_udpSocket_i32 = g_halMatlab_initConnection_i32( l_remoteHostAddr_rg4ui8, l_remoteHostPort_ui16 );

                g_sigOri_initMatrices_bl();
                g_sigOri_initImuSensors_bl();

                int i = kbhit();
                while(i != 'q')
                {
                    g_sigOri_calcKalmanOrientation_bl();
                    g_sigOri_calcComplementaryOrientation_bl();

                    l_kalmanAngles_st     = g_sigOri_getAnglesKalman_bl();
                    l_compAngles_st        = g_sigOri_getAnglesComplementary_bl();
                    l_imuStates_st         = g_halImu_getImuValues_str();

                    printf("Temp%f\nMag%f",l_imuStates_st.temperature_f64, l_imuStates_st.mag.x_f64);
                    l_sendState_bl = g_halMatlab_sendSigAllStates_bl(    l_udpSocket_i32,
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
            case TESTACCMAG:
            {
                halAccmag_dataContainer l_sensorData_st;
                printf("IMU Acceleration and Compass Test\n");
                if ( g_halAccmag_initSensor_bl() != M_HAL_ACCMAG_SUCCESS_BL )
                {
                    printf( "Init failed!\n" );
                    return 1;
                }

                int i = kbhit();
                while(i != 'q')
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
            case TESTBARO:
            {
                double pressure=0;
                double temp=0;
                sigOri_orientationAngles GyroValues;
                double Gyrotemp=0;
                g_halBaro_initBaro_i32();
                g_halGyro_initGyro_i32();
                printf("IMU Barometer pressure test");
                int i = kbhit();
                while(i != 'q')
                {
                    g_halBaro_readPressureFromI2C_i32();
                    usleep(100000);
                    g_halBaro_readTemperatureFromI2C_i32();
                    usleep(100000);
                    pressure=g_halBaro_getPressure_f64();
                    temp=g_halBaro_getTemperature_f64();
                    printf("Pressure: %5.3f    ;    Temperature:  %5.3f\n",pressure,temp);
                    usleep(100000);


                    g_halGyro_readGyroscopeFromI2C_i32();
                    usleep(100000);
                    g_halGyro_readTemperatureFromI2C_i32();
                    usleep(100000);
                    GyroValues=g_halGyro_getGyroscope_st();
                    Gyrotemp=g_halGyro_getTemperature_f64();
                    printf("roll: %5.3f    ;    pitch:  %5.3f    ;    yaw:  %5.3f\n",GyroValues.roll_f64, GyroValues.pitch_f64, GyroValues.yaw_f64);
                    usleep(100000);
                }
                break;
            }
            case TESTGYRO:
            {
                double pressure=0;
                double temp=0;
                sigOri_orientationAngles GyroValues;
                double Gyrotemp=0;
                printf("IMU Gyroscope test\n");
                g_halBaro_initBaro_i32();
                g_halGyro_initGyro_i32();
                int i = kbhit();
                while(i != 'q')
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
                    printf("roll: %5.3f    ;    pitch:  %5.3f    ;    yaw:  %5.3f\n",GyroValues.roll_f64, GyroValues.pitch_f64, GyroValues.yaw_f64);
                    //usleep(100000);
                }
                break;
            }
            case TESTMATRIXLIB:
            {
                static    double l_MatrixA_f64[3][3]={{1,2,1},{2,5,4},{1,4,9}};
                //static    double l_MatrixA_f64[3][3]={{4,-14,-2},{-14,65,3},{-2,3,3}};
                //static    double l_MatrixA_f64[2][3]={{1,2,9},{2,5,9}};
                //static    double l_MatrixA_f64[1][3]={{1,2,9}};
                static    double l_MatrixB_f64[3][3]={{3,6,7},{2,5,9},{4,6,8}};
                //static    double l_MatrixB_f64[3][2]={{3,6},{2,5},{4,6}};
                static    double l_outputMatrix_f64[3][3]={{0,0,0},{0,0,0},{0,0,0}};
                //static    double l_outputMatrix_f64[3][2]={{0,0},{0,0},{0,0}};
                printf("matrix lib function test\n");
                int i = kbhit();
                while(i != 'q')
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
            case TESTUDP:
            {
                printf("simple send udp test...");
                int clientSocket;
                char message[20] = "Hello\n";
                struct sockaddr_in serverAddress;
                socklen_t addressSize;

                /*Create UDP socket*/
                clientSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

                serverAddress.sin_family = PF_INET;
                serverAddress.sin_port = htons(REMOTE_PORT);
                serverAddress.sin_addr.s_addr = inet_addr(REMOTE_ADDR);

                memset(serverAddress.sin_zero, '\0', sizeof(serverAddress.sin_zero));

                /*Initialize size variable to be used later on*/
                addressSize = sizeof(serverAddress);

                printf("Start Sending Messages\n");

                int i = kbhit();
                while(i != 'q')
                {
                    sleep(1);
                    /* Send N bytes of BUF on socket FD to peer at address ADDR (which is
                       ADDR_LEN bytes long).  Returns the number sent, or -1 for errors.

                       This function is a cancellation point and therefore not marked with
                       __THROW.  */
                    sendto(clientSocket, message, sizeof(message), 0,
                            (struct sockaddr *)&serverAddress,addressSize);
                    printf("And send again....\n");
                }
                break;
            }
            case TESTUDPTRANSFER:
            {
                sigOri_orientationAngles    l_kalmanAngles_st;
                sigOri_orientationAngles    l_compAngles_st;

                halImu_orientationValues    l_imuStates_st;
                halMatlab_rtSigAllStatePayload    l_rtCompleteSigPayload_st;


                struct timespec                    l_timestamp_st;


                printf("Starting Transfer matlab data on udp test\n");

                int val=0;
                int socketclient = 0;
                struct sockaddr_in remoteaddress;

                remoteaddress.sin_family = PF_INET;
                remoteaddress.sin_port = htons(REMOTE_PORT);

                (void)inet_aton(REMOTE_ADDR, &remoteaddress.sin_addr); //dot to integer and then host to network byte order

                socketclient = socket(PF_INET, SOCK_DGRAM, 0);


                g_sigOri_initMatrices_bl();
                g_sigOri_initImuSensors_bl();

                int i = kbhit();
                while(i != 'q')
                {
                    g_sigOri_calcKalmanOrientation_bl();
                    g_sigOri_calcComplementaryOrientation_bl();

                    l_kalmanAngles_st     = g_sigOri_getAnglesKalman_bl();
                    l_compAngles_st        = g_sigOri_getAnglesComplementary_bl();
                    l_imuStates_st         = g_halImu_getImuValues_str();


                    /*
                     * first of all: get an accurate timestamp for this data telegram
                     * Hint: ensure that 'librt' is also linked in the project!
                     *       Eclipse: Goto Project->Properties.
                     *                Select C/C++-Build->Settings
                     *                Select tab view 'Tool Settings'.
                     *                Select 'Cross G++ Linker'->Libraries
                     *                and add the entry 'rt' to 'Libraries (-l)'
                     *
                     *       GCC on the commandline: simply add '-lrt' to your gcc options
                     */
                    if ( clock_gettime(CLOCK_REALTIME, &l_timestamp_st) != M_HAL_MATLAB_SUCCESS_UI8)
                    {
                        return M_HAL_MATLAB_FAILED_UI8;
                    }

                    clock_gettime(CLOCK_REALTIME, &l_timestamp_st);

                    //assmeble timestamp and
                    l_rtCompleteSigPayload_st.timestamp_st                 = l_timestamp_st;
                    l_rtCompleteSigPayload_st.imuState_st                = l_imuStates_st;
                    l_rtCompleteSigPayload_st.kalmanSigState_st         = l_kalmanAngles_st;
                    l_rtCompleteSigPayload_st.complementarySigState_st    = l_compAngles_st;

                    printf("START MEASUREMENT\n");
                    sprintf(str, "sec =  %d, nano = %d",
                            l_rtCompleteSigPayload_st.timestamp_st.tv_sec, l_rtCompleteSigPayload_st.timestamp_st.tv_nsec);
                    puts(str);
                    sprintf(str, "acc = %f %f %f",
                            l_rtCompleteSigPayload_st.imuState_st.acc.x_f64, l_rtCompleteSigPayload_st.imuState_st.acc.y_f64, l_rtCompleteSigPayload_st.imuState_st.acc.z_f64);
                    puts(str);
                    sprintf(str, "mag = %f %f %f",
                            l_rtCompleteSigPayload_st.imuState_st.mag.x_f64, l_rtCompleteSigPayload_st.imuState_st.mag.y_f64, l_rtCompleteSigPayload_st.imuState_st.mag.z_f64);
                    puts(str);
                    sprintf(str, "roll %f, pitch %f yaw  %f",
                            l_rtCompleteSigPayload_st.imuState_st.gyro.roll_f64, l_rtCompleteSigPayload_st.imuState_st.gyro.pitch_f64, l_rtCompleteSigPayload_st.imuState_st.gyro.yaw_f64 );
                    puts(str);
                    sprintf(str, "temperature = %f",
                            l_rtCompleteSigPayload_st.imuState_st.temperature_f64);
                    puts(str);
                    sprintf(str, "pressure = %f",
                            l_rtCompleteSigPayload_st.imuState_st.pressure_f64);
                    puts(str);
                    sprintf(str, "KALMAN yaw %f, pitch %f roll %f",
                            l_rtCompleteSigPayload_st.kalmanSigState_st.yaw_f64, l_rtCompleteSigPayload_st.kalmanSigState_st.pitch_f64, l_rtCompleteSigPayload_st.kalmanSigState_st.roll_f64);
                    puts(str);
                    sprintf(str, "COMPLEMENTARY yaw %f, pitch %f roll %f",
                            l_rtCompleteSigPayload_st.complementarySigState_st.yaw_f64, l_rtCompleteSigPayload_st.complementarySigState_st.pitch_f64, l_rtCompleteSigPayload_st.complementarySigState_st.roll_f64);
                    puts(str);

                    //printf("Sending time %d and Temperature %f\n", l_rtCompleteSigPayload_st.timestamp_st.tv_sec, l_rtCompleteSigPayload_st.imuState_st.temperature_f64);
                    sendto(socketclient, (unsigned char *)&l_rtCompleteSigPayload_st , (size_t)sizeof( l_rtCompleteSigPayload_st ),  0, (struct sockaddr *)&remoteaddress, sizeof(remoteaddress));

                    usleep( 50000 ); //20ms = 50Hz
                }
                // close udp connection
                close(socketclient);
                break;
            }
            case ALLANGLES:
            {
                sigOri_orientationAngles    l_GyroPerStepAngles_st;
                sigOri_orientationAngles    l_AccMagAngles_st;
                sigOri_orientationAngles    l_kalmanAngles_st;
                sigOri_orientationAngles    l_compAngles_st;
                halImu_orientationValues    l_imuStates_st;

                halMatlab_rtSigRollPitchYawStatePayload    l_rtRollPitchYawSigPayload_st;

                struct timespec                    l_timestamp_st;

                printf("Starting Transfer matlab data on all angles\n");

                int val=0;
                int socketclient = 0;
                struct sockaddr_in remoteaddress;

                remoteaddress.sin_family = PF_INET;
                remoteaddress.sin_port = htons(REMOTE_PORT);

                (void)inet_aton(REMOTE_ADDR, &remoteaddress.sin_addr); //dot to integer and then host to network byte order

                socketclient = socket(PF_INET, SOCK_DGRAM, 0);

                g_sigOri_initMatrices_bl();
                g_sigOri_initImuSensors_bl();

                int i = kbhit();
                while(i != 'q')
                {
                    g_sigOri_calcKalmanOrientation_bl();
                    g_sigOri_calcComplementaryOrientation_bl();

                    l_imuStates_st         = g_halImu_getImuValues_str();
                    l_GyroPerStepAngles_st = g_sigOri_getAnglesGyroPerStep_bl();
                    l_AccMagAngles_st = g_sigOri_getAnglesAccMagCalc_bl();
                    l_kalmanAngles_st     = g_sigOri_getAnglesKalman_bl();
                    l_compAngles_st        = g_sigOri_getAnglesComplementary_bl();


                    if ( clock_gettime(CLOCK_REALTIME, &l_timestamp_st) != M_HAL_MATLAB_SUCCESS_UI8)
                    {
                        return M_HAL_MATLAB_FAILED_UI8;
                    }

                    clock_gettime(CLOCK_REALTIME, &l_timestamp_st);

                    //assmeble timestamp and
                    l_rtRollPitchYawSigPayload_st.timestamp_st                 = l_timestamp_st;
                    l_rtRollPitchYawSigPayload_st.angularVelocityGyroFromImu_st         = l_imuStates_st.gyro;
                    l_rtRollPitchYawSigPayload_st.angleFromGyroStepCalculation_st    = l_GyroPerStepAngles_st;
                    l_rtRollPitchYawSigPayload_st.angleFromAccMagCalculation_st         = l_AccMagAngles_st;
                    l_rtRollPitchYawSigPayload_st.angleFromkalmanSigState_st         = l_kalmanAngles_st;
                    l_rtRollPitchYawSigPayload_st.angleFromcomplementarySigState_st    = l_compAngles_st;


                    printf("START MEASUREMENT\n");
                    sprintf(str, "sec =  %d, nano = %d",
                            l_rtRollPitchYawSigPayload_st.timestamp_st.tv_sec, l_rtRollPitchYawSigPayload_st.timestamp_st.tv_nsec);
                    puts(str);
                    sprintf(str, "Raw GYro Angular velocity roll %f, pitch %f yaw  %f",
                            l_rtRollPitchYawSigPayload_st.angularVelocityGyroFromImu_st.roll_f64, l_rtRollPitchYawSigPayload_st.angularVelocityGyroFromImu_st.pitch_f64, l_rtRollPitchYawSigPayload_st.angularVelocityGyroFromImu_st.yaw_f64 );
                    puts(str);
                    sprintf(str, "Gyro Angles roll %f, pitch %f yaw  %f",
                            l_rtRollPitchYawSigPayload_st.angleFromGyroStepCalculation_st.roll_f64, l_rtRollPitchYawSigPayload_st.angleFromGyroStepCalculation_st.pitch_f64, l_rtRollPitchYawSigPayload_st.angleFromGyroStepCalculation_st.yaw_f64 );
                    puts(str);
                    sprintf(str, "ACC MAG CALC Angles roll %f, pitch %f yaw  %f",
                            l_rtRollPitchYawSigPayload_st.angleFromAccMagCalculation_st.roll_f64, l_rtRollPitchYawSigPayload_st.angleFromAccMagCalculation_st.pitch_f64, l_rtRollPitchYawSigPayload_st.angleFromAccMagCalculation_st.yaw_f64 );
                    puts(str);
                    sprintf(str, "COMPLEMENTARY Angles roll %f, pitch %f yaw %f",
                            l_rtRollPitchYawSigPayload_st.angleFromcomplementarySigState_st.roll_f64, l_rtRollPitchYawSigPayload_st.angleFromcomplementarySigState_st.pitch_f64, l_rtRollPitchYawSigPayload_st.angleFromcomplementarySigState_st.yaw_f64);
                    puts(str);
                    sprintf(str, "KALMAN Angles roll %f, pitch %f yaw %f",
                            l_rtRollPitchYawSigPayload_st.angleFromkalmanSigState_st.roll_f64, l_rtRollPitchYawSigPayload_st.angleFromkalmanSigState_st.pitch_f64, l_rtRollPitchYawSigPayload_st.angleFromkalmanSigState_st.yaw_f64);
                    puts(str);

                    sendto(socketclient, (unsigned char *)&l_rtRollPitchYawSigPayload_st , (size_t)sizeof( l_rtRollPitchYawSigPayload_st ),  0, (struct sockaddr *)&remoteaddress, sizeof(remoteaddress));

                    usleep( 50000 ); //20ms = 50Hz
                }
                // close udp connection
                close(socketclient);
                break;
            }
            case TESTALLSENSORDATA:
            {
                printf("Starting IMU send all Sensor Values\n");
                unsigned char    l_remoteHostAddr_rg4ui8[4]   = {192,168,22,160};
                unsigned short   l_remoteHostPort_ui16        = 5000;
                int              l_udpSocket_i32;
                unsigned int     l_sendState_bl;

                // open udp connection
                l_udpSocket_i32 = g_halMatlab_initConnection_i32( l_remoteHostAddr_rg4ui8, l_remoteHostPort_ui16 );

                halImu_orientationValues l_imuMeasurements_st;
                g_halImu_initImuSensors_bl();

                int i = kbhit();
                while(i != 'q')
                {
                    g_halImu_triggerImuReading_bl();
                    g_halImu_triggerBaroReading_bl();
                    g_halImu_triggerGyroReading_bl();
                    g_halImu_triggerAccReading_bl();

                    l_imuMeasurements_st=g_halImu_getImuValues_str();

                    l_sendState_bl = g_halMatlab_sendImuState_bl(l_udpSocket_i32, l_imuMeasurements_st);

                    printf("Acc X %f \n", l_imuMeasurements_st.acc.x_f64);
                    printf("Acc Y %f \n", l_imuMeasurements_st.acc.y_f64);
                    printf("Acc Z %f \n", l_imuMeasurements_st.acc.z_f64);
                    printf("Mag X %f \n", l_imuMeasurements_st.mag.x_f64);
                    printf("Mag Y %f \n", l_imuMeasurements_st.mag.y_f64);
                    printf("Mag Z %f \n", l_imuMeasurements_st.mag.z_f64);
                    printf("Gyro yaw %f \n", l_imuMeasurements_st.gyro.yaw_f64);
                    printf("Gyro pitch %f \n", l_imuMeasurements_st.gyro.pitch_f64);
                    printf("Gyro roll %f \n", l_imuMeasurements_st.gyro.roll_f64);
                    printf("Temp %f \n", l_imuMeasurements_st.temperature_f64);
                    printf("Press %f \n", l_imuMeasurements_st.pressure_f64);
                    printf("##########################################\n");

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

            case TESTMOTORPWM:
            {
                char BLCtrlADRExecuteOrder[DEFMotorsCount];
                char sendBuffer[1];
                int i ,j = 0;
                unsigned int pwmValue;

                const int STEPSIZE = 5;
                const int MAXPWMVALUE = 0x75;

                GetBLCtrlADRExecuteOrder(&BLCtrlADRExecuteOrder[0]);

                printf("Start Testing Motors with PWM");

                while(j != 1)
                {
                    sendBuffer[0]=pwmValue;
                    for(i = 0; i < DEFMotorsCount ;i++)
                    {
                        g_lldI2c_WriteI2c_bl(BLCtrlADRExecuteOrder[i],&sendBuffer[0],1);
                        usleep(10);//10us delay for HW Driver
                    }

                    usleep(10000);//10ms

                    pwmValue = pwmValue + STEPSIZE;
                    if(pwmValue > MAXPWMVALUE )
                    {
                        j = 1;
                    }

                }

            break;
            }
            case TESTMOTORISR:
                    {    //starts with first press of + or - than enter
                        //leave with pressing 'q'
                        printf("Start Testing Motors with ISR");
                        InitMotor(9000);

                        int sendValue=DEFMotorSetpointMIN;
                        int i = kbhit();
                        while(i != 'q'){
                            if(GetFlagRunSendPwmToMotor() == 1){
                                sendPwmToMotor();
                            }

                            i = kbhit();
                            int value;
                            if(i == '+'){
                                int k = kbhit();
                                switch (k){
                                case '0':
                                    value = GetPwmMotor(0);
                                    (value < 100) ? value++ : (value=100);
                                    SetPwmMotor(DEFMotorNo1_PWM, value ,0);
                                    break;
                                case '1':
                                    value = GetPwmMotor(1);
                                    (value < 100)? value++: (value=100);
                                    SetPwmMotor(DEFMotorNo2_PWM, value ,0);
                                    break;
                                case '2':
                                    value = GetPwmMotor(2);
                                    (value < 100)? value++: (value=100);
                                    SetPwmMotor(DEFMotorNo3_PWM, value ,0);
                                    break;
                                case '3':
                                    value = GetPwmMotor(3);
                                    (value < 100)? value++: (value=100);
                                    SetPwmMotor(DEFMotorNo4_PWM, value ,0);
                                    break;
                                case '4':
                                    value = GetPwmMotor(4);
                                    (value < 100)? value++: (value=100);
                                    SetPwmMotor(DEFMotorNo5_PWM, value ,0);
                                    break;
                                case '5':
                                    value = GetPwmMotor(5);
                                    (value < 100)? value++: (value=100);
                                    SetPwmMotor(DEFMotorNo6_PWM, value ,0);
                                    break;
                                case '6':
                                    value = GetPwmMotor(6);
                                    (value < 100)? value++: (value=100);
                                    SetPwmMotor(DEFMotorNo7_PWM, value ,0);
                                    break;
                                case '7':
                                    value = GetPwmMotor(7);
                                    (value < 100)? value++: (value=100);
                                    SetPwmMotor(DEFMotorNo8_PWM, value ,0);
                                    break;
                                default:
                                    break;
                                }
                            }else if(i == 45){
                                int k = kbhit();
                                switch (k){
                                case '0':
                                    value = GetPwmMotor(0);
                                    value > 0? value--: (value=DEFMotorSetpointMIN);
                                    SetPwmMotor(DEFMotorNo1_PWM, value ,0);
                                    break;
                                case '1':
                                    value = GetPwmMotor(1);
                                    value > 0? value--: (value=DEFMotorSetpointMIN);
                                    SetPwmMotor(DEFMotorNo2_PWM, value ,0);
                                    break;
                                case '2':
                                    value = GetPwmMotor(2);
                                    value > 0? value--: (value=DEFMotorSetpointMIN);
                                    SetPwmMotor(DEFMotorNo3_PWM, value ,0);
                                    break;
                                case '3':
                                    value = GetPwmMotor(3);
                                    value > 0? value--: (value=DEFMotorSetpointMIN);
                                    SetPwmMotor(DEFMotorNo4_PWM, value ,0);
                                    break;
                                case '4':
                                    value = GetPwmMotor(4);
                                    value > 0? value--: (value=DEFMotorSetpointMIN);
                                    SetPwmMotor(DEFMotorNo5_PWM, value ,0);
                                    break;
                                case '5':
                                    value = GetPwmMotor(5);
                                    value > 0? value--: (value=DEFMotorSetpointMIN);
                                    SetPwmMotor(DEFMotorNo6_PWM, value ,0);
                                    break;
                                case '6':
                                    value = GetPwmMotor(6);
                                    value > 0? value--: (value=DEFMotorSetpointMIN);
                                    SetPwmMotor(DEFMotorNo7_PWM, value ,0);
                                    break;
                                case '7':
                                    value = GetPwmMotor(7);
                                    value > 0? value--: (value=DEFMotorSetpointMIN);
                                    SetPwmMotor(DEFMotorNo8_PWM, value ,0);
                                    break;
                                }
                            }
                            /* Do Other Things*/
                        }

                    break;
                    }

            case TESTMOTORTXT:
                    {
                        FILE *testFile;
                        int lineLength =80;
                        char line[lineLength];
                        int delayS=1;
                        time_t timeStamp , currentTime;


                        printf("Start Testing Motors reading txt file\n");

                        InitMotor(9000);

                        //Wait 1 Sec
                        time(&timeStamp);
                        time(&currentTime);
                        if( difftime(currentTime, timeStamp) >= 1){
                            if(GetFlagRunSendPwmToMotor() == 1){
                                sendPwmToMotor();
                            }
                        }
                        if ((testFile = fopen("/home/pi/testfiles/MotorTest.txt", "r")) == NULL){
                            fprintf(stderr, "File kann nicht geöffnet werden");
                            exit(0);
                        }

                        time(&timeStamp);

                        while(1){ // test ends when end of file reached
                            if(GetFlagRunSendPwmToMotor() == 1){
                                sendPwmToMotor();
                            }

                            time(&currentTime);
                            if( difftime(currentTime, timeStamp) >= delayS){
                                time(&timeStamp);
                                if((fgets(line, lineLength, testFile)) != NULL)
                                {
                                    printf("\n%s", line);
                                    delayS = decodeline(&line[0], sizeof(line));
                                }else{
                                    break;
                                }
                            }
                        }



                        break;
                    }

            default:
            case TESTEND:
            {
                printf("Nothing found");
                break;
            }


        case TESTGUI:
                    {
                        printf("Sending random numbers to test gui");
                        int clientSocket;

                        struct sockaddr_in serverAddress;
                        socklen_t addressSize;

                        /*Create UDP socket*/
                        clientSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

                        serverAddress.sin_family = PF_INET;
                        serverAddress.sin_port = htons(REMOTE_PORT);
                        serverAddress.sin_addr.s_addr = inet_addr(REMOTE_ADDR);

                        memset(serverAddress.sin_zero, '\0', sizeof(serverAddress.sin_zero));

                        /*Initialize size variable to be used later on*/
                        addressSize = sizeof(serverAddress);

                        printf("Start Sending Messages\n");

                        int i = kbhit();
                        while(i != 'q')
                        {
                            sleep(1);

                            int random = rand()%150;
                            char randomToSend[3];



                            sprintf(randomToSend,"%d\n",random);


                            sendto(clientSocket, randomToSend, sizeof(randomToSend), 0,
                                    (struct sockaddr *)&serverAddress,addressSize);
                            printf("And send again....\n");

                        }
                        break;
                    }
        }
    }//end while(1)
    return 0;
}



int readTestcaseFile(char testcase[] , int length){
    FILE *testCasesFile;
    int isSelected =0;
    char* stringToken;
    char charIsSelected[length];
    char fullLine[30];
    int i;

    if ((testCasesFile = fopen("/home/pi/testfiles/_Testcases", "r+")) == NULL){
        fprintf(stderr, "File kann nicht geöffnet werden (w+)");
        exit(0);
    }

    while((fgets(testcase, length, testCasesFile)) != NULL){
        stringToken= strtok(testcase, "=\n");
        strcpy(testcase, stringToken);

        stringToken= strtok(NULL, "=\n");
        strcpy(charIsSelected, stringToken);
        isSelected = charIsSelected[0] - '0';

        if(isSelected == 1){
            strcpy(fullLine,testcase);
            for (i =0 ; i < sizeof(fullLine);i++){
                if(fullLine[i] == '\0'){
                    fullLine[i]= '=';
                    i++;
                    fullLine[i]= '1'; //Set to 1 if you dont want to set the test to 0 in _testcase
                    i++;
                    fullLine[i]= '\n';
                    i++;
                    fullLine[i]= '\0';
                    break;
                }//if
            }//for
            //Change Postion of seek
            fseek(testCasesFile, -i, SEEK_CUR);
            //Write line
            fputs(fullLine , testCasesFile);
            fclose(testCasesFile);
            return 1;
        }//if
    }//while( not end of file read)
    /* Not Testcase selected*/
    return 0;

}


#include <termios.h>

int kbhit(void)
{
    struct termios term, oterm;
      int fd = 0;
      int c = 0;
      tcgetattr(fd, &oterm);
      memcpy(&term, &oterm, sizeof(term));
      term.c_lflag = term.c_lflag & (!ICANON);
      term.c_cc[VMIN] = 0;
      term.c_cc[VTIME] = 1;
      tcsetattr(fd, TCSANOW, &term);
      c = getchar();
      tcsetattr(fd, TCSANOW, &oterm);
      return c; // gibt -1 zurück, wenn kein Zeichen gelesen wurde
}


int decodeline(char line[], int lineLength){
    int motorNumber;
    char controllChar;
    int pwmValue;
    int offsetPwmValue=0;
    int delay=0;
    char *pNext;
    char* stringToken;

    char charMotorNumber[lineLength];
    char charPwmValue[lineLength];
    char charDelay[lineLength];

    if(line[0] == '#'){
        controllChar = line[2];

        stringToken= strtok(line, "#+-=;\n");
        strcpy(charMotorNumber, stringToken);
        motorNumber = charMotorNumber[0] - '0';

        stringToken = strtok (NULL, "#+-=;\n");
        strcpy(charPwmValue, stringToken);
        pwmValue = strtol(charPwmValue , &pNext, 10);

        stringToken = strtok (NULL, "#+-=;\n");
        strcpy(charDelay, stringToken);
        delay = strtol(charDelay , &pNext, 10);

        printf("pwmValue : %i", pwmValue);

        switch(motorNumber){
            case 0:
                pwmValue = calcPwmValue(controllChar , motorNumber, pwmValue);
                SetPwmMotor(DEFMotorNo1_PWM, pwmValue, 0);
                break;
            case 1:
                pwmValue = calcPwmValue(controllChar , motorNumber, pwmValue);
                SetPwmMotor(DEFMotorNo2_PWM, pwmValue, 0);
                break;
            case 2:
                pwmValue = calcPwmValue(controllChar , motorNumber, pwmValue);
                SetPwmMotor(DEFMotorNo3_PWM, pwmValue, 0);
                break;
            case 3:
                pwmValue = calcPwmValue(controllChar , motorNumber, pwmValue);
                SetPwmMotor(DEFMotorNo4_PWM, pwmValue, 0);
                break;
            case 4:
                pwmValue = calcPwmValue(controllChar , motorNumber, pwmValue);
                SetPwmMotor(DEFMotorNo5_PWM, pwmValue, 0);
                break;
            case 5:
                pwmValue = calcPwmValue(controllChar , motorNumber, pwmValue);
                SetPwmMotor(DEFMotorNo6_PWM, pwmValue, 0);
                break;
            case 6:
                pwmValue = calcPwmValue(controllChar , motorNumber, pwmValue);
                SetPwmMotor(DEFMotorNo7_PWM, pwmValue, 0);
                break;
            case 7:
                pwmValue = calcPwmValue(controllChar , motorNumber, pwmValue);
                SetPwmMotor(DEFMotorNo8_PWM, pwmValue, 0);
                break;
            case 12: // CW'>'
                if(controllChar == '='){
                    SetPwmMotor(DEFMotorCW_PWM, pwmValue, 0);
                }else{

                    offsetPwmValue = calcPwmValue( controllChar , 0, pwmValue);
                    SetPwmMotor(DEFMotorNo1_PWM, offsetPwmValue, 0);
                    offsetPwmValue = calcPwmValue( controllChar , 2, pwmValue);
                    SetPwmMotor(DEFMotorNo3_PWM, offsetPwmValue, 0);
                    #if Okto_Plus
                        offsetPwmValue = calcPwmValue( controllChar , 4, pwmValue);
                        SetPwmMotor(DEFMotorNo5_PWM, offsetPwmValue, 0);
                        offsetPwmValue = calcPwmValue( controllChar , 6, pwmValue);
                        SetPwmMotor(DEFMotorNo7_PWM, offsetPwmValue, 0);
                    #endif
                }
                break;
            case 14: // '<' CCW
                if(controllChar == '='){
                    SetPwmMotor(DEFMotorCCW_PWM, pwmValue, 0);
                }else{
                    offsetPwmValue = calcPwmValue( controllChar , 1, pwmValue);
                    SetPwmMotor(DEFMotorNo2_PWM, offsetPwmValue, 0);
                    offsetPwmValue = calcPwmValue( controllChar , 3, pwmValue);
                    SetPwmMotor(DEFMotorNo4_PWM, offsetPwmValue, 0);
                    #if Okto_Plus
                        offsetPwmValue = calcPwmValue( controllChar , 5, pwmValue);
                        SetPwmMotor(DEFMotorNo6_PWM, offsetPwmValue, 0);
                        offsetPwmValue = calcPwmValue( controllChar , 7, pwmValue);
                        SetPwmMotor(DEFMotorNo8_PWM, offsetPwmValue, 0);
                    #endif
                }
                break;
            default:
                break;
        }//switch
        printf("motorNumber : %i", motorNumber);
    }//if
    return delay;
}


int calcPwmValue(char controllChar , int motorNumber, int pwmValue){
    switch(controllChar){
                case '+':
                    pwmValue = GetPwmMotor(motorNumber)+pwmValue;
                    break;
                case '-':
                    pwmValue = GetPwmMotor(motorNumber)-pwmValue;
                    break;
                case '=':
                    break;
                default:
                    break;
        }
    return pwmValue;
}
