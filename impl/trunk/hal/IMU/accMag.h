/*!
 * \file accMag.h
 */
#ifndef HAL_ACCMAG_H
#define HAL_ACCMAG_H

#include "accMag_registers.h"

// Replacement for boolean states
#define M_HAL_ACCMAG_TRUE_BL							1
#define M_HAL_ACCMAG_FALSE_BL							0

#define M_HAL_ACCMAG_SUCCESS_BL							0
#define M_HAL_ACCMAG_FAILED_BL							1

#define M_HAL_ACCMAG_WRITE_BYTESTREAM_BUFFER_SIZE_UI8	12		//!< defines the local write buffer of function l_writeI2cByteStream_bl

#define M_HAL_ACCMAG_ACCSCALE_UI8						8		//!< defines the defined scale of the accelerometer [m*s^(-2)]
#define M_HAL_ACCMAG_MAGSCALE_UI8						4		//!< defines the defined scale of the magnetometer [0.1*mT]
#define	M_HAL_ACCMAG_I2CADDR_UI8						0x1E	//!< I2C chip address of LSM303D (Acceleration & Compass sensor)

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/05
 *
 * \brief	3D vector of floats for x,y,z axes of sensors
 * \details	To store the 3D-components of the sensor data, a dedicated
 * 			type is declared. Every component is given in float (single
 * 			precision).
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
typedef struct{
	double	x_f64;	//!< x-component of a 3D vector data
	double	y_f64;	//!< y-component of a 3D vector data
	double	z_f64;	//!< z-component of a 3D vector data
} halAccmag_3dDoubleVector;

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/05
 *
 * \brief	Container for Acc. and Compass data
 * \details	Since the used chip (LSM303D) consists of an acceleration
 * 			sensor and a compass sensor, both data sets shall be kept in
 * 			one container.
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
typedef struct{
	halAccmag_3dDoubleVector	acc;		//!< acceleration data, SI-unit: m*s^(-2)
	halAccmag_3dDoubleVector	mag;		//!< compass data, SI-unit: kg*s^(-2)*A^(-1) (Tesla)
} halAccmag_dataContainer;

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/13
 *
 * \brief	Enumeration to choose accelerometer or magnetometer or both
 * \details	.
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
typedef enum{
	SENSOR_ACC_EN,		//!< element to indicate a update of only accelerometer
	SENSOR_MAG_EN,		//!< element to indicate a update of only magnetometer
	SENSOR_BOTH_EN		//!< element to indicate a update of both sensors
} halAccmag_sensorSelect;

/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/05/05
 *
 * DESCRIPTION:
 * Interfaces to initialize the sensor
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
unsigned int g_halAccmag_initSensor_bl(void);

/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/05/05
 *
 * DESCRIPTION:
 * Interfaces to trigger a new measurement
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
unsigned int g_halAccmag_triggerAccUpdate_bl( void );
unsigned int g_halAccmag_triggerMagUpdate_bl( void );
unsigned int g_halAccmag_triggerFullUpdate_bl( void );

/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/05/05
 *
 * DESCRIPTION:
 * Interfaces access acceleration or compass data (3D vectors)
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
halAccmag_3dDoubleVector	g_halAccmag_getAccVector_st( void );
halAccmag_3dDoubleVector	g_halAccmag_getMagVector_st( void );

/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/05/05
 *
 * DESCRIPTION:
 * Interfaces to access the complete measurement state (data container)
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
halAccmag_dataContainer	g_halAccmag_getAccMagContainer_st( void );

#endif //HAL_ACCMAG_H
