/*!
 * \file barometer.h
 */
/*
 * barometer.h
 *
 *  Created on: 05.05.2015
 *      Author: user
 */

#ifndef BAROMETER_H_
#define BAROMETER_H_

// 7 Bit I2C Slave address
#define M_I2C_SLAVE_ADDRESS_BARO_UI8 0b1011100

// Define multiple or single data
#define M_HAL_BARO_MULTIPLE_FLAG_UI8 0b10000000
#define M_HAL_BARO_SINGLE_FLAG_UI8 0b00000000

#define M_HAL_BARO_NR_OF_BYTES_ONE_UI8 1
#define M_HAL_BARO_NR_OF_BYTES_TWO_UI8 2
#define M_HAL_BARO_NR_OF_BYTES_THREE_UI8 3

/***************************Start of register defines**********************************/

//Reference pressure: 2er complement Full value: XL & H & L
#define M_HAL_BARO_REF_P_XL_UI8 0x08
#define M_HAL_BARO_REF_P_L_UI8 0x09
#define M_HAL_BARO_REF_P_H_UI8 0x0A
//----------------------------------------------------------
//Device Identifier: chip LPS331AP = 0xBB
#define M_HAL_BARO_WHO_AM_I_UI8 0x0F
//----------------------------------------------------------
//Pressure resolution mode
#define M_HAL_BARO_RES_CONF_UI8 0x10
//Pressure resolution configuration
#define M_HAL_BARO_PRES_RES_CONF_1_UI8 		0b00000000
#define M_HAL_BARO_PRES_RES_CONF_2_UI8	 	0b00000001
#define M_HAL_BARO_PRES_RES_CONF_4_UI8 		0b00000010
#define M_HAL_BARO_PRES_RES_CONF_8_UI8 		0b00000011
#define M_HAL_BARO_PRES_RES_CONF_16_UI8 	0b00000100
#define M_HAL_BARO_PRES_RES_CONF_32_UI8 	0b00000101
#define M_HAL_BARO_PRES_RES_CONF_64_UI8 	0b00000110
#define M_HAL_BARO_PRES_RES_CONF_128_UI8 	0b00000111
#define M_HAL_BARO_PRES_RES_CONF_256_UI8 	0b00001000
#define M_HAL_BARO_PRES_RES_CONF_384_UI8 	0b00001001
#define M_HAL_BARO_PRES_RES_CONF_512_UI8 	0b00001010

//Temperature resolution configuration
#define M_HAL_BARO_TEMP_RES_CONF_1_UI8 		0b00000000
#define M_HAL_BARO_TEMP_RES_CONF_2_UI8	 	0b00010000
#define M_HAL_BARO_TEMP_RES_CONF_4_UI8 		0b00100000
#define M_HAL_BARO_TEMP_RES_CONF_8_UI8 		0b00110000
#define M_HAL_BARO_TEMP_RES_CONF_16_UI8 	0b01000000
#define M_HAL_BARO_TEMP_RES_CONF_32_UI8 	0b01010000
#define M_HAL_BARO_TEMP_RES_CONF_64_UI8 	0b01100000
#define M_HAL_BARO_TEMP_RES_CONF_128_UI8 	0b01110000

//----------------------------------------------------------
//Control register 1
#define M_HAL_BARO_CTRL_REG1_UI8 0x20
//Power down control
#define M_HAL_BARO_CTRL_REG1_PD_UI8						0b10000000
#define M_HAL_BARO_CTRL_REG1_ZERO_UI8					0b00000000
//Data rate P=Pressure T=Temperature
#define M_HAL_BARO_CTRL_REG1_DATARATE_ONESHOT_1_UI8 	0b00000000
#define M_HAL_BARO_CTRL_REG1_DATARATE_P1HZ_T1HZ_UI8	 	0b00010000
#define M_HAL_BARO_CTRL_REG1_DATARATE_P7HZ_T1HZ_UI8 	0b00100000
#define M_HAL_BARO_CTRL_REG1_DATARATE_P12HZ_T1HZ_UI8 	0b00110000
#define M_HAL_BARO_CTRL_REG1_DATARATE_P25HZ_T1HZ_UI8 	0b01000000
#define M_HAL_BARO_CTRL_REG1_DATARATE_P7HZ_T7HZ_UI8		0b01010000
#define M_HAL_BARO_CTRL_REG1_DATARATE_P12HZ_T12HZ_UI8 	0b01100000
#define M_HAL_BARO_CTRL_REG1_DATARATE_P25HZ_T25HZ_UI 	0b01110000
//Interrupt circuit enable
#define M_HAL_BARO_CTRL_REG1_DIFF_EN_UI8				0b00001000
//Block data update
#define M_HAL_BARO_CTRL_REG1_BDU_UI8					0b00000100
//Delta pressure enable
#define M_HAL_BARO_CTRL_REG1_DELTA_EN_UI8				0b00000010
//SIM:SPI Interface Mode selection
#define M_HAL_BARO_CTRL_REG1_SIM_UI8					0b00000001

//----------------------------------------------------------
//Control register 2
#define M_HAL_BARO_CTRL_REG2_UI8 0x21
//Reboot memory content
#define M_HAL_BARO_CTRL_REG2_BOOT_UI8					0b10000000
//Software reset
#define M_HAL_BARO_CTRL_REG2_SWRESET_UI8				0b00000100
//Autozero enable
#define M_HAL_BARO_CTRL_REG2_AUTOZERO_UI8				0b00000010
//One shot enable
#define M_HAL_BARO_CTRL_REG2_ONE_SHOT_UI8				0b00000001

//----------------------------------------------------------
//Control register 3 Interrupt control
#define M_HAL_BARO_CTRL_REG3_UI8 0x22
//Interrupt active High Low
#define M_HAL_BARO_CTRL_REG3_INT_H_L_UI8				0b10000000
//Push pull - open drain selection on interrupt pads
#define M_HAL_BARO_CTRL_REG3_PP_OD_UI8					0b01000000
//data signal on INT2 pad control bits
#define M_HAL_BARO_CTRL_REG3_INT2_GND_UI8 				0b00000000
#define M_HAL_BARO_CTRL_REG3_INT2_P_HIGH_UI8	 		0b00001000
#define M_HAL_BARO_CTRL_REG3_INT2_P_LOW_UI8 			0b00010000
#define M_HAL_BARO_CTRL_REG3_INT2_P_LOW_HIGH_UI8 		0b00011000
#define M_HAL_BARO_CTRL_REG3_INT2_DATA_READY_UI8		0b00100000
#define M_HAL_BARO_CTRL_REG3_INT2_TRISTATE_UI8 			0b00111000
//data signal on INT1 pad control bits
#define M_HAL_BARO_CTRL_REG3_INT1_GND_UI8 				0b00000000
#define M_HAL_BARO_CTRL_REG3_INT1_P_HIGH_UI8	 		0b00000001
#define M_HAL_BARO_CTRL_REG3_INT1_P_LOW_UI8 			0b00000010
#define M_HAL_BARO_CTRL_REG3_INT1_P_LOW_HIGH_UI8 		0b00000011
#define M_HAL_BARO_CTRL_REG3_INT1_DATA_READY_UI8		0b00000100
#define M_HAL_BARO_CTRL_REG3_INT1_TRISTATE_UI8 			0b00000111

//----------------------------------------------------------
//Interrupt configuration
#define M_HAL_BARO_INT_CFG_REG_UI8 0x23
//LIR: Latch Interrupt request into INT_SOURCE register
#define M_HAL_BARO_INT_CFG_REG_LIR_UI8					0b00000100
//PL_E: Enable interrupt generation on differential pressure low event
#define M_HAL_BARO_INT_CFG_REG_PL_E_UI8					0b00000010
//PH_E: Enable interrupt generation on differential pressure high event
#define M_HAL_BARO_INT_CFG_REG_PH_E_UI8					0b00000001

//----------------------------------------------------------
//Interrupt source
#define M_HAL_BARO_INT_SOURCE_REG_UI8 0x24
//IA: Interrupt Active.
//#define M_HAL_BARO_INT_SOURCE_REG_IA_UI8					0b00000100
//PL: Differential pressure Low.
//#define M_HAL_BARO_INT_SOURCE_REG_PL_UI8					0b00000010
//PH: Differential pressure High.
//#define M_HAL_BARO_INT_SOURCE_REG_PH_UI8					0b00000001

//----------------------------------------------------------
//Threshold pressure (LSB): unsigned Full value: High & Low
#define M_HAL_BARO_THS_P_LOW_REG_UI8 0x25
#define M_HAL_BARO_THS_P_HIGH_REG_UI8 0x26

//----------------------------------------------------------
//Status register
#define M_HAL_BARO_STATUS_REG_UI8 0x27

//----------------------------------------------------------
//Pressure data: 2er complement Full value:   H & L & XL
#define M_HAL_BARO_PRESS_OUT_XL_UI8 0x28
#define M_HAL_BARO_PRESS_OUT_L_UI8 0x29
#define M_HAL_BARO_PRESS_OUT_H_UI8 0x2A

//----------------------------------------------------------
//Temperature data: 2er complement Full value:   H & L
#define M_HAL_BARO_TEMP_OUT_L_UI8 0x2B
#define M_HAL_BARO_TEMP_OUT_H_UI8 0x2C

//----------------------------------------------------------
//Analog front end control
#define M_HAL_BARO_AMP_CTRL_UI8 0x30

//----------------------------------------------------------
//Pressure offset: H & L & XL
#define M_HAL_BARO_DELTA_PRESS_XL_REH_UI8 0x3C
#define M_HAL_BARO_DELTA_PRESS_L_UI8 0x3D
#define M_HAL_BARO_DELTA_PRESS_H_UI8 0x3E

/*****************END of register defines********************/

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
int g_halBaro_initBaro_i32(void);

/* ---------------------------------------------
AUTHOR: Oliver Breuning (olbrgs00)
DATE OF CREATION: 2015/05/05

INPUT PARAMS: --
OUTPUT: --

DESCRIPTION:
Get interfaces for barometer values
CHANGELOG:
none
--------------------------------------------- */
double g_halBaro_getPressure_f64(void);
double g_halBaro_getTemperature_f64(void);


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
int g_halBaro_readPressureFromI2C_i32(void);
int g_halBaro_readTemperatureFromI2C_i32(void);



#endif /* BAROMETER_H_ */
