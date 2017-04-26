/*!
 * \file LIDAR.c
 */

#include "../LLD_IF/LLD_I2C.h"
#include "LIDAR.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

// Readable Var
static double m_distance_f64;

/*!**********************************************************************
 * \author Philipp Woditsch ( phwogs00 )
 * \date 2015/06/21
 *
 * \brief get Distance from LIDAR Laser Sensor
 * \details Interface to read Distance measured by LIDAR Lite Laser Sensor
 * 
 *
 *
 * \param[ in ] no parameter
 * \param[ out ] distance of Laser Sensor
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */

double g_LIDAR_getDistance_f64(void)
{
    return m_distance_f64;
}


/*!**********************************************************************
 * \author Philipp Woditsch ( phwogs00 )
 * \date 2015/06/21
 *
 * \brief Trigger I2C transfer
 * \details Trigger Distance transfer from LIDAR to HAL
 *
 * \param[ in ] no parameter
 * \param[ out ] succeeded
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */

int g_LIDAR_readDistanceFromI2C_i32(void)
{
unsigned char l_ReadBuffer_ui8[2]={0,0};
unsigned char l_WriteBuffer_ui8[2]={0,0};
int l_DistInCm_i32 =  0;

//Trigger Measurement of Distance (DC stabnilization cycle, Signal Acquisition, DataProcessing)
l_WriteBuffer_ui8[0]=0x00;                                 //write Reg 0x00
l_WriteBuffer_ui8[1]=0x04;                                 //with value 0x04
if(g_lldI2c_WriteI2c0_bool(M_I2C_SLAVE_ADDRESS_LIDAR_UI8, l_WriteBuffer_ui8, 2)!=0)
{
return -1;
}

//Waiting Time for Acquisition
usleep(20*1000);


//Set Acquisition count cycle to 255
l_WriteBuffer_ui8[0]=0x02;
l_WriteBuffer_ui8[1]=0xFF;
if(g_lldI2c_WriteI2c0_bool(M_I2C_SLAVE_ADDRESS_LIDAR_UI8, l_WriteBuffer_ui8, 2)!=0)
{
return -1;
}

//Set Reg 0x8f as Output-Register
l_WriteBuffer_ui8[0]=0x8f;
if(g_lldI2c_WriteI2c0_bool(M_I2C_SLAVE_ADDRESS_LIDAR_UI8, l_WriteBuffer_ui8, 1)!=0)
{
return -1;
}

//Read 2-Byte Distance in cm from Register 0x8f
if(g_lldI2c_ReadI2c0_bool(M_I2C_SLAVE_ADDRESS_LIDAR_UI8, (l_ReadBuffer_ui8), 2)!=0)
{
return -1;
}

//Conversion from int(cm) to double(m)
l_DistInCm_i32 = *l_ReadBuffer_ui8 << 8;
l_DistInCm_i32 |= *(l_ReadBuffer_ui8+1);
m_distance_f64 = (double)l_DistInCm_i32;
m_distance_f64 = (m_distance_f64/100);
//printf("Distance: %d / %.2f\n",l_DistInCm_i32,m_distance_f64);
//usleep(500*1000);


return 0;
}
