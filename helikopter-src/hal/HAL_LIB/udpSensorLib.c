/*!
 * \file udpSensorLib.c
 */
#include <string.h>
#include<time.h>
#include "udpSensorLib.h"


unsigned int g_hal_send_angles_raw_bool(    int f_socketHandler_i32,
                                            HAL_ANGLE_PAYLOAD_ST f_sigState_st )
{

    HAL_RT_ANGLE_PAYLOAD_ST    l_rtSigPayload_st;
    struct timespec            l_timestamp_st;

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

    //assmeble timestamp and
    l_rtSigPayload_st.timestamp_st     = l_timestamp_st;
    l_rtSigPayload_st.sigState_st    = f_sigState_st;

    return g_udp_sendPacket_bool(     f_socketHandler_i32,
                                        (unsigned char*)&l_rtSigPayload_st,
                                        sizeof( l_rtSigPayload_st ) );
}



unsigned int g_hal_send_all_angles_calculated_bool(    int f_socketHandler_i32,
                                                HAL_SENSOR_PAYLOAD_ST f_rawsensorValues_st,
                                                HAL_ANGLE_PAYLOAD_ST f_sigKalmanState_st,
                                                HAL_ANGLE_PAYLOAD_ST f_sigComplementaryState_st )
{

    HAL_RT_SENSOR_PAYLOAD_FUSION_ST    l_rtCompleteSigPayload_st;
    struct timespec                    l_timestamp_st;

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

    //assmeble timestamp and
    l_rtCompleteSigPayload_st.timestamp_st                 = l_timestamp_st;
    l_rtCompleteSigPayload_st.sensorValues_st                = f_rawsensorValues_st;
    l_rtCompleteSigPayload_st.kalmanSigState_st         = f_sigKalmanState_st;
    l_rtCompleteSigPayload_st.complementarySigState_st    = f_sigComplementaryState_st;

    return g_udp_sendPacket_bool(     f_socketHandler_i32,
                                        (unsigned char*)&l_rtCompleteSigPayload_st,
                                        sizeof( l_rtCompleteSigPayload_st ) );
}


HAL_RT_ANGLE_PAYLOAD_ST g_hal_receive_angles_raw_bool( int f_socketHandler_i32 ) {
    HAL_RT_ANGLE_PAYLOAD_ST         l_recvSigState_st;
    unsigned char                l_recvBuffer_rgXui8[ sizeof(HAL_RT_ANGLE_PAYLOAD_ST) ];
    unsigned int                l_recvBytesNumber_ui32;

    // zero all values
    l_recvSigState_st.timestamp_st.tv_sec     = 0;
    l_recvSigState_st.timestamp_st.tv_nsec     = 0;

    l_recvSigState_st.sigState_st.roll_f64     = 0;
    l_recvSigState_st.sigState_st.pitch_f64 = 0;
    l_recvSigState_st.sigState_st.yaw_f64     = 0;


    // receive packet
    l_recvBytesNumber_ui32 = g_udp_recvPacket_ui32(    f_socketHandler_i32,
                                                            l_recvBuffer_rgXui8,
                                                            sizeof(HAL_RT_ANGLE_PAYLOAD_ST) );

    if ( l_recvBytesNumber_ui32 == sizeof(HAL_RT_ANGLE_PAYLOAD_ST) )
    {
        memcpy( &l_recvSigState_st, &l_recvBuffer_rgXui8, sizeof(HAL_RT_ANGLE_PAYLOAD_ST));
    }

    return l_recvSigState_st;
}


HAL_RT_SENSOR_PAYLOAD_FUSION_ST g_hal_receive_angles_calculated_bool( int f_socketHandler_i32 ) {
    HAL_RT_SENSOR_PAYLOAD_FUSION_ST         l_recvSigAllStates_st;
    unsigned char                              l_recvBuffer_rgXui8[ sizeof(HAL_RT_SENSOR_PAYLOAD_FUSION_ST) ];
    unsigned int                              l_recvBytesNumber_ui32;

    // zero all values
    l_recvSigAllStates_st.timestamp_st.tv_sec     = 0;
    l_recvSigAllStates_st.timestamp_st.tv_nsec     = 0;

    l_recvSigAllStates_st.sensorValues_st.acc.x_f64       = 0;
    l_recvSigAllStates_st.sensorValues_st.acc.y_f64       = 0;
    l_recvSigAllStates_st.sensorValues_st.acc.z_f64       = 0;
  
    l_recvSigAllStates_st.sensorValues_st.mag.x_f64       = 0;
    l_recvSigAllStates_st.sensorValues_st.mag.y_f64       = 0;
    l_recvSigAllStates_st.sensorValues_st.mag.z_f64       = 0;
  
    l_recvSigAllStates_st.sensorValues_st.gyro.roll_f64     = 0;
    l_recvSigAllStates_st.sensorValues_st.gyro.pitch_f64  = 0;
    l_recvSigAllStates_st.sensorValues_st.gyro.yaw_f64       = 0;
  
    l_recvSigAllStates_st.sensorValues_st.temperature_f64 = 0;
    l_recvSigAllStates_st.sensorValues_st.pressure_f64    = 0;
  
    l_recvSigAllStates_st.kalmanSigState_st.roll_f64     = 0;
    l_recvSigAllStates_st.kalmanSigState_st.pitch_f64 = 0;
    l_recvSigAllStates_st.kalmanSigState_st.yaw_f64     = 0;

    l_recvSigAllStates_st.complementarySigState_st.roll_f64     = 0;
    l_recvSigAllStates_st.complementarySigState_st.pitch_f64 = 0;
    l_recvSigAllStates_st.complementarySigState_st.yaw_f64     = 0;

    // receive packet
    l_recvBytesNumber_ui32 = g_udp_recvPacket_ui32(    f_socketHandler_i32,
                                                            l_recvBuffer_rgXui8,
                                                            sizeof(HAL_RT_SENSOR_PAYLOAD_FUSION_ST) );

    if ( l_recvBytesNumber_ui32 == sizeof(HAL_RT_SENSOR_PAYLOAD_FUSION_ST) )
    {
        memcpy( &l_recvSigAllStates_st, &l_recvBuffer_rgXui8, sizeof(HAL_RT_SENSOR_PAYLOAD_FUSION_ST));
    }

    return l_recvSigAllStates_st;
}



unsigned int g_hal_send_sensor_raw_bool(    int f_socketHandler_i32,
                                            HAL_SENSOR_PAYLOAD_ST f_sensorValues_st) {

    HAL_RT_SENSOR_PAYLOAD_ST    l_rtImuPayload_st;
    struct timespec            l_timestamp_st;

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

    //assmeble timestamp and
    l_rtImuPayload_st.timestamp_st     = l_timestamp_st;
    l_rtImuPayload_st.sensorValues_st    = f_sensorValues_st;

    return g_udp_sendPacket_bool(     f_socketHandler_i32,
                                        (unsigned char*)&l_rtImuPayload_st,
                                        sizeof( l_rtImuPayload_st ) );
}



HAL_RT_SENSOR_PAYLOAD_ST g_hal_receive_sensor_raw_bool(int f_socketHandler_i32) {
    HAL_RT_SENSOR_PAYLOAD_ST         l_recvsensorValues_st;
    unsigned char                l_recvBuffer_rgXui8[ sizeof(HAL_RT_SENSOR_PAYLOAD_ST) ];
    unsigned int                l_recvBytesNumber_ui32;

    // zero all values
    l_recvsensorValues_st.timestamp_st.tv_sec     = 0;
    l_recvsensorValues_st.timestamp_st.tv_nsec     = 0;

    l_recvsensorValues_st.sensorValues_st.acc.x_f64 = 0;
    l_recvsensorValues_st.sensorValues_st.acc.y_f64 = 0;
    l_recvsensorValues_st.sensorValues_st.acc.z_f64 = 0;

    l_recvsensorValues_st.sensorValues_st.gyro.pitch_f64 = 0;
    l_recvsensorValues_st.sensorValues_st.gyro.roll_f64 = 0;
    l_recvsensorValues_st.sensorValues_st.gyro.yaw_f64 = 0;

    l_recvsensorValues_st.sensorValues_st.mag.x_f64 = 0;
    l_recvsensorValues_st.sensorValues_st.mag.y_f64 = 0;
    l_recvsensorValues_st.sensorValues_st.mag.z_f64 = 0;

    l_recvsensorValues_st.sensorValues_st.pressure_f64 = 0;
    l_recvsensorValues_st.sensorValues_st.temperature_f64 = 0;

    // receive packet
    l_recvBytesNumber_ui32 = g_udp_recvPacket_ui32(    f_socketHandler_i32,
                                                            l_recvBuffer_rgXui8,
                                                            sizeof(HAL_RT_SENSOR_PAYLOAD_ST) );

    if ( l_recvBytesNumber_ui32 == sizeof(HAL_RT_SENSOR_PAYLOAD_ST) )
    {
        memcpy( &l_recvsensorValues_st, &l_recvBuffer_rgXui8, sizeof(HAL_RT_SENSOR_PAYLOAD_ST));
    }

    l_recvBytesNumber_ui32 = g_udp_recvPacket_ui32(    f_socketHandler_i32,
                                                            l_recvBuffer_rgXui8,
                                                            sizeof(HAL_SENSOR_PAYLOAD_ST) );

    if ( l_recvBytesNumber_ui32 == sizeof(HAL_SENSOR_PAYLOAD_ST) )
    {
        memcpy( &l_recvsensorValues_st, &l_recvBuffer_rgXui8, sizeof(HAL_SENSOR_PAYLOAD_ST));
    }


    return l_recvsensorValues_st;
}


HAL_SENSOR_PAYLOAD_ST g_hal_receive_sensor_raw_no_time_bool(int f_socketHandler_i32) {
    HAL_SENSOR_PAYLOAD_ST         l_recvsensorValues_st;
    unsigned char                l_recvBuffer_rgXui8[ sizeof(HAL_RT_SENSOR_PAYLOAD_ST) ];
    unsigned int                l_recvBytesNumber_ui32;

    l_recvsensorValues_st.acc.x_f64 = 0;
    l_recvsensorValues_st.acc.y_f64 = 0;
    l_recvsensorValues_st.acc.z_f64 = 0;

    l_recvsensorValues_st.gyro.pitch_f64 = 0;
    l_recvsensorValues_st.gyro.roll_f64 = 0;
    l_recvsensorValues_st.gyro.yaw_f64 = 0;

    l_recvsensorValues_st.mag.x_f64 = 0;
    l_recvsensorValues_st.mag.y_f64 = 0;
    l_recvsensorValues_st.mag.z_f64 = 0;

    l_recvsensorValues_st.pressure_f64 = 0;
    l_recvsensorValues_st.temperature_f64 = 0;

    // receive packet
    l_recvBytesNumber_ui32 = g_udp_recvPacket_ui32(    f_socketHandler_i32,
                                                            l_recvBuffer_rgXui8,
                                                            sizeof(HAL_SENSOR_PAYLOAD_ST) );

    if ( l_recvBytesNumber_ui32 == sizeof(HAL_SENSOR_PAYLOAD_ST) )
    {
        memcpy( &l_recvsensorValues_st, &l_recvBuffer_rgXui8, sizeof(HAL_SENSOR_PAYLOAD_ST));
    }

    return l_recvsensorValues_st;
}
