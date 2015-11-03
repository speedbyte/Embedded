/*!
 * \file LIDAR.h
 */
/*
 * LIDAR.h
 *
 *  Created on: 2015/06/21
 *      Author: phwogs00
 */

#ifndef LIDAR_H_
#define LIDAR_H_

// 7 Bit I2C Slave address
#define M_I2C_SLAVE_ADDRESS_LIDAR_UI8 0x62  


double g_LIDAR_getDistance_f64(void);
int g_LIDAR_readDistanceFromI2C_i32(void);


#endif /*LIDAR*/