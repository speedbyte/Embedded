/*!
 * \file accMag.c
 */
#include "../../LLD_IF/LLD_I2C.h"
#include "accMag.h"

#include<limits.h>

/*!
 *  acceleration state and compass state in one container
 */
static halAccmag_dataContainer m_halAccmag_sensorState_st;

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/05
 *
 * \brief    Wrapper function to read a single byte register of LSM303D
 * \details    This function is a wrapper to the I2C Interface to read one
 *             single byte of the Accelerometer/Magnetometer (LSM303D). It
 *             eases the write and read procedure for reading one register
 *             byte of the sensor.
 *
 *     \param[in]    f_registerAddr_ui8 specifies the register address to
 *                 return
 *     \param[out] returns the requested byte of I2C data
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
static inline unsigned char l_readI2cByte_ui8( unsigned char f_registerAddr_ui8 )
{
    unsigned char    l_registerAddr_ui8 = 0;
    unsigned char    l_recvDataByte_ui8 = 0;

    /*
     * ensure single byte read (MSB of register address shall be 0)
     * -> Mask MSB to zero!
     */
    l_registerAddr_ui8 = f_registerAddr_ui8 & 0b01111111;

    //write register request to I2C
    if ( g_lldI2c_WriteI2c_bool(M_HAL_ACCMAG_I2CADDR_UI8, &l_registerAddr_ui8, 1) != M_HAL_ACCMAG_SUCCESS_BOOL )
    {
        // error in I2C access
        return M_HAL_ACCMAG_FAILED_BL;
    }

    //read requested register data
    if ( g_lldI2c_ReadI2c_bool(M_HAL_ACCMAG_I2CADDR_UI8, &l_recvDataByte_ui8, 1) != M_HAL_ACCMAG_SUCCESS_BOOL )
    {
        // error in I2C access
        return M_HAL_ACCMAG_FAILED_BL;
    }

    return l_recvDataByte_ui8;
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/08
 *
 * \brief    Wrapper function to read byte stream to registers of LSM303D
 * \details    This function is a wrapper to the I2C Interface to read a
 *             byte stream to a series of registers of the Accelerometer/
 *             Magnetometer (LSM303D). The first register address can be
 *             defined in the parameter list of the function. After reading
 *             the first byte of the start address, the register address
 *             will be incremented.
 *
 *     \param[in]    f_startRegisterAddr_ui8    specifies the first register
 *                 address to return
 *     \param[in]  f_readDestinationBuffer_pui8 points to an array of
 *                 unsigned 8bit integer elements. This array receives all
 *                 read data bytes (output byte stream buffer).
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
static inline unsigned int l_readI2cByteStream_bool( unsigned char f_startRegisterAddr_ui8, const unsigned char* f_readDestinationBuffer_pui8, unsigned int f_numOfBytesToRead_ui32 )
{
    unsigned char    l_registerAddr_ui8     = 0;

    // ensure at least one data byte to read
    if (f_numOfBytesToRead_ui32 < 1)
    {
        return M_HAL_ACCMAG_FAILED_BL;
    }

    /*
     * ensure byte stream reading (MSB of register address shall be 1)
     *   -> Mask MSB to one!
     *   -> LSM303D will auto-increment the register address for each byte
     *      of data
     */
    l_registerAddr_ui8 = f_startRegisterAddr_ui8 | 0b10000000;

    //write register request to I2C
    if ( g_lldI2c_WriteI2c_bool(M_HAL_ACCMAG_I2CADDR_UI8, &l_registerAddr_ui8, 1) != M_HAL_ACCMAG_SUCCESS_BOOL )
    {
        // error in I2C access
        return M_HAL_ACCMAG_FAILED_BL;
    }

    //read requested registers to I2C
    if ( g_lldI2c_ReadI2c_bool(M_HAL_ACCMAG_I2CADDR_UI8, f_readDestinationBuffer_pui8, f_numOfBytesToRead_ui32) != M_HAL_ACCMAG_SUCCESS_BOOL )
    {
        // error in I2C access
        return M_HAL_ACCMAG_FAILED_BL;
    }

    return M_HAL_ACCMAG_SUCCESS_BL;
}

//
//// BEGIN: DISABLED CODE
//// --> not used function
//// ----> not deleted for completeness
//// ----> uncommented to compile only necessary code
//
///*!**********************************************************************
// * \author     Juergen Schmidt (juscgs00)
// * \date     2014/05/05
// *
// * \brief    Wrapper function to write a single byte register of LSM303D
// * \details    This function is a wrapper to the I2C Interface to write one
// *             single byte to a register of the Accelerometer/Magnetometer
// *             (LSM303D). It eases the concatenation of register address and
// *             data byte to transmit.
// *
// *     \param[in]    f_registerAddr_ui8    specifies the register address to
// *                 return
// *     \param[in]  f_byteToWrite_ui8     specifies the single byte to write
// *     \param[out] returns a boolean value, indicating the occurrence of
// *                 failures\n
// *                 0 .... indicates success (no errors)\n
// *                 1 .... indicates failed (some errors)
// *
// * \internal
// * CHANGELOG:
// * none
// * \endinternal
// ***********************************************************************/
//static inline unsigned int l_writeI2cByte_bool( unsigned char f_registerAddr_ui8, unsigned char f_byteToWrite_ui8 )
//{
//    unsigned int    l_writeSucceeded_bool     = M_HAL_ACCMAG_SUCCESS_BL; // success state as default
//    unsigned char    l_writeBuffer_rg2ui8[2];
//
//    /*
//     * prepare data to write (register + data)
//     * + ensure single byte writing (MSB of register address shall be 0)
//     *   -> Mask MSB to zero!
//     */
//    l_writeBuffer_rg2ui8[0] = f_registerAddr_ui8 & 0b01111111;
//    l_writeBuffer_rg2ui8[1] = f_byteToWrite_ui8;
//
//    //write register to I2C
//    if ( g_lldI2c_WriteI2c_bool(M_HAL_ACCMAG_I2CADDR_UI8, l_writeBuffer_rg2ui8, 2) == M_HAL_ACCMAG_FAILED_BOOL )
//    {
//        // error in I2C access
//        l_writeSucceeded_bool = M_HAL_ACCMAG_FAILED_BL;
//    }
//
//    return l_writeSucceeded_bl;
//}
//
//// END: DISABLED CODE
//


/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/08
 *
 * \brief    Wrapper function to write byte stream to registers of LSM303D
 * \details    This function is a wrapper to the I2C Interface to write a
 *             byte stream to a series of registers of the Accelerometer/
 *             Magnetometer (LSM303D). The first register address can be
 *             defined in the parameter list of the function. After writing
 *             the first byte to the start address, the register address
 *             will be incremented.
 *
 *     \param[in]    f_startRegisterAddr_ui8    specifies the first register
 *                 address to return
 *     \param[in]  f_byteStreamToWrite_pui8 points to an array of unsigned
 *                 8bit data elements (input byte stream buffer)
 *     \param[out] returns a boolean value, indicating the occurrence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * 2015/05/13 juscgs00:
 * - changed malloc/free approach to fixed size array (with define to set
 *   size of array in header)
 * \endinternal
 ***********************************************************************/
static inline unsigned int l_writeI2cByteStream_bool( unsigned char f_startRegisterAddr_ui8, const unsigned char* const f_byteStreamToWrite_pui8, unsigned int f_numOfBytes_ui32 )
{
    unsigned int    l_writeSucceeded_bool     = M_HAL_ACCMAG_SUCCESS_BL;     // success state as default
    unsigned char     l_bufCtr_ui8            = 0;                        // loop counter to assemble payload and register address
    unsigned char    l_byteStreamBuffer_rgXui8[M_HAL_ACCMAG_WRITE_BYTESTREAM_BUFFER_SIZE_UI8];
    /*
     * - ensure at least one data byte to write
     * - prevent a buffer overflow of l_byteStreamBuffer_rgXui8
     *   --> payload data bytes + register address (subaddress)
     */
    if (         (f_numOfBytes_ui32 < 1)
            ||  (f_numOfBytes_ui32 > M_HAL_ACCMAG_WRITE_BYTESTREAM_BUFFER_SIZE_UI8-1) )
    {
        return M_HAL_ACCMAG_FAILED_BL;
    }

    /*
     * prepare data to write (register + data)
     * (1) ensure byte stream writing (MSB of register address shall be 1)
     *     -> Mask MSB to one!
     *     -> LSM303D will auto-increment the register address for each byte
     *        of data
     * (2) copy data to write to local buffer, start at second byte position
     *     (first byte position is the register address)
     */
    l_byteStreamBuffer_rgXui8[0] = f_startRegisterAddr_ui8 | 0b10000000;
    for(l_bufCtr_ui8=0; l_bufCtr_ui8 < f_numOfBytes_ui32; l_bufCtr_ui8++)
    {
        l_byteStreamBuffer_rgXui8[l_bufCtr_ui8+1] = f_byteStreamToWrite_pui8[l_bufCtr_ui8];
    }

    //write register to I2C
    if ( g_lldI2c_WriteI2c_bool(M_HAL_ACCMAG_I2CADDR_UI8, l_byteStreamBuffer_rgXui8, f_numOfBytes_ui32 + 1) != M_HAL_ACCMAG_SUCCESS_BOOL )
    {
        // error in I2C access
        l_writeSucceeded_bool = M_HAL_ACCMAG_FAILED_BL;
    }

    return l_writeSucceeded_bl;
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/10
 *
 * \brief    Complement of twos of a 16 bit integer
 * \details    This function computes the two's complement of two 8bit
 *             integers (most significant and least significant bytes)
 *
 *     \param[in]    f_lsb_ui8 is the least significant byte
 *     \param[in]    f_msb_ui8 is the most significant byte
 *     \param[out] returns a unsigned 16bit integer of the two's complement
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
static inline signed short l_twoCompOf16Bit_ui16( unsigned char f_lsb_ui8, unsigned char f_msb_ui8 )
{
    signed short    l_compOfTwo_ui16 = 0; //init variable with zeros

    /*
     * 1. assemble 16bit value of two 8bit chunks
     * 2. invert 16bit
     * 3. add 1 to 16bit value
     * 4. mask only 16bit range (to avoid overflows)
     * --> conversion of two's complement
     */
    l_compOfTwo_ui16 = (signed short)( ( ~((int)(f_msb_ui8 << 8) + (int)(f_lsb_ui8)) + (int)1 ) & (int)0xFFFF );

    return l_compOfTwo_ui16;
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/11
 *
 * \brief    Converts raw sensor values of the magnetometer into SI unit
 * \details    This function converts the raw sensor values (signed 16bit
 *             integers)of the magnetometer into SI unit (64bit float). The
 *             unit for the magnetometer is Tesla\n
 *             (SI representation: Tesla = \f[ \frac{kg}{s^2\dotA} \f])
 *
 *     \param[in]    f_rawMagVal_i16 is raw signed 16bit sensor value
 *     \param[in]    f_scalingValue_ui8 is the absolute value of the scale
 *                 defined maximal sensor value range (e.g. "+/-4 Gauss" will
 *                 result in "4")
 *     \param[out] returns a 64bit float value in SI units\n
 *                 (Tesla = \f[ \frac{kg}{s^2\dotA} \f])
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
static inline double l_convertMagRawToSIUnit_f64( signed short f_rawMagVal_i16, unsigned char f_scalingValueGauss_ui8 )
{
    double            l_outputValue_f64 = 0;
    const double    l_gaussToSI_f64 = 0.1E-3;    //1Gauss = 0.1mT = 0.1*10^(-3)T

    // unitless [-1,1]
    l_outputValue_f64 = (double)f_rawMagVal_i16 / (double)SHRT_MAX;

    // Units: 1 * T*Gauss^(-1) * Gauss = m*s^(-2)
    l_outputValue_f64 = l_outputValue_f64 * l_gaussToSI_f64 * (double)f_scalingValueGauss_ui8;

    return l_outputValue_f64;    //Tesla
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/11
 *
 * \brief    Converts raw sensor values of the accelerometer into SI unit
 * \details    This function converts the raw sensor values (signed 16bit
 *             integers)of the accelerometer into SI unit (64bit float). The
 *             unit for the accelerometer is \f[ \frac{m}{s^2} \f]
 *
 *     \param[in]    f_rawMagVal_i16 is raw signed 16bit sensor value
 *     \param[in]    f_scalingValue_ui8 is the absolute value of the max. scale
 *                 defined in the sensor's control registers.\n
 *                 Example: maximal sensor range "+/- 8G" will    result in "8"
 *     \param[out] returns a 64bit float value in SI units (\f[ \frac{m}{s^2} \f])
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
static inline double l_convertAccRawToSIUnit_f64( signed short f_rawAccVal_i16, unsigned char f_scalingValueG_ui8 )
{
    double            l_outputValue_f64     = 0;
    const double    l_gravityConst_f64     = 9.81; // m*(s^-2) per G

    // unitless [-1,1]
    l_outputValue_f64 = (double)f_scalingValueG_ui8 * (double)f_rawAccVal_i16 / (double)SHRT_MAX;

    // Units: 1 * m*s^(-2)*G^(-1) * G = m*s^(-2)
    l_outputValue_f64 = l_outputValue_f64 * l_gravityConst_f64;

    return l_outputValue_f64;  // m*(s^-2)
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/05
 *
 * \brief    Trigger a update of the current sensor state data
 * \details    This function accesses the accelereation and compass sensor
 *             via I2C to load a new measurement to the sensor state storage
 *
 * \param[in]    f_sensor_en is a enum type that indicates, which sensor(s)
 *                 shall be updated
 * \param[out]    returns a boolean value, indicating the occurrence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
static inline unsigned int l_updateSensorState_vd( halAccmag_sensorSelect f_sensor_en )
{
    halAccmag_3dDoubleVector    l_accBuffer_st;
    halAccmag_3dDoubleVector    l_magBuffer_st;
    unsigned char                l_readBuffer_rg6ui8[6];
    signed short                l_tempComponent_i16 = 0;
    unsigned int                l_successState_bool = M_HAL_ACCMAG_SUCCESS_BL;

    //init local data buffers with current values
    l_accBuffer_st = m_halAccmag_sensorState_st.acc;
    l_magBuffer_st = m_halAccmag_sensorState_st.mag;

    /*
     * READ ACCELEROMETER
     * - uses sequential read (auto-increment)
     * - sequence as follows:
     *   (Byte 1) X-Component, LSB
     *   (Byte 2) X-Component, MSB
     *   (Byte 3) Y-Component, LSB
     *   (Byte 4) Y-Component, MSB
     *   (Byte 5) Z-Component, LSB
     *   (Byte 6) Z-Component, MSB
     */
    if ( (f_sensor_en == SENSOR_ACC_EN) || (f_sensor_en == SENSOR_BOTH_EN) )
    {
        if ( l_readI2cByteStream_bool(M_HAL_ACCMAG_OUT_X_L_A_UI8,l_readBuffer_rg6ui8, 6) == M_HAL_ACCMAG_SUCCESS_BOOL )
        {
            // x-component
            l_tempComponent_i16 = l_twoCompOf16Bit_ui16(l_readBuffer_rg6ui8[0], l_readBuffer_rg6ui8[1]);
            l_accBuffer_st.x_f64 = l_convertAccRawToSIUnit_f64( l_tempComponent_i16, M_HAL_ACCMAG_ACCSCALE_UI8 );

            // y-component
            l_tempComponent_i16 = l_twoCompOf16Bit_ui16(l_readBuffer_rg6ui8[2], l_readBuffer_rg6ui8[3]);
            l_accBuffer_st.y_f64 = l_convertAccRawToSIUnit_f64( l_tempComponent_i16, M_HAL_ACCMAG_ACCSCALE_UI8 );

            // z-component
            l_tempComponent_i16 = l_twoCompOf16Bit_ui16(l_readBuffer_rg6ui8[4], l_readBuffer_rg6ui8[5]);
            l_accBuffer_st.z_f64 = l_convertAccRawToSIUnit_f64( l_tempComponent_i16, M_HAL_ACCMAG_ACCSCALE_UI8 );
        }else{
            l_successState_bool = M_HAL_ACCMAG_FAILED_BL;
        }

    }
    /*
     * READ MAGNETOMETER
     * - uses sequential read (auto-increment)
     * - sequence as follows:
     *   (Byte 1) X-Component, LSB
     *   (Byte 2) X-Component, MSB
     *   (Byte 3) Y-Component, LSB
     *   (Byte 4) Y-Component, MSB
     *   (Byte 5) Z-Component, LSB
     *   (Byte 6) Z-Component, MSB
     */
    if ( (f_sensor_en == SENSOR_MAG_EN) || (f_sensor_en == SENSOR_BOTH_EN) )
    {
        if ( l_readI2cByteStream_bool(M_HAL_ACCMAG_OUT_X_L_M_UI8,l_readBuffer_rg6ui8, 6) == M_HAL_ACCMAG_SUCCESS_BOOL )
        {
            // x-component
            l_tempComponent_i16 = l_twoCompOf16Bit_ui16(l_readBuffer_rg6ui8[0], l_readBuffer_rg6ui8[1]);
            l_magBuffer_st.x_f64 = l_convertMagRawToSIUnit_f64( l_tempComponent_i16, M_HAL_ACCMAG_MAGSCALE_UI8 );

            // y-component
            l_tempComponent_i16 = l_twoCompOf16Bit_ui16(l_readBuffer_rg6ui8[2], l_readBuffer_rg6ui8[3]);
            l_magBuffer_st.y_f64 = l_convertMagRawToSIUnit_f64( l_tempComponent_i16, M_HAL_ACCMAG_MAGSCALE_UI8 );

            // z-component
            l_tempComponent_i16 = l_twoCompOf16Bit_ui16(l_readBuffer_rg6ui8[4], l_readBuffer_rg6ui8[5]);
            l_magBuffer_st.z_f64 = l_convertMagRawToSIUnit_f64( l_tempComponent_i16, M_HAL_ACCMAG_MAGSCALE_UI8 );
        }else{
            l_successState_bool = M_HAL_ACCMAG_FAILED_BL;
        }
    }

    // update sensor state storage values
    m_halAccmag_sensorState_st.acc = l_accBuffer_st;
    m_halAccmag_sensorState_st.mag = l_magBuffer_st;

    return l_successState_bl;
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/05
 *
 * \brief    Initialize sensor
 * \details    Sends all commands on I2C to initialize the acc.- and
 *             magnetometer. It uses on big 8 byte config buffer to set all
 *             necessary bits. This way, a burst write to the control
 *             registers of LSM303D is performed to reduce the I2C bus load.
 *
 * \param[out]    returns a boolean value, indicating the occurrence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halAccmag_initSensor_bool(void)
{
    unsigned char l_configRegisters_rg8ui8[8];    //buffer for 8 control register bytes

    //Identify sensor
    if ( l_readI2cByte_ui8( M_HAL_ACCMAG_WHO_AM_I_UI8 ) != M_HAL_ACCMAG_WHO_AM_I_PATTERN_UI8 )
    {
        // sensor could not be identified --> abort initialization
        return M_HAL_ACCMAG_FAILED_BL;
    }

    /*
     * ACCELEROMETER
     */
    // CTRL0: no FIFO (default values)
    l_configRegisters_rg8ui8[0] = 0b00000000;

    // CTRL1: Enable accelerometer, 800Hz sampling
    l_configRegisters_rg8ui8[1] = (        M_HAL_ACCMAG_CTRL1_MASK_AXEN_UI8
            |     M_HAL_ACCMAG_CTRL1_MASK_AYEN_UI8
            |    M_HAL_ACCMAG_CTRL1_MASK_AZEN_UI8
            |     M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_800HZ_UI8);

    // CTRL2 register (default values): Set scale +/-8G (accelerometer) & Anti-Alias-Filter ~200Hz
    l_configRegisters_rg8ui8[2] = (     M_HAL_ACCMAG_CTRL2_MASK_ACC_SCALE_8G_UI8
                                    |     M_HAL_ACCMAG_CTRL2_MASK_ACC_BANDWIDTH_194HZ_UI8 );

    // CTRL3 register (default values): Disable all interrupts
    l_configRegisters_rg8ui8[3] = 0b00000000;

    //CTRL4 register (default values)
    l_configRegisters_rg8ui8[4] = 0b00000000;

    /*
     * MAGNETOMETER
     */
    // CTRL5 register: Disable Temp.-sensor, set high-resolution, set 100Hz data rate
    l_configRegisters_rg8ui8[5] = (        M_HAL_ACCMAG_CTRL5_MASK_MAG_RES_HIGH_UI8
            |     M_HAL_ACCMAG_CTRL5_MASK_MAG_RATE_100HZ_UI8 );

    // CTRL6 register: set scale +/-0.4mT
    l_configRegisters_rg8ui8[6] = M_HAL_ACCMAG_CTRL6_MASK_MAG_SCALE_4GAUSS_UI8;

    // CTRL7 register (default values): set continuous-conversion mode (magnetometer)
    l_configRegisters_rg8ui8[7] = M_HAL_ACCMAG_CTRL7_MASK_MAG_SENSMODE_CONTINOUS_UI8;


    // send config
    if ( l_writeI2cByteStream_bool(M_HAL_ACCMAG_CTRL0_UI8, l_configRegisters_rg8ui8, sizeof(l_configRegisters_rg8ui8) ) == M_HAL_ACCMAG_FAILED_BOOL )
    {
        // setting register CTRL1 failed
        return M_HAL_ACCMAG_FAILED_BL;
    }

    return M_HAL_ACCMAG_SUCCESS_BL;
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/13
 *
 * \brief    Trigger a new measurement of the accelerometer
 * \details    .
 *
 * \param[out]    returns a boolean value, indicating the occurrence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halAccmag_triggerAccUpdate_bool( void )
{
    return l_updateSensorState_vd(SENSOR_ACC_EN);
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/13
 *
 * \brief    Trigger a new measurement of the magnetometer
 * \details    .
 *
 * \param[out]    returns a boolean value, indicating the occurrence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halAccmag_triggerMagUpdate_bool( void )
{
    return l_updateSensorState_vd(SENSOR_MAG_EN);
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/13
 *
 * \brief    Trigger a new measurement of both sensors
 * \details    .
 *
 * \param[out]    returns a boolean value, indicating the occurrence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halAccmag_triggerFullUpdate_bool( void )
{
    return l_updateSensorState_vd(SENSOR_BOTH_EN);
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/05
 *
 * \brief    Get current state of acceleration
 * \details    This function returns the current state of the accelerometer.\n
 *             Attention: To retrieve a new measurement the measurement
 *             trigger is to be called first!
 *
 * \param[out]    3D vector of acceleration components (x,y,z)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
halAccmag_3dDoubleVector g_halAccmag_getAccVector_st( void )
{
    return m_halAccmag_sensorState_st.acc;
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/05
 *
 * \brief    Get current state of compass
 * \details    This function returns the current state of the magnetometer.\n
 *             Attention: To retrieve a new measurement the measurement
 *             trigger is to be called first!
 *
 * \param[out]    3D vector of compass components (x,y,z)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
halAccmag_3dDoubleVector g_halAccmag_getMagVector_st( void )
{
    return m_halAccmag_sensorState_st.mag;
}

/*!**********************************************************************
 * \author     Juergen Schmidt (juscgs00)
 * \date     2014/05/05
 *
 * \brief    Get complete data container (acceleration & compass)
 * \details    This function returns the complete accelerometer and
 *             magnetometer state. Attention: To retrieve a new measurement
 *             a measurement trigger is to be called first!
 *
 * \param[out]    Container with compass and acceleration data
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
halAccmag_dataContainer    g_halAccmag_getAccMagContainer_st( void )
{
    return m_halAccmag_sensorState_st;
}
