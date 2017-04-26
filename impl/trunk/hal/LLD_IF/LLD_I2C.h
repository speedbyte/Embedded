/*!
 * \file LLD_I2C.h
 */
#ifndef LLD_I2C_H_
#define LLD_I2C_H_

/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/05/13
 *
 * DESCRIPTION:
 * Defines to parameterize the I2C-Interface
 *
 * CHANGELOG:
 * 2015/06/21 phwogs00:
 * - added dev-handler for second I2C Bus
 * -------------------------------------------------------------------- */
#define	M_HAL_LLDI2C_TRANSMISSION_RETRYNUM_UI8	3				//!< defines the number of transmission retries on the I2C bus
#define	M_HAL_LLDI2C_I2C_DEV_UI8				"/dev/i2c-1"	//!< defines the dev handler for the I2C1 bus
#define	M_HAL_LLDI2C_I2C0_DEV_UI8				"/dev/i2c-0"  //!< defines the dev handler for the I2C0 bus

/* -----------------------------------------------------------------------
 * AUTHOR: Philipp Woditsch (phwogs00)
 * DATE OF CREATION: 2015/05/04
 *
 * DESCRIPTION:
 * Interface to access I2C
 *
 * CHANGELOG:
 * 2015/06/21 phwogs00:
 * - added functions for 2nd I2C Bus  
 *  
 * 2015/05/13 juscgs00:
 * - changed sencond function parameters to const pointer
 *
 * 2015/04/05 phwogs00:
 * Write Changelog entry to remember correct syntax
 * -------------------------------------------------------------------- */
unsigned int g_lldI2c_WriteI2c_bool(unsigned char, const unsigned char*, unsigned int);
unsigned int g_lldI2c_ReadI2c_bool(unsigned char, const unsigned char*, unsigned int);
unsigned int g_lldI2c_WriteI2c0_bool(unsigned char, const unsigned char*, unsigned int);
unsigned int g_lldI2c_ReadI2c0_bool(unsigned char, const unsigned char*, unsigned int);


#endif //LLD_I2C_H_
