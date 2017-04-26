/*!
 * \file LLD_I2C.c
 */
#include "LLD_I2C.h"
#include <fcntl.h>          //required for open()
#include <linux/i2c-dev.h>  //coming with i2c-tools
#include <unistd.h>
#include <sys/ioctl.h>

/*!**********************************************************************
 * \author     Philipp Woditsch (phwogs00)
 * \date     2015/05/04
 * 
 * \brief    Write-function for I2C Bus
 * \details    Function for writing a byte-array on the I2C-Bus. A pointer
 *             to the byte-array and the number of payload bytes to read are
 *             required. The function ensures to write the desired bytes on
 *             the bus, including a retransmission procedure.
 * 
 * \param[in]    f_lldI2c_i2cSlaveAddress_ui8 is the address of the I2C
 *                 Slave device
 * \param[in]    f_i2cWriteBuffer_pui8 is pointer to the byte-array to
 *                 which the read bus data is written
 * \param[in]   l_i2cNumOfDataBytes_ui32 is the amount of bytes to be
 *                 written
 * \param[out]    returns the error state\n
 *                 0   ... success (no errors)\n
 *                 >=1    ... failed (some errors occured)
 * 
 * \internal
 * CHANGELOG:
 * 2015/05/13 juscgs00:
 * - Changed second function parameter to const pointer
 * - Changed function parameter names according naming syle guide (f_..)
 * - Changed global i2cFile-handler to local variable
 * - Introduced a define for the transmission retry number
 * - Introduced a define for device-file of I2C
 * - extended commenting
 *
 * 2015/05/06 phwogs00:
 * Changed variable and function names in order to guideline
 * \endinternal
 ***********************************************************************/
unsigned int g_lldI2c_WriteI2c_bool(unsigned char f_lldI2c_i2cSlaveAddress_ui8, const unsigned char* f_i2cWriteBuffer_pui8, unsigned int f_i2cNumOfDataBytes_ui32)
{
    unsigned char     l_returnOfWrittenBytes_ui8     = 0;
    unsigned char     l_WriteRetryCounter_ui8     = 0;
    unsigned int     l_i2cFile_ui32                 = 0;

    //Open I2C device
    l_i2cFile_ui32 = open(M_HAL_LLDI2C_I2C_DEV_UI8, O_RDWR);
    if(l_i2cFile_ui32 < 0)
    {
        /*ERROR HANDLER*/
        return 1;
    }

    //Specify the address of the I2C Slave to communicate with
    ioctl(l_i2cFile_ui32, I2C_SLAVE, f_lldI2c_i2cSlaveAddress_ui8);

    //Write Buffer to I2C Slave Device
    while(        (l_returnOfWrittenBytes_ui8 != f_i2cNumOfDataBytes_ui32)
            &&     (l_WriteRetryCounter_ui8 < M_HAL_LLDI2C_TRANSMISSION_RETRYNUM_UI8) )
    {
        l_returnOfWrittenBytes_ui8 = write(l_i2cFile_ui32, f_i2cWriteBuffer_pui8, f_i2cNumOfDataBytes_ui32);
        l_WriteRetryCounter_ui8++;
    }

    if(l_WriteRetryCounter_ui8 >= M_HAL_LLDI2C_TRANSMISSION_RETRYNUM_UI8)
    {
        return 1;
    }

    //Close I2C device
    close(l_i2cFile_ui32);
    if(l_i2cFile_ui32 < 0)
    {
        /*ERROR HANDLER*/
        return 1;
    }

    return 0;
}



/*!**********************************************************************
 * \author     Philipp Woditsch (phwogs00)
 * \date         2015/05/04
 * 
 * \brief    Read-function for I2C-Bus
 * \details    Function for reading data from the I2C-Bus into a byte-array.
 *             A pointer to the byte-array and the number of payload bytes
 *             to read are    required. The function ensures to write the
 *             desired bytes on the bus, including a retransmission
 *             procedure.
 * 
 * \param[in]    f_lldI2c_i2cSlaveAddress_ui8 is the Address of the I2C
 *                 Slave device in Hex
 * \param[in]    f_lldI2c_i2cReadBuffer_pui8 is a pointer to an array
 *                 where the readed data should be stored
 * \param[in]   f_i2cNumberOfReadingBytes_ui32is gives the amount of
 *                 bytes to be readed
 * \param[out]    returns the error state\n
 *                 0   ... success (no errors)\n
 *                 >=1    ... failed (some errors occured)
 * 
 * \internal
 * CHANGELOG:
 * 2015/05/13 juscgs00:
 * - Changed second function parameter to const pointer
 * - Changed function parameter names according naming syle guide (f_..)
 * - Changed global i2cFile-handler to local variable
 * - Introduced a define for the transmission retry number
 * - Introduced a define for device-file of I2C
 * - deleted some german comments
 *
 * 2015/05/06 phwogs00:
 * Changed variable and function names in order to guideline
 *   *
 * \endinternal
 ***********************************************************************/ 
unsigned int g_lldI2c_ReadI2c_bool(unsigned char f_lldI2c_i2cSlaveAddress_ui8, const unsigned char* f_lldI2c_i2cReadBuffer_pui8, unsigned int f_i2cNumOfDataBytes_ui32)
{
    unsigned char     l_ReturnOfReadBytes_ui8 = 0;
    unsigned char     l_ReadRetryCounter_ui8     = 0;
    unsigned int     l_i2cFile_ui32             = 0;

    //Open I2C device
    l_i2cFile_ui32 = open(M_HAL_LLDI2C_I2C_DEV_UI8, O_RDWR);   //Open I2C device
    if(l_i2cFile_ui32 < 0)
    {
        /*ERROR HANDLER*/
        return 1;
    }

    //Specify the address of the I2C Slave to communicate with
    ioctl(l_i2cFile_ui32, I2C_SLAVE, f_lldI2c_i2cSlaveAddress_ui8);

    while(        (l_ReturnOfReadBytes_ui8 != f_i2cNumOfDataBytes_ui32)
            &&     (l_ReadRetryCounter_ui8 < M_HAL_LLDI2C_TRANSMISSION_RETRYNUM_UI8) )
    {
        l_ReturnOfReadBytes_ui8 = read(l_i2cFile_ui32, (void *)f_lldI2c_i2cReadBuffer_pui8, f_i2cNumOfDataBytes_ui32);
        l_ReadRetryCounter_ui8++;
    }

    if(l_ReadRetryCounter_ui8 >= M_HAL_LLDI2C_TRANSMISSION_RETRYNUM_UI8)
    {
        return 1;
    }

    //Close I2C device
    close(l_i2cFile_ui32);
    if(l_i2cFile_ui32 < 0)
    {
        /*ERROR HANDLER*/
        return 1;
    }
    return(0);

}


/****************************************************************************/
/*                    I2C-0 bus functions following                         */
/****************************************************************************/

/*!**********************************************************************
 * \author     Philipp Woditsch (phwogs00)
 * \date     2015/06/21
 * 
 * \brief    Write-function for I2C0 Bus
 * \details    Function for writing a byte-array on the I2C-Bus. A pointer
 *             to the byte-array and the number of payload bytes to read are
 *             required. The function ensures to write the desired bytes on
 *             the bus, including a retransmission procedure.
 * 
 * \param[in]    f_lldI2c_i2cSlaveAddress_ui8 is the address of the I2C
 *                 Slave device
 * \param[in]    f_i2cWriteBuffer_pui8 is pointer to the byte-array to
 *                 which the read bus data is written
 * \param[in]   l_i2cNumOfDataBytes_ui32 is the amount of bytes to be
 *                 written
 * \param[out]    returns the error state\n
 *                 0   ... success (no errors)\n
 *                 >=1    ... failed (some errors occured)
 * 
 * \internal
 * CHANGELOG:
 *
 * 
 * \endinternal
 ***********************************************************************/
unsigned int g_lldI2c_WriteI2c0_bool(unsigned char f_lldI2c_i2cSlaveAddress_ui8, const unsigned char* f_i2cWriteBuffer_pui8, unsigned int f_i2cNumOfDataBytes_ui32)
{
    unsigned char     l_returnOfWrittenBytes_ui8     = 0;
    unsigned char     l_WriteRetryCounter_ui8     = 0;
    unsigned int     l_i2cFile_ui32                 = 0;

    //Open I2C device
    l_i2cFile_ui32 = open(M_HAL_LLDI2C_I2C0_DEV_UI8, O_RDWR);
    if(l_i2cFile_ui32 < 0)
    {
        /*ERROR HANDLER*/
        return 1;
    }

    //Specify the address of the I2C Slave to communicate with
    ioctl(l_i2cFile_ui32, I2C_SLAVE, f_lldI2c_i2cSlaveAddress_ui8);

    //Write Buffer to I2C Slave Device
    while(        (l_returnOfWrittenBytes_ui8 != f_i2cNumOfDataBytes_ui32)
            &&     (l_WriteRetryCounter_ui8 < M_HAL_LLDI2C_TRANSMISSION_RETRYNUM_UI8) )
    {
        l_returnOfWrittenBytes_ui8 = write(l_i2cFile_ui32, f_i2cWriteBuffer_pui8, f_i2cNumOfDataBytes_ui32);
        l_WriteRetryCounter_ui8++;
    }

    if(l_WriteRetryCounter_ui8 >= M_HAL_LLDI2C_TRANSMISSION_RETRYNUM_UI8)
    {
        return 1;
    }

    //Close I2C device
    close(l_i2cFile_ui32);
    if(l_i2cFile_ui32 < 0)
    {
        /*ERROR HANDLER*/
        return 1;
    }

    return 0;
}



/*!**********************************************************************
 * \author     Philipp Woditsch (phwogs00)
 * \date         2015/06/21
 * 
 * \brief    Read-function for I2C0-Bus
 * \details    Function for reading data from the I2C-Bus into a byte-array.
 *             A pointer to the byte-array and the number of payload bytes
 *             to read are    required. The function ensures to write the
 *             desired bytes on the bus, including a retransmission
 *             procedure.
 * 
 * \param[in]    f_lldI2c_i2cSlaveAddress_ui8 is the Address of the I2C
 *                 Slave device in Hex
 * \param[in]    f_lldI2c_i2cReadBuffer_pui8 is a pointer to an array
 *                 where the readed data should be stored
 * \param[in]   f_i2cNumberOfReadingBytes_ui32is gives the amount of
 *                 bytes to be readed
 * \param[out]    returns the error state\n
 *                 0   ... success (no errors)\n
 *                 >=1    ... failed (some errors occured)
 * 
 * \internal
 * CHANGELOG:
 * 
 * 
 *  * \endinternal
 ***********************************************************************/ 
unsigned int g_lldI2c_ReadI2c0_bool(unsigned char f_lldI2c_i2cSlaveAddress_ui8, const unsigned char* f_lldI2c_i2cReadBuffer_pui8, unsigned int f_i2cNumOfDataBytes_ui32)
{
    unsigned char     l_ReturnOfReadBytes_ui8 = 0;
    unsigned char     l_ReadRetryCounter_ui8     = 0;
    unsigned int     l_i2cFile_ui32             = 0;

    //Open I2C device
    l_i2cFile_ui32 = open(M_HAL_LLDI2C_I2C0_DEV_UI8, O_RDWR);   //Open I2C device
    if(l_i2cFile_ui32 < 0)
    {
        /*ERROR HANDLER*/
        return 1;
    }

    //Specify the address of the I2C Slave to communicate with
    ioctl(l_i2cFile_ui32, I2C_SLAVE, f_lldI2c_i2cSlaveAddress_ui8);

    while(        (l_ReturnOfReadBytes_ui8 != f_i2cNumOfDataBytes_ui32)
            &&     (l_ReadRetryCounter_ui8 < M_HAL_LLDI2C_TRANSMISSION_RETRYNUM_UI8) )
    {
        l_ReturnOfReadBytes_ui8 = read(l_i2cFile_ui32, (void *)f_lldI2c_i2cReadBuffer_pui8, f_i2cNumOfDataBytes_ui32);
        l_ReadRetryCounter_ui8++;
    }

    if(l_ReadRetryCounter_ui8 >= M_HAL_LLDI2C_TRANSMISSION_RETRYNUM_UI8)
    {
        return 1;
    }

    //Close I2C device
    close(l_i2cFile_ui32);
    if(l_i2cFile_ui32 < 0)
    {
        /*ERROR HANDLER*/
        return 1;
    }
    return(0);

}
