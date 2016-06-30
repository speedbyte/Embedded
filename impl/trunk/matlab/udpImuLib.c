/*!
 * \file udpImuLib.c
 */
#include <string.h>

#ifdef __linux__
    #include<time.h>
#endif

#include "udpImuLib.h"

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/17
 *
 * \brief    Sends a packet of IMU data with the current unuix-timestamp
 *             via a given UDP-Socket
 * \details    This function sends a data packet with the given IMU state
 *             via a given UDP-Socket. The    current timestamp is added to
 *             the payload to get some sort of    realtime behavior.\n
 *             This can be used to perform    a Software-in -the-Loop setup
 *             or test specific filter    algorithms in MATLAB.\n
 *             It is recommended to open the neccessary UDP-socket with
 *             g_halMatlab_initSocket_i32() or
 *             g_halMatlab_initConnection_i32().
 *
 *     \param[in]    f_socketHandler_i32 specifies socket handler number used
 *                 for the data transmission
 *     \param[in]    f_imuState_st is a the IMU state packed into a custom
 *                 struct type (type: halImu_orientationValues)
 *     \param[out] returns a boolean value, indicating the occurrence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halMatlab_sendImuState_bl(    int f_socketHandler_i32,
                                            halImu_orientationValues f_imuState_st) {

    halMatlab_rtImuPayload    l_rtImuPayload_st;
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
    l_rtImuPayload_st.imuState_st    = f_imuState_st;

    return g_halMatlab_sendPacket_bl(     f_socketHandler_i32,
                                        (unsigned char*)&l_rtImuPayload_st,
                                        sizeof( l_rtImuPayload_st ) );
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/17
 *
 * \brief    Receives a packet of IMU data with the current via a given
 *             UDP-Socket
 * \details    This function receives a data packet with a synthetic IMU
 *             state via a given UDP-Socket. This can be used to perform
 *             a Software-in -the-Loop setup or test specific filter
 *             algorithms in MATLAB.\n
 *             It is recommended to open the neccessary UDP-socket with
 *             g_halMatlab_initSocket_i32() or
 *             g_halMatlab_initConnection_i32().
 *
 *     \param[in]    f_socketHandler_i32 specifies socket handler number used
 *                 for the data transmission
 *     \param[out] returns the received synthetic IMU state packed into a
 *                 custom struct type (type: halImu_orientationValues)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
halMatlab_rtImuPayload g_halMatlab_recvImuStateAndTime_bl(int f_socketHandler_i32) {
    halMatlab_rtImuPayload         l_recvImuState_st;
    unsigned char                l_recvBuffer_rgXui8[ sizeof(halMatlab_rtImuPayload) ];
    unsigned int                l_recvBytesNumber_ui32;

    // zero all values
    l_recvImuState_st.timestamp_st.tv_sec     = 0;
    l_recvImuState_st.timestamp_st.tv_nsec     = 0;

    l_recvImuState_st.imuState_st.acc.x_f64 = 0;
    l_recvImuState_st.imuState_st.acc.y_f64 = 0;
    l_recvImuState_st.imuState_st.acc.z_f64 = 0;

    l_recvImuState_st.imuState_st.gyro.pitch_f64 = 0;
    l_recvImuState_st.imuState_st.gyro.roll_f64 = 0;
    l_recvImuState_st.imuState_st.gyro.yaw_f64 = 0;

    l_recvImuState_st.imuState_st.mag.x_f64 = 0;
    l_recvImuState_st.imuState_st.mag.y_f64 = 0;
    l_recvImuState_st.imuState_st.mag.z_f64 = 0;

    l_recvImuState_st.imuState_st.pressure_f64 = 0;
    l_recvImuState_st.imuState_st.temperature_f64 = 0;

    // receive packet
    l_recvBytesNumber_ui32 = g_halMatlab_recvPacket_ui32(    f_socketHandler_i32,
                                                            l_recvBuffer_rgXui8,
                                                            sizeof(halMatlab_rtImuPayload) );

    if ( l_recvBytesNumber_ui32 == sizeof(halMatlab_rtImuPayload) )
    {
        memcpy( &l_recvImuState_st, &l_recvBuffer_rgXui8, sizeof(halMatlab_rtImuPayload));
    }

    return l_recvImuState_st;
}


/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/17
 *
 * \brief    Receives a packet of IMU data with the current via a given
 *             UDP-Socket
 * \details    This function receives a data packet with a synthetic IMU
 *             state via a given UDP-Socket. This can be used to perform
 *             a Software-in -the-Loop setup or test specific filter
 *             algorithms in MATLAB.\n
 *             It is recommended to open the neccessary UDP-socket with
 *             g_halMatlab_initSocket_i32() or
 *             g_halMatlab_initConnection_i32().
 *
 *     \param[in]    f_socketHandler_i32 specifies socket handler number used
 *                 for the data transmission
 *     \param[out] returns the received synthetic IMU state packed into a
 *                 custom struct type (type: halImu_orientationValues)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
halImu_orientationValues g_halMatlab_recvImuState_bl(int f_socketHandler_i32) {
    halImu_orientationValues         l_recvImuState_st;
    unsigned char                l_recvBuffer_rgXui8[ sizeof(halMatlab_rtImuPayload) ];
    unsigned int                l_recvBytesNumber_ui32;

    l_recvImuState_st.acc.x_f64 = 0;
    l_recvImuState_st.acc.y_f64 = 0;
    l_recvImuState_st.acc.z_f64 = 0;

    l_recvImuState_st.gyro.pitch_f64 = 0;
    l_recvImuState_st.gyro.roll_f64 = 0;
    l_recvImuState_st.gyro.yaw_f64 = 0;

    l_recvImuState_st.mag.x_f64 = 0;
    l_recvImuState_st.mag.y_f64 = 0;
    l_recvImuState_st.mag.z_f64 = 0;

    l_recvImuState_st.pressure_f64 = 0;
    l_recvImuState_st.temperature_f64 = 0;

    // receive packet
    l_recvBytesNumber_ui32 = g_halMatlab_recvPacket_ui32(    f_socketHandler_i32,
                                                            l_recvBuffer_rgXui8,
                                                            sizeof(halImu_orientationValues) );

    if ( l_recvBytesNumber_ui32 == sizeof(halImu_orientationValues) )
    {
        memcpy( &l_recvImuState_st, &l_recvBuffer_rgXui8, sizeof(halImu_orientationValues));
    }

    return l_recvImuState_st;
}
