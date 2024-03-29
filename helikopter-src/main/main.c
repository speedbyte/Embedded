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

#include "udpSensorLib.h"
#include "matrixLib.h"
#include "HAL_ADC.h"
#include "batteryCheck.h"
#include "Orientation.h"
#include "GPS.h"
#include "imu.h"
#include "barometer.h"
#include "LIDAR.h"
#include "LLD_UART.h"
#include "LLD_I2C.h"
#include "MOTOR.h"

extern float g_halADC_get_ui16(unsigned char);

int readTestcaseFile(char testcase[] , int length);
int kbhit(void);
int calcPwmValue(char controllChar , int motorNumber, int pwmValue);

#define REMOTE_PORT 5000
#define REMOTE_ADDR "192.168.178.46"

typedef enum enumTestCases {
    TESTADC = 1,
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
    TESTSINGLESENSOR,
    SEND_ALL_PAYLOAD,
    SEND_ALL_PAYLOAD_INTERACTIVE,
    RECEIVE,
    TESTEND
} enumTestcases;

static char str[500];
static char str2[500];

//necessary variables for sending via UDP
struct sockaddr_in remoteaddress;
char sendAddrString[20];
socklen_t addressSize;

struct sockaddr_in sendAddr;
struct sockaddr_in recvAdr;

//UDP Socket

//Necessary characters for sending SensorData
int accx, accy, accz, magx, magy, magz, gy, gp, gr, temp, press, clocks,
        clockms, m1, m2, m3, m4;
char imu_x[16];
char imu_y[16];
char imu_z[16];
char mag_x[16];
char mag_y[16];
char mag_z[16];
char g_y[16];
char g_p[16];
char g_r[16];
char tmp[16];
char prs[16];
char tis[15];
char tims[15];
char Motor1[16];
char Motor2[16];
char Motor3[16];
char Motor4[16];
char buffer[270];

//////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    while (1) {
        enumTestcases runCommand = 0;
        int testValueLength = 20;
        char testValue[testValueLength];

        //Socket to Send Data
        int send = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

        sprintf(sendAddrString, REMOTE_ADDR);
        memset(sendAddr.sin_zero, '\0', sizeof(sendAddr.sin_zero));
        sendAddr.sin_family = PF_INET;
        sendAddr.sin_port = htons(REMOTE_PORT);
        sendAddr.sin_addr.s_addr = inet_addr(REMOTE_ADDR);

        //Socket to receive Data
        int receive = socket(PF_INET, SOCK_DGRAM, 0);
        recvAdr.sin_family = PF_INET;
        recvAdr.sin_port = htons(4999);
        recvAdr.sin_addr.s_addr = htonl(INADDR_ANY);
        bind(receive, (struct sockaddr*) &recvAdr, sizeof(recvAdr));

        //////////////////////////////////////////////////////////////////////////////

        if (argc == 2) {
            sprintf(sendAddrString, argv[1]);
            printf("%s %d", sendAddrString, strlen(sendAddrString));
            //puts(argv[0]);
        }

        memset(remoteaddress.sin_zero, '\0', sizeof(remoteaddress.sin_zero));
        remoteaddress.sin_family = PF_INET;
        remoteaddress.sin_port = htons(REMOTE_PORT);
        (void) inet_aton(sendAddrString, &remoteaddress.sin_addr); //dot to integer and then host to network byte order
        send = socket(PF_INET, SOCK_DGRAM, 0);
        /*Initialize size variable to be used later on*/
        addressSize = sizeof(remoteaddress);

        scanf("%s", testValue);

        //        do{
        //            sleep(2);
        //            isSelected = readTestcaseFile(&testValue[0] ,testValueLength);
        //        }while (isSelected != 1);

        printf("Received string is %s\n", testValue);
        if (strcmp(testValue, "testadc") == 0)
            runCommand = TESTADC;
        else if (strcmp(testValue, "testbattery") == 0)
            runCommand = TESTBATTERY;
        else if (strcmp(testValue, "testgps") == 0)
            runCommand = TESTGPS;
        else if (strcmp(testValue, "testimu") == 0)
            runCommand = TESTIMU;
        else if (strcmp(testValue, "testlaser") == 0)
            runCommand = TESTLASER;
        else if (strcmp(testValue, "testuart") == 0)
            runCommand = TESTUART;
        else if (strcmp(testValue, "testmatlabimu") == 0)
            runCommand = TESTMATLABIMU;
        else if (strcmp(testValue, "testmatlabkalman") == 0)
            runCommand = TESTMATLABKALMAN;
        else if (strcmp(testValue, "testaccmag") == 0)
            runCommand = TESTACCMAG;
        else if (strcmp(testValue, "testgyro") == 0)
            runCommand = TESTGYRO;
        else if (strcmp(testValue, "testbaro") == 0)
            runCommand = TESTBARO;
        else if (strcmp(testValue, "testmatrixlib") == 0)
            runCommand = TESTMATRIXLIB;
        else if (strcmp(testValue, "testudp") == 0)
            runCommand = TESTUDP;
        else if (strcmp(testValue, "testudptransfer") == 0)
            runCommand = TESTUDPTRANSFER;
        else if (strcmp(testValue, "testallangles") == 0)
            runCommand = ALLANGLES;
        else if (strcmp(testValue, "testallsensordata") == 0)
            runCommand = TESTALLSENSORDATA;
        else if (strcmp(testValue, "testmotorpwm") == 0)
            runCommand = TESTMOTORPWM;
        else if (strcmp(testValue, "testmotorisr") == 0)
            runCommand = TESTMOTORISR;
        else if (strcmp(testValue, "testmotortxt") == 0)
            runCommand = TESTMOTORTXT;
        else if (strcmp(testValue, "testgui") == 0)
            runCommand = TESTGUI;
        else if (strcmp(testValue, "testsinglesensor") == 0)
            runCommand = TESTSINGLESENSOR;
        else if (strcmp(testValue, "send_all_payload") == 0)
            runCommand = SEND_ALL_PAYLOAD;
        else if (strcmp(testValue, "send_all_payload_interactive") == 0)
            runCommand = SEND_ALL_PAYLOAD_INTERACTIVE;
        else if (strcmp(testValue, "receive") == 0)
            runCommand = RECEIVE;

        switch (runCommand) {
        case TESTADC: {
            float erg;
            printf("Starting ADC Test\n");
            erg = g_halADC_get_ui16(1);
            if (erg < 0) {
                printf("Fehler");
                return 1;
            } else {
                printf("Ergebniss: %f\n", erg);
            }
            break;
        }
        case TESTBATTERY: {
            double l_batterLevel_f64 = 0;
            printf("Starting Battery Test\n");
            int i = kbhit();
            while (i != 'q') {
                g_halBatCheck_readBatStatusFromI2C_bool();
                l_batterLevel_f64 = g_halBatCheck_getBatteryStatus_f64();
                printf("Measured Voltage: %5.3f\n", l_batterLevel_f64);
                sleep(1);
            }
            break;
        }
        case TESTGPS: {
            struct strPosition main_longitude;
            struct strPosition main_latitude;
            printf("Starting GPS Test\n");
            int i = kbhit();
            while (i != 'q') {
                g_halGps_getData_i32();
            }
            break;
        }
        case TESTIMU: {
            HAL_SENSOR_PAYLOAD_ST l_imuMeasurements_st;
            printf("Starting IMU Test\n");
            g_halImu_initImuSensors_bool();
            int i = kbhit();
            while (i != 'q') {
                g_halImu_triggerImuReading_bool();
                g_halImu_triggerBaroReading_bool();
                g_halImu_triggerGyroReading_bool();
                g_halImu_triggerAccReading_bool();

                l_imuMeasurements_st = g_halImu_getsensorValues_str();

                printf("Pressure: %5.3f    ;    Temperature:  %5.3f\n",
                        l_imuMeasurements_st.pressure_f64,
                        l_imuMeasurements_st.temperature_f64);
                printf(
                        "roll: %5.3f    ;    pitch:  %5.3f    ;    yaw:  %5.3f\n",
                        l_imuMeasurements_st.gyro.roll_f64,
                        l_imuMeasurements_st.gyro.pitch_f64,
                        l_imuMeasurements_st.gyro.yaw_f64);
                printf("X: %5.3f ; Y:  %5.3f ; Z:  %5.3f\n",
                        l_imuMeasurements_st.acc.x_f64,
                        l_imuMeasurements_st.acc.y_f64,
                        l_imuMeasurements_st.acc.z_f64);
                printf("X: %5.10f ; Y:  %5.10f ; Z:  %5.10f\n\n\n\n",
                        l_imuMeasurements_st.mag.x_f64,
                        l_imuMeasurements_st.mag.y_f64,
                        l_imuMeasurements_st.mag.z_f64);
            }
            break;
        }
        case TESTLASER: {
            double dist = 0;
            printf("Starting LASER Test\n");
            int i = kbhit();
            while (i != 'q') {
                g_LIDAR_readDistanceFromI2C_i32();
                //usleep(100000);

                dist = g_LIDAR_getDistance_f64();

                printf("Distance: %4.2f m\n", dist);
                usleep(500 * 1000);
            }
            break;
        }
        case TESTUART: {
            char rec_char = 'z';
            char *ptr_rec_char = &rec_char;
            printf("Starting UART Test\n");
            FILE *fp = (FILE *) -1;
            //open file to write received data from GPS
            fp = (FILE *) open("GPS_logging.txt", 100 | 01, 400);
            sleep(1);
            int i = kbhit();
            while (i != 'q') {
                rec_char = g_lldUart_readByte_ch();
                //save read values if filestream is opened
                if (fp != (FILE *) -1) {
                    write((int) fp, ptr_rec_char, 1);
                }
            }
            fclose(fp);
            break;
        }
        case TESTMATLABIMU: {
            printf("Starting IMU Matlab Test\n");
            unsigned char l_remoteHostAddr_rg4ui8[4] = { 192, 168, 22, 160 };
            unsigned short l_remoteHostPort_ui16 = 5000;
            int l_udpSocket_i32;
            unsigned int l_sendState_bool;

            // open udp connection
            l_udpSocket_i32 = g_udp_initConnection_i32(
                    l_remoteHostAddr_rg4ui8, l_remoteHostPort_ui16);

            HAL_SENSOR_PAYLOAD_ST l_imuMeasurements_st;
            g_halImu_initImuSensors_bool();

            int i = kbhit();
            while (i != 'q') {
                g_halImu_triggerImuReading_bool();
                g_halImu_triggerBaroReading_bool();
                g_halImu_triggerGyroReading_bool();
                g_halImu_triggerAccReading_bool();

                l_imuMeasurements_st = g_halImu_getsensorValues_str();

                l_sendState_bool = g_hal_send_sensor_raw_bool(l_udpSocket_i32,
                        l_imuMeasurements_st);
                printf("Temp %f\n", l_imuMeasurements_st.temperature_f64);
                if (l_sendState_bool != M_HAL_MATLAB_SUCCESS_UI8) {
                    printf("UDP-Packet error\n");
                }
                usleep(20000); //20ms = 50Hz
            }
            // close udp connection
            g_udp_closeSocket_bool(l_udpSocket_i32);
            break;
        }
        case TESTMATLABKALMAN: {
            printf("Starting Kalman Orientation Matlab Test\n");
            unsigned char l_remoteHostAddr_rg4ui8[4] = { 192, 168, 22, 160 };
            unsigned short l_remoteHostPort_ui16 = 5000;
            int l_udpSocket_i32;
            unsigned int l_sendState_bool;

            HAL_ANGLE_PAYLOAD_ST l_kalmanAngles_st;
            HAL_ANGLE_PAYLOAD_ST l_compAngles_st;
            HAL_SENSOR_PAYLOAD_ST l_sensorValues_st;

            // open udp connection
            l_udpSocket_i32 = g_udp_initConnection_i32(
                    l_remoteHostAddr_rg4ui8, l_remoteHostPort_ui16);

            g_initMatrices_bool();
            g_initImuSensors_bool();

            int i = kbhit();
            while (i != 'q') {
                g_calcKalmanOrientation_bool();
                g_calcComplementaryOrientation_bool();

                l_kalmanAngles_st = g_getAnglesKalman_bool();
                l_compAngles_st = g_getAnglesComplementary_bool();
                l_sensorValues_st = g_halImu_getsensorValues_str();

                printf("Temp%f\nMag%f", l_sensorValues_st.temperature_f64,
                        l_sensorValues_st.mag.x_f64);
                l_sendState_bool = g_hal_send_all_angles_calculated_bool(
                        l_udpSocket_i32, l_sensorValues_st, l_kalmanAngles_st,
                        l_compAngles_st);
                if (l_sendState_bool != M_HAL_MATLAB_SUCCESS_UI8) {
                    printf("UDP-Packet error\n");
                } else {
                    printf("Sent packet\n");
                }
                usleep(20000); //20ms = 50Hz
            }
            // close udp connection
            g_udp_closeSocket_bool(l_udpSocket_i32);
            break;
        }
        case TESTACCMAG: {
            halAccmag_dataContainer l_sensorData_st;
            printf("IMU Acceleration and Compass Test\n");
            if (g_halAccmag_initSensor_bool() != M_HAL_ACCMAG_SUCCESS_BOOL) {
                printf("Init failed!\n");
                return 1;
            }
            int i = kbhit();
            while (i != 'q') {
                if (g_halAccmag_triggerAccUpdate_bool() != M_HAL_ACCMAG_SUCCESS_BOOL) {
                    printf("ACC update failed!\n");
                    return 1;
                }
                if (g_halAccmag_triggerMagUpdate_bool() != M_HAL_ACCMAG_SUCCESS_BOOL) {
                    printf("MAG update failed!\n");
                    return 1;
                }
                l_sensorData_st = g_halAccmag_getAccMagContainer_st();
                printf(
                        "Acc - x:%f y:%lf z:%f | Mag - x:%.10f y:%.10f z:%.10f\n",
                        l_sensorData_st.acc.x_f64, l_sensorData_st.acc.y_f64,
                        l_sensorData_st.acc.z_f64, l_sensorData_st.mag.x_f64,
                        l_sensorData_st.mag.y_f64, l_sensorData_st.mag.z_f64);
                usleep(250000);
            }
            break;
        }
        case TESTBARO: {
            double pressure = 0;
            double temp = 0;
            HAL_ANGLE_PAYLOAD_ST GyroValues;
            double Gyrotemp = 0;
            g_halBaro_initBaro_i32();
            g_halGyro_initGyro_i32();
            printf("IMU Barometer pressure test");
            int i = kbhit();
            while (i != 'q') {
                g_halBaro_readPressureFromI2C_i32();
                usleep(100000);
                g_halBaro_readTemperatureFromI2C_i32();
                usleep(100000);
                pressure = g_halBaro_getPressure_f64();
                temp = g_halBaro_getTemperature_f64();
                printf("Pressure: %5.3f    ;    Temperature:  %5.3f\n",
                        pressure, temp);
                usleep(100000);
                g_halGyro_I2C_readRawValue_i32();
                usleep(100000);
                g_halGyro_readTemperatureFromI2C_i32();
                usleep(100000);
                GyroValues = g_halGyro_getGyroscope_st();
                Gyrotemp = g_halGyro_getTemperature_f64();
                printf(
                        "roll: %5.3f    ;    pitch:  %5.3f    ;    yaw:  %5.3f\n",
                        GyroValues.roll_f64, GyroValues.pitch_f64,
                        GyroValues.yaw_f64);
                usleep(100000);
            }
            break;
        }
        case TESTGYRO: {
            double pressure = 0;
            double temp = 0;
            HAL_ANGLE_PAYLOAD_ST GyroValues;
            double Gyrotemp = 0;
            printf("IMU Gyroscope test\n");
            g_halBaro_initBaro_i32();
            g_halGyro_initGyro_i32();
            int i = kbhit();
            while (i != 'q') {
                g_halBaro_readPressureFromI2C_i32();
                //usleep(100000);
                g_halBaro_readTemperatureFromI2C_i32();
                //usleep(100000);
                pressure = g_halBaro_getPressure_f64();
                temp = g_halBaro_getTemperature_f64();
                printf("Pressure: %5.3f    ;    Temperature:  %5.3f\n",
                        pressure, temp);
                //usleep(100000);
                g_halGyro_I2C_readRawValue_i32();
                //usleep(100000);
                g_halGyro_readTemperatureFromI2C_i32();
                //usleep(100000);
                GyroValues = g_halGyro_getGyroscope_st();
                Gyrotemp = g_halGyro_getTemperature_f64();
                printf(
                        "roll: %5.3f    ;    pitch:  %5.3f    ;    yaw:  %5.3f\n",
                        GyroValues.roll_f64, GyroValues.pitch_f64,
                        GyroValues.yaw_f64);
                //usleep(100000);
            }
            break;
        }
        case TESTMATRIXLIB: {
            static double l_MatrixA_f64[3][3] = { { 1, 2, 1 }, { 2, 5, 4 }, { 1,
                    4, 9 } };
            //static    double l_MatrixA_f64[3][3]={{4,-14,-2},{-14,65,3},{-2,3,3}};
            //static    double l_MatrixA_f64[2][3]={{1,2,9},{2,5,9}};
            //static    double l_MatrixA_f64[1][3]={{1,2,9}};
            static double l_MatrixB_f64[3][3] = { { 3, 6, 7 }, { 2, 5, 9 }, { 4,
                    6, 8 } };
            //static    double l_MatrixB_f64[3][2]={{3,6},{2,5},{4,6}};
            static double l_outputMatrix_f64[3][3] = { { 0, 0, 0 }, { 0, 0, 0 },
                    { 0, 0, 0 } };
            //static    double l_outputMatrix_f64[3][2]={{0,0},{0,0},{0,0}};
            printf("matrix lib function test\n");
            int i = kbhit();
            while (i != 'q') {
                g_sigMath_matrixEye_bool((double*) l_outputMatrix_f64, 3, 3);
                sleep(1);
                g_sigMath_matrixInitialize_bool((double*) l_outputMatrix_f64, 3,
                        3, 1);
                sleep(1);
                g_sigMath_matrixMultiplikation_bool((double*) l_outputMatrix_f64,
                        (double*) l_MatrixA_f64, 3, 3, (double*) l_MatrixB_f64,
                        3, 3);
                sleep(1);
                g_sigMath_matrixAddition_bool((double*) l_outputMatrix_f64,
                        (double*) l_MatrixA_f64, 3, 3, (double*) l_MatrixB_f64,
                        3, 3);
                sleep(1);
                g_sigMath_matrixSubtraktion_bool((double*) l_outputMatrix_f64,
                        (double*) l_MatrixA_f64, 3, 3, (double*) l_MatrixB_f64,
                        3, 3);
                sleep(1);
                g_sigMath_matrixAssignment_bool((double*) l_outputMatrix_f64, 3,
                        3, (double*) l_MatrixA_f64, 3, 3);
                sleep(1);
                g_sigMath_matrixTransponiert_bool((double*) l_outputMatrix_f64,
                        (double*) l_MatrixA_f64, 3, 3);
                sleep(1);
                g_sigMath_matrixInverse_bool((double*) l_outputMatrix_f64,
                        (double*) l_MatrixA_f64, 3, 3);
                sleep(1);
            }
            break;
        }
        case TESTUDP: {
            printf("simple send udp test...");
            char message[20] = "Hello\n";

            printf("Start Sending Messages\n");

            int i = kbhit();
            while (i != 'q') {
                sleep(1);
                /* Send N bytes of BUF on socket FD to peer at address ADDR (which is
                 ADDR_LEN bytes long).  Returns the number sent, or -1 for errors.

                 This function is a cancellation point and therefore not marked with
                 __THROW.  */
                sendto(send, message, sizeof(message), 0,
                        (struct sockaddr *) &sendAddr, addressSize);
                printf("And send again....\n");
            }
            break;
        }
        case TESTUDPTRANSFER: {
            HAL_ANGLE_PAYLOAD_ST l_kalmanAngles_st;
            HAL_ANGLE_PAYLOAD_ST l_compAngles_st;

            HAL_SENSOR_PAYLOAD_ST l_sensorValues_st;
            HAL_RT_SENSOR_PAYLOAD_FUSION_ST l_rtCompleteSigPayload_st;

            struct timespec l_timestamp_st;

            printf("Starting Transfer matlab data on udp test\n");

            g_initMatrices_bool();
            g_initImuSensors_bool();

            int i = kbhit();
            while (i != 'q') {
                g_calcKalmanOrientation_bool();
                g_calcComplementaryOrientation_bool();

                l_kalmanAngles_st = g_getAnglesKalman_bool();
                l_compAngles_st = g_getAnglesComplementary_bool();
                l_sensorValues_st = g_halImu_getsensorValues_str();

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
                if (clock_gettime(CLOCK_REALTIME,
                        &l_timestamp_st) != M_HAL_MATLAB_SUCCESS_UI8) {
                    return M_HAL_MATLAB_FAILED_UI8;
                }

                clock_gettime(CLOCK_REALTIME, &l_timestamp_st);

                //assmeble timestamp and
                l_rtCompleteSigPayload_st.timestamp_st = l_timestamp_st;
                l_rtCompleteSigPayload_st.sensorValues_st = l_sensorValues_st;
                l_rtCompleteSigPayload_st.kalmanSigState_st = l_kalmanAngles_st;
                l_rtCompleteSigPayload_st.complementarySigState_st =
                        l_compAngles_st;

                printf("START MEASUREMENT\n");
                sprintf(str, "sec =  %d, nano = %d",
                        l_rtCompleteSigPayload_st.timestamp_st.tv_sec,
                        l_rtCompleteSigPayload_st.timestamp_st.tv_nsec);
                puts(str);
                sprintf(str, "acc = %f %f %f",
                        l_rtCompleteSigPayload_st.sensorValues_st.acc.x_f64,
                        l_rtCompleteSigPayload_st.sensorValues_st.acc.y_f64,
                        l_rtCompleteSigPayload_st.sensorValues_st.acc.z_f64);
                puts(str);
                sprintf(str, "mag = %f %f %f",
                        l_rtCompleteSigPayload_st.sensorValues_st.mag.x_f64,
                        l_rtCompleteSigPayload_st.sensorValues_st.mag.y_f64,
                        l_rtCompleteSigPayload_st.sensorValues_st.mag.z_f64);
                puts(str);
                sprintf(str, "roll %f, pitch %f yaw  %f",
                        l_rtCompleteSigPayload_st.sensorValues_st.gyro.roll_f64,
                        l_rtCompleteSigPayload_st.sensorValues_st.gyro.pitch_f64,
                        l_rtCompleteSigPayload_st.sensorValues_st.gyro.yaw_f64);
                puts(str);
                sprintf(str, "temperature = %f",
                        l_rtCompleteSigPayload_st.sensorValues_st.temperature_f64);
                puts(str);
                sprintf(str, "pressure = %f",
                        l_rtCompleteSigPayload_st.sensorValues_st.pressure_f64);
                puts(str);
                sprintf(str, "KALMAN yaw %f, pitch %f roll %f",
                        l_rtCompleteSigPayload_st.kalmanSigState_st.yaw_f64,
                        l_rtCompleteSigPayload_st.kalmanSigState_st.pitch_f64,
                        l_rtCompleteSigPayload_st.kalmanSigState_st.roll_f64);
                puts(str);
                sprintf(str, "COMPLEMENTARY yaw %f, pitch %f roll %f",
                        l_rtCompleteSigPayload_st.complementarySigState_st.yaw_f64,
                        l_rtCompleteSigPayload_st.complementarySigState_st.pitch_f64,
                        l_rtCompleteSigPayload_st.complementarySigState_st.roll_f64);
                puts(str);

                //printf("Sending time %d and Temperature %f\n", l_rtCompleteSigPayload_st.timestamp_st.tv_sec, l_rtCompleteSigPayload_st.sensorValues_st.temperature_f64);
                sendto(send, (unsigned char *) &l_rtCompleteSigPayload_st,
                        (size_t) sizeof(l_rtCompleteSigPayload_st), 0,
                        (struct sockaddr *) &remoteaddress,
                        sizeof(remoteaddress));
                usleep(50000); //20ms = 50Hz
            }
            // close udp connection
            close(send);
            break;
        }
        case ALLANGLES: {
            HAL_ANGLE_PAYLOAD_ST l_GyroPerStepAngles_st;
            HAL_ANGLE_PAYLOAD_ST l_AccMagAngles_st;
            HAL_ANGLE_PAYLOAD_ST l_kalmanAngles_st;
            HAL_ANGLE_PAYLOAD_ST l_compAngles_st;
            HAL_SENSOR_PAYLOAD_ST l_sensorValues_st;

            HAL_RT_ANGLE_CALCULATED_ST l_rtRollPitchYawSigPayload_st;

            struct timespec l_timestamp_st;

            printf("Starting Transfer matlab data on all angles\n");

            int val = 0;

            g_initMatrices_bool();
            g_initImuSensors_bool();

            int i = kbhit();
            while (i != 'q') {
                g_calcKalmanOrientation_bool();
                g_calcComplementaryOrientation_bool();

                l_sensorValues_st = g_halImu_getsensorValues_str();
                l_GyroPerStepAngles_st = g_getAnglesGyroPerStep_bool();
                l_AccMagAngles_st = g_getAnglesAccMagCalc_bool();
                l_kalmanAngles_st = g_getAnglesKalman_bool();
                l_compAngles_st = g_getAnglesComplementary_bool();

                if (clock_gettime(CLOCK_REALTIME,
                        &l_timestamp_st) != M_HAL_MATLAB_SUCCESS_UI8) {
                    return M_HAL_MATLAB_FAILED_UI8;
                }

                clock_gettime(CLOCK_REALTIME, &l_timestamp_st);

                //assmeble timestamp and
                l_rtRollPitchYawSigPayload_st.timestamp_st = l_timestamp_st;
                l_rtRollPitchYawSigPayload_st.angularVelocityGyroFromImu_st =
                        l_sensorValues_st.gyro;
                l_rtRollPitchYawSigPayload_st.angleFromGyroStepCalculation_st =
                        l_GyroPerStepAngles_st;
                l_rtRollPitchYawSigPayload_st.angleFromAccMagCalculation_st =
                        l_AccMagAngles_st;
                l_rtRollPitchYawSigPayload_st.angleFromkalmanSigState_st =
                        l_kalmanAngles_st;
                l_rtRollPitchYawSigPayload_st.angleFromcomplementarySigState_st =
                        l_compAngles_st;

                printf("START MEASUREMENT\n");
                sprintf(str, "sec =  %d, nano = %d",
                        l_rtRollPitchYawSigPayload_st.timestamp_st.tv_sec,
                        l_rtRollPitchYawSigPayload_st.timestamp_st.tv_nsec);
                puts(str);
                sprintf(str,
                        "Raw GYro Angular velocity roll %f, pitch %f yaw  %f",
                        l_rtRollPitchYawSigPayload_st.angularVelocityGyroFromImu_st.roll_f64,
                        l_rtRollPitchYawSigPayload_st.angularVelocityGyroFromImu_st.pitch_f64,
                        l_rtRollPitchYawSigPayload_st.angularVelocityGyroFromImu_st.yaw_f64);
                puts(str);
                sprintf(str, "Gyro Angles roll %f, pitch %f yaw  %f",
                        l_rtRollPitchYawSigPayload_st.angleFromGyroStepCalculation_st.roll_f64,
                        l_rtRollPitchYawSigPayload_st.angleFromGyroStepCalculation_st.pitch_f64,
                        l_rtRollPitchYawSigPayload_st.angleFromGyroStepCalculation_st.yaw_f64);
                puts(str);
                sprintf(str, "ACC MAG CALC Angles roll %f, pitch %f yaw  %f",
                        l_rtRollPitchYawSigPayload_st.angleFromAccMagCalculation_st.roll_f64,
                        l_rtRollPitchYawSigPayload_st.angleFromAccMagCalculation_st.pitch_f64,
                        l_rtRollPitchYawSigPayload_st.angleFromAccMagCalculation_st.yaw_f64);
                puts(str);
                sprintf(str, "COMPLEMENTARY Angles roll %f, pitch %f yaw %f",
                        l_rtRollPitchYawSigPayload_st.angleFromcomplementarySigState_st.roll_f64,
                        l_rtRollPitchYawSigPayload_st.angleFromcomplementarySigState_st.pitch_f64,
                        l_rtRollPitchYawSigPayload_st.angleFromcomplementarySigState_st.yaw_f64);
                puts(str);
                sprintf(str, "KALMAN Angles roll %f, pitch %f yaw %f",
                        l_rtRollPitchYawSigPayload_st.angleFromkalmanSigState_st.roll_f64,
                        l_rtRollPitchYawSigPayload_st.angleFromkalmanSigState_st.pitch_f64,
                        l_rtRollPitchYawSigPayload_st.angleFromkalmanSigState_st.yaw_f64);
                puts(str);

                sendto(send, (unsigned char *) &l_rtRollPitchYawSigPayload_st,
                        (size_t) sizeof(l_rtRollPitchYawSigPayload_st), 0,
                        (struct sockaddr *) &remoteaddress,
                        sizeof(remoteaddress));

                usleep(50000); //20ms = 50Hz
            }
            // close udp connection
            close(send);
            break;
        }

        case TESTALLSENSORDATA: {
            printf("Starting IMU send all Sensor Values\n");
            unsigned char l_remoteHostAddr_rg4ui8[4] = { 192, 168, 22, 160 };
            unsigned short l_remoteHostPort_ui16 = 5000;
            int l_udpSocket_i32;
            unsigned int l_sendState_bool;

            // open udp connection
            l_udpSocket_i32 = g_udp_initConnection_i32(
                    l_remoteHostAddr_rg4ui8, l_remoteHostPort_ui16);

            HAL_SENSOR_PAYLOAD_ST l_imuMeasurements_st;
            g_halImu_initImuSensors_bool();

            int i = kbhit();
            while (i != 'q') {
                g_halImu_triggerImuReading_bool();
                g_halImu_triggerBaroReading_bool();
                g_halImu_triggerGyroReading_bool();
                g_halImu_triggerAccReading_bool();

                l_imuMeasurements_st = g_halImu_getsensorValues_str();

                l_sendState_bool = g_hal_send_sensor_raw_bool(l_udpSocket_i32,
                        l_imuMeasurements_st);

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

                if (l_sendState_bool != M_HAL_MATLAB_SUCCESS_UI8) {
                    printf("UDP-Packet error\n");
                }
                usleep(20000); //20ms = 50Hz
            }
            // close udp connection
            g_udp_closeSocket_bool(l_udpSocket_i32);
            break;
        }

            /*!**********************************************************************
             * \author  Marcel Früh
             * \date    2016/06/5
             *
             *
             * \details Sends Sensor Data to above specificated IP Adress and PORT
             *          1s Sleep after every round
             *
             *
             ***********************************************************************/
        case SEND_ALL_PAYLOAD: {

            //Preparation for Sensor Calls
            HAL_SENSOR_PAYLOAD_ST l_imuMeasurements_st;
            g_halImu_initImuSensors_bool();

            printf("Start Sending \n");

            //Sensor Data
            while (1) {

                g_halImu_triggerImuReading_bool();
                g_halImu_triggerBaroReading_bool();
                g_halImu_triggerGyroReading_bool();
                g_halImu_triggerAccReading_bool();

                //Get Sensor Data and Timestamp

                l_imuMeasurements_st = g_halImu_getsensorValues_str();

                long ms; // Milliseconds
                struct timespec spec;
                time_t res;
                res = time(NULL);
                clock_gettime(CLOCK_REALTIME, &spec);
                ms = round(spec.tv_nsec / 1.0e6); // nano -> mili

                //Call SensorData an save them in floats

                float ax = l_imuMeasurements_st.acc.x_f64;
                float ay = l_imuMeasurements_st.acc.y_f64;
                float az = l_imuMeasurements_st.acc.z_f64;

                float mx = l_imuMeasurements_st.mag.x_f64;
                float my = l_imuMeasurements_st.mag.y_f64;
                float mz = l_imuMeasurements_st.mag.z_f64;

                float y = l_imuMeasurements_st.gyro.yaw_f64;
                float p = l_imuMeasurements_st.gyro.pitch_f64;
                float r = l_imuMeasurements_st.gyro.roll_f64;

                float t = l_imuMeasurements_st.temperature_f64;
                float pr = l_imuMeasurements_st.pressure_f64;

                //No Motor running : ZERO
                int mot1 = 0;
                int mot2 = 0;
                int mot3 = 0;
                int mot4 = 0;

                clocks = sprintf(tis, "TimS%u\n", res);
                clockms = sprintf(tims, "TimM%u\n", ms);
                int sizeC = clocks + clockms;
                accx = sprintf(imu_x, "AccX%f\n", ax);
                int sizeAccX = sizeC + accx;
                accy = sprintf(imu_y, "AccY%f\n", ay);
                int sizeAccY = sizeAccX + accy;
                accz = sprintf(imu_z, "AccZ%f\n", az);
                int sizeAccZ = sizeAccY + accz;

                magx = sprintf(mag_x, "MagX%f\n", mx);
                int sizemagX = sizeAccZ + magx;

                magy = sprintf(mag_y, "MagY%f\n", my);
                int sizemagY = sizemagX + magy;

                magz = sprintf(mag_z, "MagZ%f\n", mz);
                int sizemagZ = sizemagY + magz;

                gy = sprintf(g_y, "GyrY%f\n", y);
                int sizeGy = sizemagZ + gy;
                gp = sprintf(g_p, "GyrP%f\n", p);
                int sizeGp = sizeGy + gp;

                gr = sprintf(g_r, "GyrR%f\n", r);
                int sizeGr = sizeGp + gr;

                temp = sprintf(tmp, "Temp%f\n", t);
                int sizeTemp = sizeGr + temp;
                press = sprintf(prs, "Pres%f\n", pr);
                int sizePress = sizeTemp + press;
                m1 = sprintf(Motor1, "Mot1%u\n", mot1);
                int sizeM1 = sizePress + m1;
                m2 = sprintf(Motor2, "Mot2%u\n", mot2);
                int sizeM2 = sizeM1 + m2;
                m3 = sprintf(Motor3, "Mot3%u\n", mot3);
                int sizeM3 = sizeM2 + m3;
                m4 = sprintf(Motor4, "Mot4%u\n", mot4);
                int sizeM4 = sizeM3 + m4;

                memcpy(buffer, tis, clocks);
                memcpy(buffer + clocks, tims, clockms);
                memcpy(buffer + sizeC, imu_x, accx);
                memcpy(buffer + sizeAccX, imu_y, accy);
                memcpy(buffer + sizeAccY, imu_z, accz);
                memcpy(buffer + sizeAccZ, mag_x, magx);
                memcpy(buffer + sizemagX, mag_y, magy);
                memcpy(buffer + sizemagY, mag_z, magz);
                memcpy(buffer + sizemagZ, g_y, gy);
                memcpy(buffer + sizeGy, g_p, gp);
                memcpy(buffer + sizeGp, g_r, gr);
                memcpy(buffer + sizeGr, tmp, temp);
                memcpy(buffer + sizeTemp, prs, press);
                memcpy(buffer + sizePress, Motor1, m1);
                memcpy(buffer + sizeM1, Motor2, m2);
                memcpy(buffer + sizeM2, Motor3, m3);
                memcpy(buffer + sizeM3, Motor4, m4);

                sendto(send, buffer, sizeof(buffer), 0,
                        (struct sockaddr *) &sendAddr, addressSize);

                printf(tis, '\n');
                printf(tims, '\n');
                printf(imu_x, '\n');
                printf(imu_x, '\n');
                printf(imu_z, '\n');
                printf(mag_x, '\n');
                printf(mag_y, '\n');
                printf(mag_z, '\n');
                printf(g_y, '\n');
                printf(g_p, '\n');
                printf(g_r, '\n');
                printf(tmp, '\n');
                printf(prs, '\n');
                printf(Motor1, '\n');
                printf(Motor2, '\n');
                printf(Motor3, '\n');
                printf(Motor4, '\n');

                sleep(1);
            }
        }
            break;

            /*!**********************************************************************
             * \author  Marcel Früh
             * \date    2016/07/13
             *
             *
             * \details Starts DEMO. Insert MAX PWM and(< 100) and stepsize.
             * PWM is increased by stepsize each roud
             *
             *
             ***********************************************************************/
        case SEND_ALL_PAYLOAD_INTERACTIVE: {

            //Trigger Sensors
            HAL_SENSOR_PAYLOAD_ST l_imuMeasurements_st;
            g_halImu_initImuSensors_bool();

            //Motor
            printf("Beschleunigungstest \n");

            char pwm[3];
            char step[3];

            char BLCtrlADRExecuteOrder[DEFMotorsCount];
            char sendBuffer[1];
            unsigned int pwmValue;
            int STEPSIZE;
            int MAXPWMVALUE = 0;

            printf("Eingabe maximaler PWM Wert, 2 Ziffern < 70 \n");
            scanf("%s", pwm);
            MAXPWMVALUE = atoi(pwm);
            printf("Eingabe Stepsize, 1 Ziffer, < 10\n");
            scanf("%s", step);
            STEPSIZE = atoi(step);

            GetBLCtrlADRExecuteOrder(&BLCtrlADRExecuteOrder[0]);

            while (1) {

                //First Sensor then Motor
                while (pwmValue < MAXPWMVALUE) {

                    sendBuffer[0] = pwmValue;

                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[0],
                            &sendBuffer[0], 1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[1],
                            &sendBuffer[0], 1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[2],
                            &sendBuffer[0], 1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[3],
                            &sendBuffer[0], 1);

                    //Preparation for Sensor Calls

                    g_halImu_triggerImuReading_bool();
                    g_halImu_triggerBaroReading_bool();
                    g_halImu_triggerGyroReading_bool();
                    g_halImu_triggerAccReading_bool();

                    //Get Sensor Data and Timestamp

                    l_imuMeasurements_st = g_halImu_getsensorValues_str();

                    long ms; // Milliseconds
                    struct timespec spec;
                    time_t res;
                    res = time(NULL);
                    clock_gettime(CLOCK_REALTIME, &spec);
                    ms = round(spec.tv_nsec / 1.0e6); // nano -> mili

                    //Call SensorData an save them in floats

                    float ax = l_imuMeasurements_st.acc.x_f64;
                    float ay = l_imuMeasurements_st.acc.y_f64;
                    float az = l_imuMeasurements_st.acc.z_f64;

                    float mx = l_imuMeasurements_st.mag.x_f64;
                    float my = l_imuMeasurements_st.mag.y_f64;
                    float mz = l_imuMeasurements_st.mag.z_f64;

                    float y = l_imuMeasurements_st.gyro.yaw_f64;
                    float p = l_imuMeasurements_st.gyro.pitch_f64;
                    float r = l_imuMeasurements_st.gyro.roll_f64;

                    float t = l_imuMeasurements_st.temperature_f64;
                    float pr = l_imuMeasurements_st.pressure_f64;

                    int mot1 = pwmValue;
                    int mot2 = pwmValue;
                    int mot3 = pwmValue;
                    int mot4 = pwmValue;

                    clocks = sprintf(tis, "TimS%u\n", res);
                    clockms = sprintf(tims, "TimM%u\n", ms);
                    int sizeC = clocks + clockms;
                    accx = sprintf(imu_x, "AccX%f\n", ax);
                    int sizeAccX = sizeC + accx;
                    accy = sprintf(imu_y, "AccY%f\n", ay);
                    int sizeAccY = sizeAccX + accy;
                    accz = sprintf(imu_z, "AccZ%f\n", az);
                    int sizeAccZ = sizeAccY + accz;

                    magx = sprintf(mag_x, "MagX%f\n", mx);
                    int sizemagX = sizeAccZ + magx;

                    magy = sprintf(mag_y, "MagY%f\n", my);
                    int sizemagY = sizemagX + magy;

                    magz = sprintf(mag_z, "MagZ%f\n", mz);
                    int sizemagZ = sizemagY + magz;

                    gy = sprintf(g_y, "GyrY%f\n", y);
                    int sizeGy = sizemagZ + gy;
                    gp = sprintf(g_p, "GyrP%f\n", p);
                    int sizeGp = sizeGy + gp;

                    gr = sprintf(g_r, "GyrR%f\n", r);
                    int sizeGr = sizeGp + gr;

                    temp = sprintf(tmp, "Temp%f\n", t);
                    int sizeTemp = sizeGr + temp;
                    press = sprintf(prs, "Pres%f\n", pr);
                    int sizePress = sizeTemp + press;
                    m1 = sprintf(Motor1, "Mot1%u\n", mot1);
                    int sizeM1 = sizePress + m1;
                    m2 = sprintf(Motor2, "Mot2%u\n", mot2);
                    int sizeM2 = sizeM1 + m2;
                    m3 = sprintf(Motor3, "Mot3%u\n", mot3);
                    int sizeM3 = sizeM2 + m3;
                    m4 = sprintf(Motor4, "Mot4%u\n", mot4);
                    int sizeM4 = sizeM3 + m4;

                    memcpy(buffer, tis, clocks);
                    memcpy(buffer + clocks, tims, clockms);
                    memcpy(buffer + sizeC, imu_x, accx);
                    memcpy(buffer + sizeAccX, imu_y, accy);
                    memcpy(buffer + sizeAccY, imu_z, accz);
                    memcpy(buffer + sizeAccZ, mag_x, magx);
                    memcpy(buffer + sizemagX, mag_y, magy);
                    memcpy(buffer + sizemagY, mag_z, magz);
                    memcpy(buffer + sizemagZ, g_y, gy);
                    memcpy(buffer + sizeGy, g_p, gp);
                    memcpy(buffer + sizeGp, g_r, gr);
                    memcpy(buffer + sizeGr, tmp, temp);
                    memcpy(buffer + sizeTemp, prs, press);
                    memcpy(buffer + sizePress, Motor1, m1);
                    memcpy(buffer + sizeM1, Motor2, m2);
                    memcpy(buffer + sizeM2, Motor3, m3);
                    memcpy(buffer + sizeM3, Motor4, m4);

                    sendto(send, buffer, sizeof(buffer), 0,
                            (struct sockaddr *) &sendAddr, addressSize);

                    pwmValue = pwmValue + STEPSIZE;

                    usleep(100000);
                }

                while (pwmValue > 5) {

                    sendBuffer[0] = pwmValue;

                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[0],
                            &sendBuffer[0], 1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[1],
                            &sendBuffer[0], 1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[2],
                            &sendBuffer[0], 1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[3],
                            &sendBuffer[0], 1);
                    g_halImu_triggerImuReading_bool();
                    g_halImu_triggerBaroReading_bool();
                    g_halImu_triggerGyroReading_bool();
                    g_halImu_triggerAccReading_bool();

                    //Get Sensor Data and Timestamp

                    l_imuMeasurements_st = g_halImu_getsensorValues_str();

                    long ms; // Milliseconds
                    struct timespec spec;
                    time_t res;
                    res = time(NULL);
                    clock_gettime(CLOCK_REALTIME, &spec);
                    ms = round(spec.tv_nsec / 1.0e6); // nano -> mili

                    //Call SensorData an save them in floats

                    float ax = l_imuMeasurements_st.acc.x_f64;
                    float ay = l_imuMeasurements_st.acc.y_f64;
                    float az = l_imuMeasurements_st.acc.z_f64;

                    float mx = l_imuMeasurements_st.mag.x_f64;
                    float my = l_imuMeasurements_st.mag.y_f64;
                    float mz = l_imuMeasurements_st.mag.z_f64;

                    float y = l_imuMeasurements_st.gyro.yaw_f64;
                    float p = l_imuMeasurements_st.gyro.pitch_f64;
                    float r = l_imuMeasurements_st.gyro.roll_f64;

                    float t = l_imuMeasurements_st.temperature_f64;
                    float pr = l_imuMeasurements_st.pressure_f64;

                    int mot1 = pwmValue;
                    int mot2 = pwmValue;
                    int mot3 = pwmValue;
                    int mot4 = pwmValue;

                    clocks = sprintf(tis, "TimS%u\n", res);
                    clockms = sprintf(tims, "TimM%u\n", ms);
                    int sizeC = clocks + clockms;
                    accx = sprintf(imu_x, "AccX%f\n", ax);
                    int sizeAccX = sizeC + accx;
                    accy = sprintf(imu_y, "AccY%f\n", ay);
                    int sizeAccY = sizeAccX + accy;
                    accz = sprintf(imu_z, "AccZ%f\n", az);
                    int sizeAccZ = sizeAccY + accz;

                    magx = sprintf(mag_x, "MagX%f\n", mx);
                    int sizemagX = sizeAccZ + magx;

                    magy = sprintf(mag_y, "MagY%f\n", my);
                    int sizemagY = sizemagX + magy;

                    magz = sprintf(mag_z, "MagZ%f\n", mz);
                    int sizemagZ = sizemagY + magz;

                    gy = sprintf(g_y, "GyrY%f\n", y);
                    int sizeGy = sizemagZ + gy;
                    gp = sprintf(g_p, "GyrP%f\n", p);
                    int sizeGp = sizeGy + gp;

                    gr = sprintf(g_r, "GyrR%f\n", r);
                    int sizeGr = sizeGp + gr;

                    temp = sprintf(tmp, "Temp%f\n", t);
                    int sizeTemp = sizeGr + temp;
                    press = sprintf(prs, "Pres%f\n", pr);
                    int sizePress = sizeTemp + press;
                    m1 = sprintf(Motor1, "Mot1%u\n", mot1);
                    int sizeM1 = sizePress + m1;
                    m2 = sprintf(Motor2, "Mot2%u\n", mot2);
                    int sizeM2 = sizeM1 + m2;
                    m3 = sprintf(Motor3, "Mot3%u\n", mot3);
                    int sizeM3 = sizeM2 + m3;
                    m4 = sprintf(Motor4, "Mot4%u\n", mot4);
                    int sizeM4 = sizeM3 + m4;

                    memcpy(buffer, tis, clocks);
                    memcpy(buffer + clocks, tims, clockms);
                    memcpy(buffer + sizeC, imu_x, accx);
                    memcpy(buffer + sizeAccX, imu_y, accy);
                    memcpy(buffer + sizeAccY, imu_z, accz);
                    memcpy(buffer + sizeAccZ, mag_x, magx);
                    memcpy(buffer + sizemagX, mag_y, magy);
                    memcpy(buffer + sizemagY, mag_z, magz);
                    memcpy(buffer + sizemagZ, g_y, gy);
                    memcpy(buffer + sizeGy, g_p, gp);
                    memcpy(buffer + sizeGp, g_r, gr);
                    memcpy(buffer + sizeGr, tmp, temp);
                    memcpy(buffer + sizeTemp, prs, press);
                    memcpy(buffer + sizePress, Motor1, m1);
                    memcpy(buffer + sizeM1, Motor2, m2);
                    memcpy(buffer + sizeM2, Motor3, m3);
                    memcpy(buffer + sizeM3, Motor4, m4);

                    sendto(send, buffer, sizeof(buffer), 0,
                            (struct sockaddr *) &sendAddr, addressSize);

                    usleep(100000);

                    pwmValue = pwmValue - STEPSIZE;
                }
            }
        }

            break;

            /*!**********************************************************************
             * \author  Marcel Früh
             * \date    2016/08/15
             *
             *
             * \details Receiver for the C++ APP. Receives char array and
             *          runs different operations, depending on the indicators
             *          in the received char.
             *
             *
             ***********************************************************************/


//            char toSend[30]=".00:42:01:42:02:42:03:42." So kann jeder Motor einzeln angesteuert werden, mit dem gewünschten Wert. 00-03 sind dabei die Motoren. Nach dem Doppelpunkt folgt der PWM Wert.\\$
//            char toSend[30]=".go:42:go:42:go:42:go:42." Alle Rotoren drehen sich mit dem PWM Wert 15\\$
//            char toSend[30]=".aa:42:aa:42:aa:42:aa:42." Testen der Motoren\\$
//            char toSend[30]=".dm:42:dm:42:dm:42:dm:42." Starten der Demo\\$

        case RECEIVE: {

            //Preparation for Sensor Calls
            HAL_SENSOR_PAYLOAD_ST l_imuMeasurements_st;
            g_halImu_initImuSensors_bool();

            char BLCtrlADRExecuteOrder[DEFMotorsCount];

            //Testfälle

            char test[] = "aa"; //Testen aller 4 Motoren
            char start[] = "go"; //Alle 4 Motoren laufen mit konstanter Geschwindigkeit
            char stop[] = "st"; //Die Motoren stoppen
            char demo[] = "dm";

            char mot0[] = "00";
            char mot1[] = "01";
            char mot2[] = "02";
            char mot3[] = "03";

            GetBLCtrlADRExecuteOrder(&BLCtrlADRExecuteOrder[0]);
            char sendBuffer0[1];
            char sendBuffer1[1];
            char sendBuffer2[1];
            char sendBuffer3[1];

            unsigned int pwmValue0;
            unsigned int pwmValue1;
            unsigned int pwmValue2;
            unsigned int pwmValue3;

            char msg0[50];


            while (1) {

                char *ind0, *ind1, *ind2, *ind3;
                char *pwm0, *pwm1, *pwm2, *pwm3;

                //receive from APP
                recv(receive, msg0, sizeof(msg0), 0);
                printf("Msg0 \n %s",msg0);



               printf("Garbage %s \n", strtok(msg0, "."));

                ind0 = strtok(NULL, ":");
                printf("Ind0 %s \n",ind0);

                pwm0 = strtok(NULL, ":");
                printf("Pwm0 %s \n",pwm0);

                ind1 = strtok(NULL, ":");
                printf("Ind1 %s \n",ind1);


                pwm1 = strtok(NULL, ":");
                printf("Pwm1 %s \n",pwm1);


                ind2 = strtok(NULL, ":");
                printf("Ind2 %s \n",ind2);


                pwm2 = strtok(NULL, ":");
                printf("Pwm2 %s \n",pwm2);


                ind3 = strtok(NULL, ":");
                printf("Ind3 %s \n",ind3);


                pwm3 = strtok(NULL, ".");
                printf("Pwm3 %s \n",pwm3);



                //Motortest, alle Motoren laufen kurz
                if (strcmp(test, ind0) == 0) {
                    printf("Test\n");
                    pwmValue0 = 10;
                    pwmValue1 = 10;
                    pwmValue2 = 10;
                    pwmValue3 = 10;
                    sendBuffer0[0] = pwmValue0;
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[0],
                            &sendBuffer0[0], 1);
                    sleep(1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[1],
                            &sendBuffer0[0], 1);
                    sleep(1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[2],
                            &sendBuffer0[0], 1);
                    sleep(1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[3],
                            &sendBuffer0[0], 1);
                }

                //Alle 4 Motoren laufen mit konstanter Geschwindigkeit

                if (strcmp(start, ind0) == 0) {
                    printf("Starting Motors\n");
                    pwmValue0 = 15;
                    pwmValue1 = 15;
                    pwmValue2 = 15;
                    pwmValue3 = 15;
                    sendBuffer0[0] = pwmValue0;

                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[0],
                            &sendBuffer0[0], 1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[1],
                            &sendBuffer0[0], 1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[2],
                            &sendBuffer0[0], 1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[3],
                            &sendBuffer0[0], 1);
                }

                //Alle 4 Motoren stoppen
                if (strcmp(stop, ind0) == 0) {
                    printf("STOP\n");
                    pwmValue0 = 0;
                    pwmValue1 = 0;
                    pwmValue2 = 0;
                    pwmValue3 = 0;
                    //Motoren halten wenn nicht angesteuert an;
                    //Kein Code nötig
                }

                //DEMO
                if (strcmp(ind0, demo) == 0) {
                    printf("Start DEMO\n");
                    playDemo();
                }

                //Steuerung

                if (strcmp(mot0, ind0) == 0) {
                    pwmValue0 = atoi(pwm0);
                    sendBuffer0[0] = pwmValue0;
                    printf("PWM0 %u\n", pwmValue0);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[0],
                            &sendBuffer0[0], 1);

                }

                if (strcmp(mot1, ind1) == 0) {
                    pwmValue1 = atoi(pwm1);
                    sendBuffer1[0] = pwmValue1;
                    printf("PWM1 %u\n", pwmValue1);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[1],
                            &sendBuffer1[0], 1);

                }

                if (strcmp(mot2, ind2) == 0) {
                    pwmValue2 = atoi(pwm2);
                    sendBuffer2[0] = pwmValue2;
                    printf("PWM2 %u\n", pwmValue2);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[2],
                            &sendBuffer2[0], 1);

                }

                if (strcmp(mot3, ind3) == 0) {
                    pwmValue3 = atoi(pwm3);
                    sendBuffer3[0] = pwmValue3;
                    printf("PWM3 %u\n", pwmValue3);
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[3],
                            &sendBuffer3[0], 1);

                }


                g_halImu_triggerImuReading_bool();
                g_halImu_triggerBaroReading_bool();
                g_halImu_triggerGyroReading_bool();
                g_halImu_triggerAccReading_bool();

                //Get Sensor Data and Timestamp

                l_imuMeasurements_st = g_halImu_getsensorValues_str();

                long ms; // Milliseconds
                struct timespec spec;
                time_t res;
                res = time(NULL);
                clock_gettime(CLOCK_REALTIME, &spec);
                ms = round(spec.tv_nsec / 1.0e6); // nano -> mili

                //Call SensorData an save them in floats

                float ax = l_imuMeasurements_st.acc.x_f64;
                float ay = l_imuMeasurements_st.acc.y_f64;
                float az = l_imuMeasurements_st.acc.z_f64;

                float mx = l_imuMeasurements_st.mag.x_f64;
                float my = l_imuMeasurements_st.mag.y_f64;
                float mz = l_imuMeasurements_st.mag.z_f64;

                float y = l_imuMeasurements_st.gyro.yaw_f64;
                float p = l_imuMeasurements_st.gyro.pitch_f64;
                float r = l_imuMeasurements_st.gyro.roll_f64;

                float t = l_imuMeasurements_st.temperature_f64;
                float pr = l_imuMeasurements_st.pressure_f64;

                int mot1 = pwmValue0;
                int mot2 = pwmValue1;
                int mot3 = pwmValue2;
                int mot4 = pwmValue3;

                clocks = sprintf(tis, "TimS%u\n", res);
                clockms = sprintf(tims, "TimM%u\n", ms);
                int sizeC = clocks + clockms;
                accx = sprintf(imu_x, "AccX%f\n", ax);
                int sizeAccX = sizeC + accx;
                accy = sprintf(imu_y, "AccY%f\n", ay);
                int sizeAccY = sizeAccX + accy;
                accz = sprintf(imu_z, "AccZ%f\n", az);
                int sizeAccZ = sizeAccY + accz;

                magx = sprintf(mag_x, "MagX%f\n", mx);
                int sizemagX = sizeAccZ + magx;

                magy = sprintf(mag_y, "MagY%f\n", my);
                int sizemagY = sizemagX + magy;

                magz = sprintf(mag_z, "MagZ%f\n", mz);
                int sizemagZ = sizemagY + magz;

                gy = sprintf(g_y, "GyrY%f\n", y);
                int sizeGy = sizemagZ + gy;
                gp = sprintf(g_p, "GyrP%f\n", p);
                int sizeGp = sizeGy + gp;

                gr = sprintf(g_r, "GyrR%f\n", r);
                int sizeGr = sizeGp + gr;

                temp = sprintf(tmp, "Temp%f\n", t);
                int sizeTemp = sizeGr + temp;
                press = sprintf(prs, "Pres%f\n", pr);
                int sizePress = sizeTemp + press;
                m1 = sprintf(Motor1, "Mot1%u\n", mot1);
                int sizeM1 = sizePress + m1;
                m2 = sprintf(Motor2, "Mot2%u\n", mot2);
                int sizeM2 = sizeM1 + m2;
                m3 = sprintf(Motor3, "Mot3%u\n", mot3);
                int sizeM3 = sizeM2 + m3;
                m4 = sprintf(Motor4, "Mot4%u\n", mot4);
                int sizeM4 = sizeM3 + m4;

                memcpy(buffer, tis, clocks);
                memcpy(buffer + clocks, tims, clockms);
                memcpy(buffer + sizeC, imu_x, accx);
                memcpy(buffer + sizeAccX, imu_y, accy);
                memcpy(buffer + sizeAccY, imu_z, accz);
                memcpy(buffer + sizeAccZ, mag_x, magx);
                memcpy(buffer + sizemagX, mag_y, magy);
                memcpy(buffer + sizemagY, mag_z, magz);
                memcpy(buffer + sizemagZ, g_y, gy);
                memcpy(buffer + sizeGy, g_p, gp);
                memcpy(buffer + sizeGp, g_r, gr);
                memcpy(buffer + sizeGr, tmp, temp);
                memcpy(buffer + sizeTemp, prs, press);
                memcpy(buffer + sizePress, Motor1, m1);
                memcpy(buffer + sizeM1, Motor2, m2);
                memcpy(buffer + sizeM2, Motor3, m3);
                memcpy(buffer + sizeM3, Motor4, m4);

                sendto(send, buffer, sizeof(buffer), 0,
                        (struct sockaddr *) &sendAddr, addressSize);

            }
        }

            break;

        case TESTMOTORPWM: {
            char BLCtrlADRExecuteOrder[DEFMotorsCount];
            char sendBuffer[1];
            int i, j = 0;
            unsigned int pwmValue;

            const int STEPSIZE = 5;
            const int MAXPWMVALUE = 0x75;

            GetBLCtrlADRExecuteOrder(&BLCtrlADRExecuteOrder[0]);

            printf("Start Testing Motors with PWM");

            while (j != 1) {
                sendBuffer[0] = pwmValue;
                for (i = 0; i < DEFMotorsCount; i++) {
                    g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[i],
                            &sendBuffer[0], 1);
                    usleep(10); //10us delay for HW Driver
                }
                usleep(10000); //10ms
                pwmValue = pwmValue + STEPSIZE;
                if (pwmValue > MAXPWMVALUE) {
                    j = 1;
                }
            }
            break;
        }
        case TESTMOTORISR: {    //starts with first press of + or - than enter
                                //leave with pressing 'q'
            printf("Start Testing Motors with ISR");
            InitMotor(9000);

            int sendValue = DEFMotorSetpointMIN;
            int i = kbhit();
            while (i != 'q') {
                if (GetFlagRunSendPwmToMotor() == 1) {
                    sendPwmToMotor();
                }
                i = kbhit();
                int value;
                if (i == '+') {
                    int k = kbhit();
                    switch (k) {
                    case '0':
                        value = GetPwmMotor(0);
                        (value < 100) ? value++ : (value = 100);
                        SetPwmMotor(DEFMotorNo1_PWM, value, 0);
                        break;
                    case '1':
                        value = GetPwmMotor(1);
                        (value < 100) ? value++ : (value = 100);
                        SetPwmMotor(DEFMotorNo2_PWM, value, 0);
                        break;
                    case '2':
                        value = GetPwmMotor(2);
                        (value < 100) ? value++ : (value = 100);
                        SetPwmMotor(DEFMotorNo3_PWM, value, 0);
                        break;
                    case '3':
                        value = GetPwmMotor(3);
                        (value < 100) ? value++ : (value = 100);
                        SetPwmMotor(DEFMotorNo4_PWM, value, 0);
                        break;
                    case '4':
                        value = GetPwmMotor(4);
                        (value < 100) ? value++ : (value = 100);
                        SetPwmMotor(DEFMotorNo5_PWM, value, 0);
                        break;
                    case '5':
                        value = GetPwmMotor(5);
                        (value < 100) ? value++ : (value = 100);
                        SetPwmMotor(DEFMotorNo6_PWM, value, 0);
                        break;
                    case '6':
                        value = GetPwmMotor(6);
                        (value < 100) ? value++ : (value = 100);
                        SetPwmMotor(DEFMotorNo7_PWM, value, 0);
                        break;
                    case '7':
                        value = GetPwmMotor(7);
                        (value < 100) ? value++ : (value = 100);
                        SetPwmMotor(DEFMotorNo8_PWM, value, 0);
                        break;
                    default:
                        break;
                    }
                } else if (i == 45) {
                    int k = kbhit();
                    switch (k) {
                    case '0':
                        value = GetPwmMotor(0);
                        value > 0 ? value-- : (value = DEFMotorSetpointMIN);
                        SetPwmMotor(DEFMotorNo1_PWM, value, 0);
                        break;
                    case '1':
                        value = GetPwmMotor(1);
                        value > 0 ? value-- : (value = DEFMotorSetpointMIN);
                        SetPwmMotor(DEFMotorNo2_PWM, value, 0);
                        break;
                    case '2':
                        value = GetPwmMotor(2);
                        value > 0 ? value-- : (value = DEFMotorSetpointMIN);
                        SetPwmMotor(DEFMotorNo3_PWM, value, 0);
                        break;
                    case '3':
                        value = GetPwmMotor(3);
                        value > 0 ? value-- : (value = DEFMotorSetpointMIN);
                        SetPwmMotor(DEFMotorNo4_PWM, value, 0);
                        break;
                    case '4':
                        value = GetPwmMotor(4);
                        value > 0 ? value-- : (value = DEFMotorSetpointMIN);
                        SetPwmMotor(DEFMotorNo5_PWM, value, 0);
                        break;
                    case '5':
                        value = GetPwmMotor(5);
                        value > 0 ? value-- : (value = DEFMotorSetpointMIN);
                        SetPwmMotor(DEFMotorNo6_PWM, value, 0);
                        break;
                    case '6':
                        value = GetPwmMotor(6);
                        value > 0 ? value-- : (value = DEFMotorSetpointMIN);
                        SetPwmMotor(DEFMotorNo7_PWM, value, 0);
                        break;
                    case '7':
                        value = GetPwmMotor(7);
                        value > 0 ? value-- : (value = DEFMotorSetpointMIN);
                        SetPwmMotor(DEFMotorNo8_PWM, value, 0);
                        break;
                    }
                }
                /* Do Other Things*/
            }

            break;
        }
        case TESTMOTORTXT: {
            FILE *testFile;
            int lineLenght = 80;
            char line[lineLenght];
            int delayS = 1;
            time_t timeStamp, currentTime;

            printf("Start Testing Motors reading txt file\n");

            InitMotor(9000);

//Wait 1 Sec
            time(&timeStamp);
            time(&currentTime);
            if (difftime(currentTime, timeStamp) >= 1) {
                if (GetFlagRunSendPwmToMotor() == 1) {
                    sendPwmToMotor();
                }
            }
            if ((testFile = fopen("/home/pi/testfiles/MotorTestSafe.txt", "r"))
                    == NULL) {
                fprintf(stderr, "File kann nicht geöffnet werden");
                exit(0);
            }

            time(&timeStamp);

            while (1) { // test ends when end of file reached
                if (GetFlagRunSendPwmToMotor() == 1) {
                    sendPwmToMotor();
                }

                time(&currentTime);
                if (difftime(currentTime, timeStamp) >= delayS) {
                    time(&timeStamp);
                    if ((fgets(line, lineLenght, testFile)) != NULL) {
                        printf("\n%s", line);
                        delayS = decodeline(&line[0], sizeof(line));
                    } else {
                        break;
                    }
                }
            }
            break;
        }
        default:
        case TESTEND: {
            printf("Nothing found");
            break;
        }

        case TESTGUI: {
            printf("Start Sending Messages\n");
            int i = kbhit();
            int writtencharacters;
            while (i != 'q') {
                sleep(1);
                int random = rand() % 1500;
                char randomToSend[20];
                writtencharacters = sprintf(randomToSend, "%d\n", random);
                sendto(send, randomToSend, writtencharacters, 0,
                        (struct sockaddr *) &remoteaddress, addressSize);
                printf("And send again....%d\n", random);
            }
            break;
        }
        case TESTSINGLESENSOR: {
            printf("Lets send some cool data \n");
            int writtencharacters;
            HAL_SENSOR_PAYLOAD_ST l_imuMeasurements_st;
            g_halImu_initImuSensors_bool();
            printf("Start Sending Messages\n");
            char imu_x[16];
            int i = kbhit();
            while (i != 'q') {
                sleep(1);
                g_halImu_triggerImuReading_bool();
                g_halImu_triggerBaroReading_bool();
                g_halImu_triggerGyroReading_bool();
                g_halImu_triggerAccReading_bool();

                l_imuMeasurements_st = g_halImu_getsensorValues_str();

                printf("Acc X %f \n", l_imuMeasurements_st.acc.x_f64);

                float k = l_imuMeasurements_st.acc.x_f64;
                writtencharacters = sprintf(imu_x, "%f \n", k);
                printf(imu_x, '\n'); //this prints the right number

                sendto(send, imu_x, writtencharacters, 0,
                        (struct sockaddr *) &remoteaddress, addressSize);
                printf("And send again....\n");
            }
            break;
        }

        }
    } //end while(1)
    return 0;
}

int readTestcaseFile(char testcase[], int lenght) {
    FILE *testCasesFile;
    int isSelected = 0;
    char* stringToken;
    char charIsSelected[lenght];
    char fullLine[30];
    int i;

    if ((testCasesFile = fopen("/home/pi/testfiles/_Testcases", "r+")) == NULL) {
        fprintf(stderr, "File kann nicht geöffnet werden (w+)");
        exit(0);
    }

    while ((fgets(testcase, lenght, testCasesFile)) != NULL) {
        stringToken = strtok(testcase, "=\n");
        strcpy(testcase, stringToken);

        stringToken = strtok(NULL, "=\n");
        strcpy(charIsSelected, stringToken);
        isSelected = charIsSelected[0] - '0';

        if (isSelected == 1) {
            strcpy(fullLine, testcase);
            for (i = 0; i < sizeof(fullLine); i++) {
                if (fullLine[i] == '\0') {
                    fullLine[i] = '=';
                    i++;
                    fullLine[i] = '1'; //Set to 1 if you dont want to set the test to 0 in _testcase
                    i++;
                    fullLine[i] = '\n';
                    i++;
                    fullLine[i] = '\0';
                    break;
                } //if
            } //for
              //Change Postion of seek
            fseek(testCasesFile, -i, SEEK_CUR);
            //Write line
            fputs(fullLine, testCasesFile);
            fclose(testCasesFile);
            return 1;
        }            //if
    }            //while( not end of file read)
    /* Not Testcase selected*/
    return 0;

}

#include <termios.h>

int kbhit(void) {
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

int decodeline(char line[], int lineLenght) {
    int motorNumber;
    char controllChar;
    int pwmValue;
    int offsetPwmValue = 0;
    int delay = 0;
    char *pNext;
    char* stringToken;

    char charMotorNumber[lineLenght];
    char charPwmValue[lineLenght];
    char charDelay[lineLenght];

    if (line[0] == '#') {
        controllChar = line[2];

        stringToken = strtok(line, "#+-=;\n");
        strcpy(charMotorNumber, stringToken);
        motorNumber = charMotorNumber[0] - '0';

        stringToken = strtok(NULL, "#+-=;\n");
        strcpy(charPwmValue, stringToken);
        pwmValue = strtol(charPwmValue, &pNext, 10);

        stringToken = strtok(NULL, "#+-=;\n");
        strcpy(charDelay, stringToken);
        delay = strtol(charDelay, &pNext, 10);

        printf("pwmValue : %i", pwmValue);

        switch (motorNumber) {
        case 0:
            pwmValue = calcPwmValue(controllChar, motorNumber, pwmValue);
            SetPwmMotor(DEFMotorNo1_PWM, pwmValue, 0);
            break;
        case 1:
            pwmValue = calcPwmValue(controllChar, motorNumber, pwmValue);
            SetPwmMotor(DEFMotorNo2_PWM, pwmValue, 0);
            break;
        case 2:
            pwmValue = calcPwmValue(controllChar, motorNumber, pwmValue);
            SetPwmMotor(DEFMotorNo3_PWM, pwmValue, 0);
            break;
        case 3:
            pwmValue = calcPwmValue(controllChar, motorNumber, pwmValue);
            SetPwmMotor(DEFMotorNo4_PWM, pwmValue, 0);
            break;
        case 4:
            pwmValue = calcPwmValue(controllChar, motorNumber, pwmValue);
            SetPwmMotor(DEFMotorNo5_PWM, pwmValue, 0);
            break;
        case 5:
            pwmValue = calcPwmValue(controllChar, motorNumber, pwmValue);
            SetPwmMotor(DEFMotorNo6_PWM, pwmValue, 0);
            break;
        case 6:
            pwmValue = calcPwmValue(controllChar, motorNumber, pwmValue);
            SetPwmMotor(DEFMotorNo7_PWM, pwmValue, 0);
            break;
        case 7:
            pwmValue = calcPwmValue(controllChar, motorNumber, pwmValue);
            SetPwmMotor(DEFMotorNo8_PWM, pwmValue, 0);
            break;
        case 12: // CW'>'
            if (controllChar == '=') {
                SetPwmMotor(DEFMotorCW_PWM, pwmValue, 0);
            } else {

                offsetPwmValue = calcPwmValue(controllChar, 0, pwmValue);
                SetPwmMotor(DEFMotorNo1_PWM, offsetPwmValue, 0);
                offsetPwmValue = calcPwmValue(controllChar, 2, pwmValue);
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
            if (controllChar == '=') {
                SetPwmMotor(DEFMotorCCW_PWM, pwmValue, 0);
            } else {
                offsetPwmValue = calcPwmValue(controllChar, 1, pwmValue);
                SetPwmMotor(DEFMotorNo2_PWM, offsetPwmValue, 0);
                offsetPwmValue = calcPwmValue(controllChar, 3, pwmValue);
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
        } //switch
        printf("motorNumber : %i", motorNumber);
    } //if
    return delay;
}

int calcPwmValue(char controllChar, int motorNumber, int pwmValue) {
    switch (controllChar) {
    case '+':
        pwmValue = GetPwmMotor(motorNumber) + pwmValue;
        break;
    case '-':
        pwmValue = GetPwmMotor(motorNumber) - pwmValue;
        break;
    case '=':
        break;
    default:
        break;
    }
    return pwmValue;
}

void playDemo() {

    //Trigger Sensors
    HAL_SENSOR_PAYLOAD_ST l_imuMeasurements_st;
    g_halImu_initImuSensors_bool();

    //UDP
    int send = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    sprintf(sendAddrString, REMOTE_ADDR);
    memset(sendAddr.sin_zero, '\0', sizeof(sendAddr.sin_zero));
    sendAddr.sin_family = PF_INET;
    sendAddr.sin_port = htons(REMOTE_PORT);
    sendAddr.sin_addr.s_addr = inet_addr(REMOTE_ADDR);

    //Motor
    printf("Beschleunigungstest \n");

    char BLCtrlADRExecuteOrder[DEFMotorsCount];
    char sendBuffer[1];
    unsigned int pwmValue = 1;
    int STEPSIZE = 1;
    int MAXPWMVALUE = 65;

    GetBLCtrlADRExecuteOrder(&BLCtrlADRExecuteOrder[0]);

    //First Sensor then Motor
    while (pwmValue < MAXPWMVALUE) {

        sendBuffer[0] = pwmValue;

        g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[0], &sendBuffer[0], 1);
        g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[1], &sendBuffer[0], 1);
        g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[2], &sendBuffer[0], 1);
        g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[3], &sendBuffer[0], 1);

        //Preparation for Sensor Calls

        g_halImu_triggerImuReading_bool();
        g_halImu_triggerBaroReading_bool();
        g_halImu_triggerGyroReading_bool();
        g_halImu_triggerAccReading_bool();

        //Get Sensor Data and Timestamp

        l_imuMeasurements_st = g_halImu_getsensorValues_str();

        long ms; // Milliseconds
        struct timespec spec;
        time_t res;
        res = time(NULL);
        clock_gettime(CLOCK_REALTIME, &spec);
        ms = round(spec.tv_nsec / 1.0e6); // nano -> mili

        //Call SensorData an save them in floats

        float ax = l_imuMeasurements_st.acc.x_f64;
        float ay = l_imuMeasurements_st.acc.y_f64;
        float az = l_imuMeasurements_st.acc.z_f64;

        float mx = l_imuMeasurements_st.mag.x_f64;
        float my = l_imuMeasurements_st.mag.y_f64;
        float mz = l_imuMeasurements_st.mag.z_f64;

        float y = l_imuMeasurements_st.gyro.yaw_f64;
        float p = l_imuMeasurements_st.gyro.pitch_f64;
        float r = l_imuMeasurements_st.gyro.roll_f64;

        float t = l_imuMeasurements_st.temperature_f64;
        float pr = l_imuMeasurements_st.pressure_f64;

        //No Motor running : ZERO
        int mot1 = pwmValue;
        int mot2 = pwmValue;
        int mot3 = pwmValue;
        int mot4 = pwmValue;

        clocks = sprintf(tis, "TimS%u\n", res);
        clockms = sprintf(tims, "TimM%u\n", ms);
        int sizeC = clocks + clockms;
        accx = sprintf(imu_x, "AccX%f\n", ax);
        int sizeAccX = sizeC + accx;
        accy = sprintf(imu_y, "AccY%f\n", ay);
        int sizeAccY = sizeAccX + accy;
        accz = sprintf(imu_z, "AccZ%f\n", az);
        int sizeAccZ = sizeAccY + accz;

        magx = sprintf(mag_x, "MagX%f\n", mx);
        int sizemagX = sizeAccZ + magx;

        magy = sprintf(mag_y, "MagY%f\n", my);
        int sizemagY = sizemagX + magy;

        magz = sprintf(mag_z, "MagZ%f\n", mz);
        int sizemagZ = sizemagY + magz;

        gy = sprintf(g_y, "GyrY%f\n", y);
        int sizeGy = sizemagZ + gy;
        gp = sprintf(g_p, "GyrP%f\n", p);
        int sizeGp = sizeGy + gp;

        gr = sprintf(g_r, "GyrR%f\n", r);
        int sizeGr = sizeGp + gr;

        temp = sprintf(tmp, "Temp%f\n", t);
        int sizeTemp = sizeGr + temp;
        press = sprintf(prs, "Pres%f\n", pr);
        int sizePress = sizeTemp + press;
        m1 = sprintf(Motor1, "Mot1%u\n", mot1);
        int sizeM1 = sizePress + m1;
        m2 = sprintf(Motor2, "Mot2%u\n", mot2);
        int sizeM2 = sizeM1 + m2;
        m3 = sprintf(Motor3, "Mot3%u\n", mot3);
        int sizeM3 = sizeM2 + m3;
        m4 = sprintf(Motor4, "Mot4%u\n", mot4);
        int sizeM4 = sizeM3 + m4;

        memcpy(buffer, tis, clocks);
        memcpy(buffer + clocks, tims, clockms);
        memcpy(buffer + sizeC, imu_x, accx);
        memcpy(buffer + sizeAccX, imu_y, accy);
        memcpy(buffer + sizeAccY, imu_z, accz);
        memcpy(buffer + sizeAccZ, mag_x, magx);
        memcpy(buffer + sizemagX, mag_y, magy);
        memcpy(buffer + sizemagY, mag_z, magz);
        memcpy(buffer + sizemagZ, g_y, gy);
        memcpy(buffer + sizeGy, g_p, gp);
        memcpy(buffer + sizeGp, g_r, gr);
        memcpy(buffer + sizeGr, tmp, temp);
        memcpy(buffer + sizeTemp, prs, press);
        memcpy(buffer + sizePress, Motor1, m1);
        memcpy(buffer + sizeM1, Motor2, m2);
        memcpy(buffer + sizeM2, Motor3, m3);
        memcpy(buffer + sizeM3, Motor4, m4);
        sendto(send, buffer, sizeof(buffer), 0, (struct sockaddr *) &sendAddr,
                addressSize);

        pwmValue = pwmValue + STEPSIZE;

        usleep(100000);
    }

    while (pwmValue > 5) {

        sendBuffer[0] = pwmValue;

        g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[0], &sendBuffer[0], 1);
        g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[1], &sendBuffer[0], 1);
        g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[2], &sendBuffer[0], 1);
        g_lldI2c_Write_bool(BLCtrlADRExecuteOrder[3], &sendBuffer[0], 1);
        g_halImu_triggerImuReading_bool();
        g_halImu_triggerBaroReading_bool();
        g_halImu_triggerGyroReading_bool();
        g_halImu_triggerAccReading_bool();

        //Get Sensor Data and Timestamp

        l_imuMeasurements_st = g_halImu_getsensorValues_str();

        long ms; // Milliseconds
        struct timespec spec;
        time_t res;
        res = time(NULL);
        clock_gettime(CLOCK_REALTIME, &spec);
        ms = round(spec.tv_nsec / 1.0e6); // nano -> mili

        //Call SensorData an save them in floats

        float ax = l_imuMeasurements_st.acc.x_f64;
        float ay = l_imuMeasurements_st.acc.y_f64;
        float az = l_imuMeasurements_st.acc.z_f64;

        float mx = l_imuMeasurements_st.mag.x_f64;
        float my = l_imuMeasurements_st.mag.y_f64;
        float mz = l_imuMeasurements_st.mag.z_f64;

        float y = l_imuMeasurements_st.gyro.yaw_f64;
        float p = l_imuMeasurements_st.gyro.pitch_f64;
        float r = l_imuMeasurements_st.gyro.roll_f64;

        float t = l_imuMeasurements_st.temperature_f64;
        float pr = l_imuMeasurements_st.pressure_f64;

        //No Motor running : ZERO
        int mot1 = pwmValue;
        int mot2 = pwmValue;
        int mot3 = pwmValue;
        int mot4 = pwmValue;

        clocks = sprintf(tis, "TimS%u\n", res);
        clockms = sprintf(tims, "TimM%u\n", ms);
        int sizeC = clocks + clockms;
        accx = sprintf(imu_x, "AccX%f\n", ax);
        int sizeAccX = sizeC + accx;
        accy = sprintf(imu_y, "AccY%f\n", ay);
        int sizeAccY = sizeAccX + accy;
        accz = sprintf(imu_z, "AccZ%f\n", az);
        int sizeAccZ = sizeAccY + accz;

        magx = sprintf(mag_x, "MagX%f\n", mx);
        int sizemagX = sizeAccZ + magx;

        magy = sprintf(mag_y, "MagY%f\n", my);
        int sizemagY = sizemagX + magy;

        magz = sprintf(mag_z, "MagZ%f\n", mz);
        int sizemagZ = sizemagY + magz;

        gy = sprintf(g_y, "GyrY%f\n", y);
        int sizeGy = sizemagZ + gy;
        gp = sprintf(g_p, "GyrP%f\n", p);
        int sizeGp = sizeGy + gp;

        gr = sprintf(g_r, "GyrR%f\n", r);
        int sizeGr = sizeGp + gr;

        temp = sprintf(tmp, "Temp%f\n", t);
        int sizeTemp = sizeGr + temp;
        press = sprintf(prs, "Pres%f\n", pr);
        int sizePress = sizeTemp + press;
        m1 = sprintf(Motor1, "Mot1%u\n", mot1);
        int sizeM1 = sizePress + m1;
        m2 = sprintf(Motor2, "Mot2%u\n", mot2);
        int sizeM2 = sizeM1 + m2;
        m3 = sprintf(Motor3, "Mot3%u\n", mot3);
        int sizeM3 = sizeM2 + m3;
        m4 = sprintf(Motor4, "Mot4%u\n", mot4);
        int sizeM4 = sizeM3 + m4;

        memcpy(buffer, tis, clocks);
        memcpy(buffer + clocks, tims, clockms);
        memcpy(buffer + sizeC, imu_x, accx);
        memcpy(buffer + sizeAccX, imu_y, accy);
        memcpy(buffer + sizeAccY, imu_z, accz);
        memcpy(buffer + sizeAccZ, mag_x, magx);
        memcpy(buffer + sizemagX, mag_y, magy);
        memcpy(buffer + sizemagY, mag_z, magz);
        memcpy(buffer + sizemagZ, g_y, gy);
        memcpy(buffer + sizeGy, g_p, gp);
        memcpy(buffer + sizeGp, g_r, gr);
        memcpy(buffer + sizeGr, tmp, temp);
        memcpy(buffer + sizeTemp, prs, press);
        memcpy(buffer + sizePress, Motor1, m1);
        memcpy(buffer + sizeM1, Motor2, m2);
        memcpy(buffer + sizeM2, Motor3, m3);
        memcpy(buffer + sizeM3, Motor4, m4);

        sendto(send, buffer, sizeof(buffer), 0, (struct sockaddr *) &sendAddr,
                addressSize);

        usleep(100000);

        pwmValue = pwmValue - STEPSIZE;
    }

}

