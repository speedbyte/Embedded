/*!
 * \file Gyro.h
 */
/*
 * Gyro.h
 *
 *  Created on: 05.05.2015
 *      Author: user
 */

#ifndef GYRO_H_
#define GYRO_H_


// 7 Bit I2C Slave address
#define M_I2C_SLAVE_ADDRESS_GYRO_UI8 0b1101010

// Define multiple or single read
#define M_HAL_GYRO_MULTIPLE_READ_FLAG_UI8 0b10000000
#define M_HAL_GYRO_SINGLE_READ_FLAG_UI8 0b00000000

#define M_HAL_BARO_NR_OF_BYTES_ONE_UI8 		1
#define M_HAL_BARO_NR_OF_BYTES_TWO_UI8 		2
#define M_HAL_BARO_NR_OF_BYTES_THREE_UI8 	3
#define M_HAL_BARO_NR_OF_BYTES_SIX_UI8 	6

/*****************Start of register defines******************/
//Device Identifier
#define M_HAL_GYRO_WHO_AM_I_UI8 0x0F

//----------------------------------------------------------
//Control register 1
#define M_HAL_GYRO_CTRL1_UI8 0x20
//Bits of DR
#define M_HAL_GYRO_CTRL1_DR0_UI8					0b01000000
#define M_HAL_GYRO_CTRL1_DR1_UI8					0b10000000
#define M_HAL_GYRO_CTRL1_DR0_DR1_UI8				0b11000000
//Bits of BW
#define M_HAL_GYRO_CTRL1_BW0_UI8					0b00010000
#define M_HAL_GYRO_CTRL1_BW1_UI8					0b00100000
#define M_HAL_GYRO_CTRL1_BW0_BW1_UI8				0b00110000
//Power mode
#define M_HAL_GYRO_CTRL1_POWER_DOWN_UI8				0b11110111 //reset of Bit 4 needed
#define M_HAL_GYRO_CTRL1_NORMAL_UI8					0b00001111
#define M_HAL_GYRO_CTRL1_SLEEP_UI8					0b00001000

//----------------------------------------------------------
//Control register 2
#define M_HAL_GYRO_CTRL2_UI8 0x21
//Edge sensitive trigger Enable
#define M_HAL_GYRO_CTRL2_EXTREN_UI8					0b10000000
//Level sensitive trigger Enable
#define M_HAL_GYRO_CTRL2_LVLEN_UI8					0b01000000
//High pass filter mode
#define M_HAL_GYRO_CTRL2_HPF_NORMAL_MODE_RESET_UI8	0b00000000
#define M_HAL_GYRO_CTRL2_HPF_REF_SIG_UI8			0b00010000
#define M_HAL_GYRO_CTRL2_HPF_NORMAL_MODE_UI8		0b00100000
#define M_HAL_GYRO_CTRL2_HPF_RESET_ON_INTER_UI8		0b00110000
//High pass filter cut off frequency configuration
#define M_HAL_GYRO_CTRL2_HPCF0_UI8					0b00000000
#define M_HAL_GYRO_CTRL2_HPCF1_UI8					0b00000001
#define M_HAL_GYRO_CTRL2_HPCF2_UI8					0b00000010
#define M_HAL_GYRO_CTRL2_HPCF3_UI8					0b00000011
#define M_HAL_GYRO_CTRL2_HPCF4_UI8					0b00000100
#define M_HAL_GYRO_CTRL2_HPCF5_UI8					0b00000101
#define M_HAL_GYRO_CTRL2_HPCF6_UI8					0b00000110
#define M_HAL_GYRO_CTRL2_HPCF7_UI8					0b00000111
#define M_HAL_GYRO_CTRL2_HPCF8_UI8					0b00001000
#define M_HAL_GYRO_CTRL2_HPCF9_UI8					0b00001001

//----------------------------------------------------------
//Control register 3
#define M_HAL_GYRO_CTRL3_UI8 0x22
//Interrupt enable on INT1 pin
#define M_HAL_GYRO_CTRL3_INT1_IG_UI8				0b10000000
//Boot status available on INT1 pin
#define M_HAL_GYRO_CTRL3_INT1_Boot_UI8				0b01000000
//Interrupt active configuration on INT
#define M_HAL_GYRO_CTRL3_H_Lactive_UI8				0b00100000
//Push- Pull / Open drain
#define M_HAL_GYRO_CTRL3_PP_OD_UI8					0b00010000
//Date Ready on DRDY/INT2 pin
#define M_HAL_GYRO_CTRL3_INT2_DRDY_UI8				0b00001000
//FIFO Threshold interrupt on DRDY/INT2 pin
#define M_HAL_GYRO_CTRL3_INT2_FTH_UI8				0b00000100
//FIFO Overrun interrupt on DRDY/INT2 pin
#define M_HAL_GYRO_CTRL3_INT2_ORun_UI8				0b00000010
//FIFO Empty interrupt on DRDY/INT2 pin
#define M_HAL_GYRO_CTRL3_INT2_Empty_UI8				0b00000001

//----------------------------------------------------------
//Control register 4
#define M_HAL_GYRO_CTRL4_UI8 0x23
//Block data update
#define M_HAL_GYRO_CTRL4_BDU_UI8					0b10000000
//Big/little endian data selection
#define M_HAL_GYRO_CTRL4_BLE_UI8					0b01000000
//Full scale selection
#define M_HAL_GYRO_CTRL4_SCALE_245DPS_UI8			0b00000000
#define M_HAL_GYRO_CTRL4_SCALE_500DPS_UI8			0b00010000
#define M_HAL_GYRO_CTRL4_SCALE_2000DPS_UI8			0b00100000
//Level sensitive latched enable
#define M_HAL_GYRO_CTRL4_IMPen_UI8					0b00001000
//FIFO Empty interrupt on DRDY/INT2 pin
#define M_HAL_GYRO_CTRL4_TEST_NORMAL_MODE_UI8		0b00000000
#define M_HAL_GYRO_CTRL4_TEST_SELF_TEST0_UI8		0b00000010
#define M_HAL_GYRO_CTRL4_TEST_SELF_TEST1_UI8		0b00000110
//FIFO Empty interrupt on DRDY/INT2 pin
#define M_HAL_GYRO_CTRL4_SIM_UI8					0b00000001

//----------------------------------------------------------
//Control register 5
#define M_HAL_GYRO_CTRL5_UI8 0x24
//Reboot memory content
#define M_HAL_GYRO_CTRL5_BOOT_UI8					0b10000000
//FIFO enable
#define M_HAL_GYRO_CTRL5_FIFO_EN_UI8				0b01000000
//Sensing chain FIFO stop values memorization at FIFO Threshold
#define M_HAL_GYRO_CTRL5_StopOnFTH_UI8				0b00100000
//High Pass filter Enable
#define M_HAL_GYRO_CTRL5_HPen_UI8					0b00010000
//INT Generator selection configuration
#define M_HAL_GYRO_CTRL5_IG_Sel_UI8					0b00000000
#define M_HAL_GYRO_CTRL5_IG_Sel0_UI8				0b00000100
#define M_HAL_GYRO_CTRL5_IG_Sel1_UI8				0b00001000
#define M_HAL_GYRO_CTRL5_IG_Sel0_IG_Sel1_UI8		0b00001100
//Out selection configuration
#define M_HAL_GYRO_CTRL5_Out_Sel_UI8				0b00000000
#define M_HAL_GYRO_CTRL5_Out_Sel0_UI8				0b00000001
#define M_HAL_GYRO_CTRL5_Out_Sel1_UI8				0b00000010
#define M_HAL_GYRO_CTRL5_Out_Sel0_Out_Sel1_UI8		0b00000011

//----------------------------------------------------------
//Digital high pass filter reference value
#define M_HAL_GYRO_REFERENCE_UI8 0x25

//----------------------------------------------------------
//OUT_TEMP register
#define M_HAL_GYRO_OUT_TEMP_UI8 0x26

//----------------------------------------------------------
//STATUS register
#define M_HAL_GYRO_STATUS_REG_UI8 0x27

//----------------------------------------------------------
//X-axis angular rate data: 2er complement Full value:   H & L
#define M_HAL_GYRO_OUT_X_L_UI8 0x28
#define M_HAL_GYRO_OUT_X_H_UI8 0x29

//----------------------------------------------------------
//Y-axis angular rate data: 2er complement Full value:   H & L
#define M_HAL_GYRO_OUT_Y_L_UI8 0x2A
#define M_HAL_GYRO_OUT_Y_H_UI8 0x2B

//----------------------------------------------------------
//Z-axis angular rate data: 2er complement Full value:   H & L
#define M_HAL_GYRO_OUT_Z_L_UI8 0x2C
#define M_HAL_GYRO_OUT_Z_H_UI8 0x2D

//----------------------------------------------------------
//FIFO_CTRL
#define M_HAL_GYRO_FIFO_CTRL_UI8 0x2E
//AND/OR combination of Interrupt events
#define M_HAL_GYRO_FIFO_CTRL_BYPASS_MODE_UI8			0b00000000
#define M_HAL_GYRO_FIFO_CTRL_FIFO_MODE_UI8				0b00100000
#define M_HAL_GYRO_FIFO_CTRL_STREAM_MODE_UI8			0b01000000
#define M_HAL_GYRO_FIFO_CTRL_STREAM_TO_FIFO_MODE_UI8	0b01100000
#define M_HAL_GYRO_FIFO_CTRL_BYPASS_TO_STREAM_MODE_UI8	0b10000000
#define M_HAL_GYRO_FIFO_CTRL_DYNAMIC_STREAM_MODE_UI8	0b11000000
#define M_HAL_GYRO_FIFO_CTRL_BYPASS_TO_FIFO_MODE_UI8	0b11100000

//----------------------------------------------------------
//FIFO_SRC register
#define M_HAL_GYRO_FIFO_SRC_UI8 0x2F

//----------------------------------------------------------
//Configuration register for Interrupt source
#define M_HAL_GYRO_IG_CFG_UI8 0x30
//AND/OR combination of Interrupt events
#define M_HAL_GYRO_IG_CFG_AND_OR_UI8				0b10000000
//Latch Interrupt Request
#define M_HAL_GYRO_IG_CFG_LIR_UI8					0b01000000
//Enable interrupt generation on Z high event
#define M_HAL_GYRO_IG_CFG_ZHIE_UI8					0b00100000
//Enable interrupt generation on Z low event
#define M_HAL_GYRO_IG_CFG_ZLIE_UI8					0b00010000
//Enable interrupt generation on Y high event
#define M_HAL_GYRO_IG_CFG_YHIE_UI8					0b00001000
//Enable interrupt generation on Y low event
#define M_HAL_GYRO_IG_CFG_YLIE_UI8					0b00000100
//Enable interrupt generation on Y low event
#define M_HAL_GYRO_IG_CFG_XHIE_UI8					0b00000010
//Enable interrupt generation on X low event
#define M_HAL_GYRO_IG_CFG_XLIE_UI8					0b00000001

//----------------------------------------------------------
//Interrupt source register. Read only register
#define M_HAL_GYRO_IG_SRC_UI8 0x31

//----------------------------------------------------------
//IG_THS_XH register
#define M_HAL_GYRO_IG_THS_XH_UI8 0x32
//Interrupt generation counter mode selection
#define M_HAL_GYRO_IG_THS_XH_DCRM_UI8				0b10000000

//----------------------------------------------------------
//IG_THS_XL register
#define M_HAL_GYRO_IG_THS_XL_UI8 0x33

//----------------------------------------------------------
//IG_THS_YH register
#define M_HAL_GYRO_IG_THS_YH_UI8 0x34

//----------------------------------------------------------
//IG_THS_YL register
#define M_HAL_GYRO_IG_THS_YL_UI8 0x35

//----------------------------------------------------------
//IG_THS_ZH register
#define M_HAL_GYRO_IG_THS_ZH_UI8 0x36

//----------------------------------------------------------
//IG_THS_ZL register
#define M_HAL_GYRO_IG_THS_ZL_UI8 0x37

//----------------------------------------------------------
//IG_DURATION register
#define M_HAL_GYRO_IG_DURATION_UI8 0x38
//Interrupt generation counter mode selection
#define M_HAL_GYRO_IG_DURATION_WAIT_UI8				0b10000000

//----------------------------------------------------------
//LOW_ODR register
#define M_HAL_GYRO_LOW_ODR_UI8 0x39
//DRDY/INT2 pin active level
#define M_HAL_GYRO_LOW_ODR_DRDY_HL_UI8				0b00100000
//SPI only
#define M_HAL_GYRO_LOW_ODR_I2C_dis_UI8				0b00001000
//Software reset
#define M_HAL_GYRO_LOW_ODR_SW_RES_UI8				0b00000100
//Low speed ODR
#define M_HAL_GYRO_LOW_ODR_Low_ODR_UI8				0b00000001

/*****************END of register defines********************/

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/05/05
 *
 * \brief struct with Gyroscope values
 * \details This struct stores yaw, pitch and roll
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
typedef struct
{
	double l_yaw_f64;
	double l_pitch_f64;
	double l_roll_f64;
}strGyro;


/* ---------------------------------------------
AUTHOR: Oliver Breuning (olbrgs00)
DATE OF CREATION: 2015/05/05

INPUT PARAMS: --
OUTPUT: --

DESCRIPTION:
Init sensor

CHANGELOG:
none
--------------------------------------------- */
int g_halGyro_initGyro_i32(void);

/* ---------------------------------------------
AUTHOR: Oliver Breuning (olbrgs00)
DATE OF CREATION: 2015/05/05

INPUT PARAMS: --
OUTPUT: --

DESCRIPTION:
Get interfaces for Gyroscope values
CHANGELOG:
none
--------------------------------------------- */
strGyro g_halGyro_getGyroscope_st(void);
double g_halGyro_getTemperature_f64(void);


/* ---------------------------------------------
AUTHOR: Oliver Breuning (olbrgs00)
DATE OF CREATION: 2015/05/05

INPUT PARAMS: --
OUTPUT: --

DESCRIPTION:
Trigger reading from I2C
CHANGELOG:
none
--------------------------------------------- */
int g_halGyro_readGyroscopeFromI2C_i32(void);
int g_halGyro_readTemperatureFromI2C_i32(void);



#endif /* GYRO_H_ */
