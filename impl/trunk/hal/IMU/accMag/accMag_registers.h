/*!
 * \file accMag_registers.h
 */
#ifndef HAL_ACCMAG_REGISTERS_H
#define HAL_ACCMAG_REGISTERS_H

/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/05/05
 *
 * DESCRIPTION:
 * Defines of all registers of LSM303D
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// CONTROL REGISTERS
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// ----------------------------------------------------------------------
// CONTROL REGISTER 0
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_CTRL0_UI8					0x1F	//!< Control register 0 address

// Bitmasks
#define	M_HAL_ACCMAG_CTRL0_MASK_BOOT_UI8		0b10000000
#define	M_HAL_ACCMAG_CTRL0_MASK_FIFO_EN_UI8		0b01000000
#define	M_HAL_ACCMAG_CTRL0_MASK_FTH_EN_UI8		0b00100000
// unused bit (force zero!)						0b00010000
// unused bit (force zero!)						0b00001000
#define	M_HAL_ACCMAG_CTRL0_MASK_HP_CLICK_UI8	0b00000100
#define	M_HAL_ACCMAG_CTRL0_MASK_HPIS1_UI8		0b00000010
#define	M_HAL_ACCMAG_CTRL0_MASK_HPIS2_UI8		0b00000001

// ----------------------------------------------------------------------
// CONTROL REGISTER 1
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_CTRL1_UI8					0x20	//!< Control register, 2nd

// Bitmasks
#define	M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_0HZ_UI8		0b00000000
#define	M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_3HZ125_UI8		0b00010000
#define	M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_6HZ25_UI8		0b00100000
#define	M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_12HZ5_UI8		0b00110000
#define	M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_25HZ_UI8		0b01000000
#define	M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_50HZ_UI8		0b01010000
#define	M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_100HZ_UI8		0b01100000
#define	M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_200HZ_UI8		0b01110000
#define	M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_400HZ_UI8		0b10000000
#define	M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_800HZ_UI8		0b10010000
#define	M_HAL_ACCMAG_CTRL1_MASK_ACC_RATE_1600HZ_UI8		0b10100000
#define	M_HAL_ACCMAG_CTRL1_MASK_BDU_UI8					0b00001000
#define	M_HAL_ACCMAG_CTRL1_MASK_AZEN_UI8				0b00000100
#define	M_HAL_ACCMAG_CTRL1_MASK_AYEN_UI8				0b00000010
#define	M_HAL_ACCMAG_CTRL1_MASK_AXEN_UI8				0b00000001

// ----------------------------------------------------------------------
// CONTROL REGISTER 2
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_CTRL2_UI8							0x21	//!< Control register, 3rd

// Bitmasks
#define	M_HAL_ACCMAG_CTRL2_MASK_ACC_BANDWIDTH_773HZ_UI8	0b00000000
#define	M_HAL_ACCMAG_CTRL2_MASK_ACC_BANDWIDTH_194HZ_UI8	0b01000000
#define	M_HAL_ACCMAG_CTRL2_MASK_ACC_BANDWIDTH_362HZ_UI8	0b10000000
#define	M_HAL_ACCMAG_CTRL2_MASK_ACC_BANDWIDTH_50HZ_UI8	0b11000000
#define	M_HAL_ACCMAG_CTRL2_MASK_ACC_SCALE_2G_UI8		0b00000000
#define	M_HAL_ACCMAG_CTRL2_MASK_ACC_SCALE_4G_UI8		0b00001000
#define	M_HAL_ACCMAG_CTRL2_MASK_ACC_SCALE_6G_UI8		0b00010000
#define	M_HAL_ACCMAG_CTRL2_MASK_ACC_SCALE_8G_UI8		0b00011000
#define	M_HAL_ACCMAG_CTRL2_MASK_ACC_SCALE_16G_UI8		0b00100000
// unused bit (force zero!)								0b00000100
#define	M_HAL_ACCMAG_CTRL2_MASK_AST_UI8					0b00000010
#define	M_HAL_ACCMAG_CTRL2_MASK_SIM_UI8					0b00000001

// ----------------------------------------------------------------------
// CONTROL REGISTER 3
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_CTRL3_UI8						0x22	//!< Control register, 4th

// Bitmasks
#define	M_HAL_ACCMAG_CTRL3_MASK_INT1_BOOT_UI8		0b10000000
#define	M_HAL_ACCMAG_CTRL3_MASK_INT1_CLICK_UI8		0b01000000
#define	M_HAL_ACCMAG_CTRL3_MASK_INT1_IG1_UI8		0b00100000
#define	M_HAL_ACCMAG_CTRL3_MASK_INT1_IG2_UI8		0b00010000
#define	M_HAL_ACCMAG_CTRL3_MASK_INT1_IGM_UI8		0b00001000
#define	M_HAL_ACCMAG_CTRL3_MASK_INT1_DRDY_A_UI8		0b00000100
#define	M_HAL_ACCMAG_CTRL3_MASK_INT1_DRDY_M_UI8		0b00000010
#define	M_HAL_ACCMAG_CTRL3_MASK_INT1_EMPTY_UI8		0b00000001

// ----------------------------------------------------------------------
// CONTROL REGISTER 4
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_CTRL4_UI8						0x23	//!< Control register, 5th

// Bitmasks
#define	M_HAL_ACCMAG_CTRL4_MASK_INT2_CLICK_UI8		0b10000000
#define	M_HAL_ACCMAG_CTRL4_MASK_INT2_INT1_UI8		0b01000000
#define	M_HAL_ACCMAG_CTRL4_MASK_INT2_INT2_UI8		0b00100000
#define	M_HAL_ACCMAG_CTRL4_MASK_INT2_INTM_UI8		0b00010000
#define	M_HAL_ACCMAG_CTRL4_MASK_INT2_DRDY_A_UI8		0b00001000
#define	M_HAL_ACCMAG_CTRL4_MASK_INT2_DRDY_M_UI8		0b00000100
#define	M_HAL_ACCMAG_CTRL4_MASK_INT2_OVERRN_UI8		0b00000010
#define	M_HAL_ACCMAG_CTRL4_MASK_INT2_FTH_UI8		0b00000001

// ----------------------------------------------------------------------
// CONTROL REGISTER 5
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_CTRL5_UI8						0x24	//!< Control register, 6th

// Bitmasks
#define	M_HAL_ACCMAG_CTRL5_MASK_TEMP_EN_UI8			0b10000000
#define	M_HAL_ACCMAG_CTRL5_MASK_MAG_RES_LOW_UI8		0b00000000
#define	M_HAL_ACCMAG_CTRL5_MASK_MAG_RES_HIGH_UI8	0b01100000
#define	M_HAL_ACCMAG_CTRL5_MASK_MAG_RATE_3HZ125_UI8	0b00000000
#define	M_HAL_ACCMAG_CTRL5_MASK_MAG_RATE_6HZ25_UI8	0b00000100
#define	M_HAL_ACCMAG_CTRL5_MASK_MAG_RATE_12HZ5_UI8	0b00001000
#define	M_HAL_ACCMAG_CTRL5_MASK_MAG_RATE_25HZ_UI8	0b00001100
#define	M_HAL_ACCMAG_CTRL5_MASK_MAG_RATE_50HZ_UI8	0b00010000
#define	M_HAL_ACCMAG_CTRL5_MASK_MAG_RATE_100HZ_UI8	0b00010100
#define	M_HAL_ACCMAG_CTRL5_MASK_LIR2_UI8			0b00000010
#define	M_HAL_ACCMAG_CTRL5_MASK_LIR1_UI8			0b00000001

// ----------------------------------------------------------------------
// CONTROL REGISTER 6
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_CTRL6_UI8							0x25	//!< Control register, 7th

// Bitmasks
#define	M_HAL_ACCMAG_CTRL6_MASK_MAG_SCALE_2GAUSS_UI8	0b000000000
#define	M_HAL_ACCMAG_CTRL6_MASK_MAG_SCALE_4GAUSS_UI8	0b001000000
#define	M_HAL_ACCMAG_CTRL6_MASK_MAG_SCALE_8GAUSS_UI8	0b010000000
#define	M_HAL_ACCMAG_CTRL6_MASK_MAG_SCALE_12GAUSS_UI8	0b011000000

// ----------------------------------------------------------------------
// CONTROL REGISTER 7
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_CTRL7_UI8					0x26	//!< Control register, 8th

// Bitmasks
#define	M_HAL_ACCMAG_CTRL7_MASK_ACC_HPFILT_NORMREF_UI8		0b00000000
#define	M_HAL_ACCMAG_CTRL7_MASK_ACC_HPFILT_SIGREF_UI8		0b01000000
#define	M_HAL_ACCMAG_CTRL7_MASK_ACC_HPFILT_NORM_UI8			0b01000000
#define	M_HAL_ACCMAG_CTRL7_MASK_ACC_HPFILT_AUTORESET_UI8	0b01000000
#define	M_HAL_ACCMAG_CTRL7_MASK_AFDS_UI8					0b00100000
#define	M_HAL_ACCMAG_CTRL7_MASK_T_ONLY_UI8					0b00010000
// unused bit (force zero!)									0b00001000
#define	M_HAL_ACCMAG_CTRL7_MASK_MLP_UI8						0b00000100
#define	M_HAL_ACCMAG_CTRL7_MASK_MAG_SENSMODE_CONTINOUS_UI8	0b00000000
#define	M_HAL_ACCMAG_CTRL7_MASK_MAG_SENSMODE_SINGLE_UI8		0b00000010
#define	M_HAL_ACCMAG_CTRL7_MASK_MAG_SENSMODE_PWRDOWN_UI8	0b00000011

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// FIFO registers
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// ----------------------------------------------------------------------
// FIFO control registers
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_FIFO_CTRL_UI8							0x2E	//!< Controls FIFO mode to store measurements

// Bitmasks
#define	M_HAL_ACCMAG_FIFO_CTRL_MASK_BYPASS_MODE_UI8			0b00000000
#define	M_HAL_ACCMAG_FIFO_CTRL_MASK_FIFO_MODE_UI8			0b00100000
#define	M_HAL_ACCMAG_FIFO_CTRL_MASK_STREAM_MODE_UI8			0b01000000
#define	M_HAL_ACCMAG_FIFO_CTRL_MASK_STREAM2FIFO_MODE_UI8	0b01100000
#define	M_HAL_ACCMAG_FIFO_CTRL_MASK_BYPASS2STREAM_MODE_UI8	0b10000000
#define	M_HAL_ACCMAG_FIFO_CTRL_MASK_FTH4_UI8				0b00010000
#define	M_HAL_ACCMAG_FIFO_CTRL_MASK_FTH3_UI8				0b00001000
#define	M_HAL_ACCMAG_FIFO_CTRL_MASK_FTH2_UI8				0b00000100
#define	M_HAL_ACCMAG_FIFO_CTRL_MASK_FTH1_UI8				0b00000010
#define	M_HAL_ACCMAG_FIFO_CTRL_MASK_FTH0_UI8				0b00000001

// ----------------------------------------------------------------------
// FIFO status registers
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_FIFO_SRC_UI8						0x2F	//!< Status of FIFO

// Bitmasks
#define	M_HAL_ACCMAG_FIFO_SRC_MASK_FTH_UI8				0b10000000
#define	M_HAL_ACCMAG_FIFO_SRC_MASK_OVRN_UI8				0b01000000
#define	M_HAL_ACCMAG_FIFO_SRC_MASK_EMPTY_UI8			0b00100000
#define	M_HAL_ACCMAG_FIFO_SRC_MASK_FSS4_UI8				0b00010000
#define	M_HAL_ACCMAG_FIFO_SRC_MASK_FSS3_UI8				0b00001000
#define	M_HAL_ACCMAG_FIFO_SRC_MASK_FSS2_UI8				0b00000100
#define	M_HAL_ACCMAG_FIFO_SRC_MASK_FSS1_UI8				0b00000010
#define	M_HAL_ACCMAG_FIFO_SRC_MASK_FSS0_UI8				0b00000001

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Sleep/Wakeup config
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define	M_HAL_ACCMAG_ACT_THS_UI7						0x3E	//!< Wakeup/RtnToSleep threshold of acc. (1LSB = 16mg)
#define	M_HAL_ACCMAG_ACT_DUR_UI8						0x3F	//!< Wakeup/RtnToSleep duration of acc.

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Temperature sensor
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define	M_HAL_ACCMAG_TEMP_OUT_L_UI8						0x06	//!< Temp. sensor data, LSB byte
#define	M_HAL_ACCMAG_TEMP_OUT_H_UI8						0x06	//!< Temp. sensor data, MSB byte

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// WHO AM I Identification
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define	M_HAL_ACCMAG_WHO_AM_I_UI8						0x0F		//!< who am i register of LSM303D
#define	M_HAL_ACCMAG_WHO_AM_I_PATTERN_UI8				0b01001001	//!< expected value of who am i register of LSM303D

// ======================================================================
// MAGNETOMETER SECTION
// ======================================================================

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Status register magnetometer
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define	M_HAL_ACCMAG_STATUS_M_UI8						0x07	//!< Status register of magnetometer

// Bitmasks
#define	M_HAL_ACCMAG_STATUS_M_MASK_ZYXMOR_UI8			0b10000000
#define	M_HAL_ACCMAG_STATUS_M_MASK_ZMOR_UI8				0b01000000
#define	M_HAL_ACCMAG_STATUS_M_MASK_YMOR_UI8				0b00100000
#define	M_HAL_ACCMAG_STATUS_M_MASK_XMOR_UI8				0b00010000
#define	M_HAL_ACCMAG_STATUS_M_MASK_ZYXMDA_UI8			0b00001000
#define	M_HAL_ACCMAG_STATUS_M_MASK_ZMDA_UI8				0b00000100
#define	M_HAL_ACCMAG_STATUS_M_MASK_YMDA_UI8				0b00000010
#define	M_HAL_ACCMAG_STATUS_M_MASK_XMDA_UI8				0b00000001

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Interrupt control for magnetometer
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// ----------------------------------------------------------------------
// Interrupt control register for magnetometer
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_INT_CTRL_M_UI8						0x12	//!< Interrupt control for magnetometer

// Bitmasks
#define	M_HAL_ACCMAG_INT_CTRL_M_MASK_XMIEN_UI8			0b10000000
#define	M_HAL_ACCMAG_INT_CTRL_M_MASK_YMIEN_UI8			0b01000000
#define	M_HAL_ACCMAG_INT_CTRL_M_MASK_ZMIEN_UI8			0b00100000
#define	M_HAL_ACCMAG_INT_CTRL_M_MASK_PP_OD_UI8			0b00010000
#define	M_HAL_ACCMAG_INT_CTRL_M_MASK_MIEA_UI8			0b00001000
#define	M_HAL_ACCMAG_INT_CTRL_M_MASK_MIEL_UI8			0b00000100
#define	M_HAL_ACCMAG_INT_CTRL_M_MASK_4D_UI8				0b00000010
#define	M_HAL_ACCMAG_INT_CTRL_M_MASK_MIEN_UI8			0b00000001

// ----------------------------------------------------------------------
// Interrupt status register for magnetometer
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_INT_SRC_M_UI8						0x13	//!< Interrupt event flags for magnetometer

// Bitmasks
#define	M_HAL_ACCMAG_INT_SRC_M_MASK_PTH_X_UI8			0b10000000
#define	M_HAL_ACCMAG_INT_SRC_M_MASK_PTH_Y_UI8			0b01000000
#define	M_HAL_ACCMAG_INT_SRC_M_MASK_PTH_Z_UI8			0b00100000
#define	M_HAL_ACCMAG_INT_SRC_M_MASK_NTH_X_UI8			0b00010000
#define	M_HAL_ACCMAG_INT_SRC_M_MASK_NTH_Y_UI8			0b00001000
#define	M_HAL_ACCMAG_INT_SRC_M_MASK_NTH_Z_UI8			0b00000100
#define	M_HAL_ACCMAG_INT_SRC_M_MASK_MROI_UI				0b00000010
#define	M_HAL_ACCMAG_INT_SRC_M_MASK_MINT_UI8			0b00000001

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Interrupt threshold for magnetometer
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define	M_HAL_ACCMAG_INT_THS_L_M_UI8					0x14	//!< Interrupt threshold value, LSB, ui16
#define	M_HAL_ACCMAG_INT_THS_H_M_UI8					0x15	//!< Interrupt threshold value, MSB, ui16

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// sensor data registers (magnetometer)
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define	M_HAL_ACCMAG_OUT_X_L_M_UI8						0x08	//!< data register compass, X-axis, LSB, 2-complement
#define	M_HAL_ACCMAG_OUT_X_H_M_UI8						0x09	//!< data register compass, X-axis, MSB, 2-complement
#define	M_HAL_ACCMAG_OUT_Y_L_M_UI8						0x0A	//!< data register compass, Y-axis, LSB, 2-complement
#define	M_HAL_ACCMAG_OUT_Y_H_M_UI8						0x0B	//!< data register compass, Y-axis, MSB, 2-complement
#define	M_HAL_ACCMAG_OUT_Z_L_M_UI8						0x0C	//!< data register compass, Z-axis, LSB, 2-complement
#define	M_HAL_ACCMAG_OUT_Z_H_M_UI8						0x0D	//!< data register compass, Z-axis, MSB, 2-complement

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// offset data registers (magnetometer)
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define	M_HAL_ACCMAG_OFFSET_X_L_M_UI8					0x16	//!< offset register compass, X-axis, LSB, 2-complement
#define	M_HAL_ACCMAG_OFFSET_X_H_M_UI8					0x17	//!< offset register compass, X-axis, MSB, 2-complement
#define	M_HAL_ACCMAG_OFFSET_Y_L_M_UI8					0x18	//!< offset register compass, Y-axis, LSB, 2-complement
#define	M_HAL_ACCMAG_OFFSET_Y_H_M_UI8					0x19	//!< offset register compass, Y-axis, MSB, 2-complement
#define	M_HAL_ACCMAG_OFFSET_Z_L_M_UI8					0x1A	//!< offset register compass, Z-axis, LSB, 2-complement
#define	M_HAL_ACCMAG_OFFSET_Z_H_M_UI8					0x1B	//!< offset register compass, Z-axis, MSB, 2-complement

// ======================================================================
// ACCELERATION SECTION
// ======================================================================

// ----------------------------------------------------------------------
// Status register acceleration
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_STATUS_A_UI8				0x27	//!< Status register of acceleration

// Bitmasks
#define	M_HAL_ACCMAG_STATUS_A_MASK_ZYXAOR_UI8	0b10000000
#define	M_HAL_ACCMAG_STATUS_A_MASK_ZAOR_UI8		0b01000000
#define	M_HAL_ACCMAG_STATUS_A_MASK_YAOR_UI8		0b00100000
#define	M_HAL_ACCMAG_STATUS_A_MASK_XAOR_UI8		0b00010000
#define	M_HAL_ACCMAG_STATUS_A_MASK_ZYXADA_UI8	0b00001000
#define	M_HAL_ACCMAG_STATUS_A_MASK_ZADA_UI8		0b00000100
#define	M_HAL_ACCMAG_STATUS_A_MASK_YADA_UI8		0b00000010
#define	M_HAL_ACCMAG_STATUS_A_MASK_XADA_UI8		0b00000001

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// sensor data registers (acceleration)
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define	M_HAL_ACCMAG_OUT_X_L_A_UI8		0x28	//!< data register acc., X-axis, LSB, 2-complement
#define	M_HAL_ACCMAG_OUT_X_H_A_UI8		0x29	//!< data register acc., X-axis, MSB, 2-complement
#define	M_HAL_ACCMAG_OUT_Y_L_A_UI8		0x2A	//!< data register acc., Y-axis, LSB, 2-complement
#define	M_HAL_ACCMAG_OUT_Y_H_A_UI8		0x2B	//!< data register acc., Y-axis, MSB, 2-complement
#define	M_HAL_ACCMAG_OUT_Z_L_A_UI8		0x2C	//!< data register acc., Z-axis, LSB, 2-complement
#define	M_HAL_ACCMAG_OUT_Z_H_A_UI8		0x2D	//!< data register acc., Z-axis, MSB, 2-complement

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// reference values for high-pass filter (acceleration)
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define	M_HAL_ACCMAG_REFERENCE_X_UI8	0x1C	//!< Acc. HP-Filter reference value, X-axis
#define	M_HAL_ACCMAG_REFERENCE_Y_UI8	0x1D	//!< Acc. HP-Filter reference value, Y-axis
#define	M_HAL_ACCMAG_REFERENCE_Z_UI8	0x1E	//!< Acc. HP-Filter reference value, Z-axis

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Inertial interrupt generator No. 1
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// ----------------------------------------------------------------------
// Inertial interrupt generator 1 config
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_IG_CFG1_UI8				0x30	//!< Inertial interrupt generator 1 config

// Bitmasks
#define	M_HAL_ACCMAG_IG_CFG1_MASK_AOI_UI8		0b10000000
#define	M_HAL_ACCMAG_IG_CFG1_MASK_6D_UI8		0b01000000
#define	M_HAL_ACCMAG_IG_CFG1_MASK_ZHIE_UI8		0b00100000
#define	M_HAL_ACCMAG_IG_CFG1_MASK_ZLIE_UI8		0b00010000
#define	M_HAL_ACCMAG_IG_CFG1_MASK_YHIE_UI8		0b00001000
#define	M_HAL_ACCMAG_IG_CFG1_MASK_YLIE_UI8		0b00000100
#define	M_HAL_ACCMAG_IG_CFG1_MASK_XHIE_UI8		0b00000010
#define	M_HAL_ACCMAG_IG_CFG1_MASK_XLIE_UI8		0b00000001

// ----------------------------------------------------------------------
// Inertial interrupt generator 1 status
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_IG_SRC1_UI8		0x31	//!< Inertial interrupt generator 1 status

// Bitmasks
// unused bit (force zero!)						0b10000000
#define	M_HAL_ACCMAG_IG_SRC1_MASK_IA_UI8		0b01000000
#define	M_HAL_ACCMAG_IG_SRC1_MASK_ZH_UI8		0b00100000
#define	M_HAL_ACCMAG_IG_SRC1_MASK_ZL_UI8		0b00010000
#define	M_HAL_ACCMAG_IG_SRC1_MASK_YH_UI8		0b00001000
#define	M_HAL_ACCMAG_IG_SRC1_MASK_YL_UI8		0b00000100
#define	M_HAL_ACCMAG_IG_SRC1_MASK_XH_UI8		0b00000010
#define	M_HAL_ACCMAG_IG_SRC1_MASK_XL_UI8		0b00000001

// ----------------------------------------------------------------------
// Inertial interrupt generator 1 threshold & duration
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_IG_THS1_UI8		0x32	//!< Inertial interrupt generator 1 threshold
#define	M_HAL_ACCMAG_IG_DUR1_UI8		0x33	//!< Inertial interrupt generator 1 duration

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Inertial interrupt generator No. 2
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// ----------------------------------------------------------------------
// Inertial interrupt generator 2 config
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_IG_CFG2_UI8				0x34	//!< Inertial interrupt generator 2 config

// Bitmasks
#define	M_HAL_ACCMAG_IG_CFG2_MASK_AOI_UI8		0b10000000
#define	M_HAL_ACCMAG_IG_CFG2_MASK_6D_UI8		0b01000000
#define	M_HAL_ACCMAG_IG_CFG2_MASK_ZHIE_UI8		0b00100000
#define	M_HAL_ACCMAG_IG_CFG2_MASK_ZLIE_UI8		0b00010000
#define	M_HAL_ACCMAG_IG_CFG2_MASK_YHIE_UI8		0b00001000
#define	M_HAL_ACCMAG_IG_CFG2_MASK_YLIE_UI8		0b00000100
#define	M_HAL_ACCMAG_IG_CFG2_MASK_XHIE_UI8		0b00000010
#define	M_HAL_ACCMAG_IG_CFG2_MASK_XLIE_UI8		0b00000001

// ----------------------------------------------------------------------
// Inertial interrupt generator 2 status
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_IG_SRC2_UI8				0x35	//!< Inertial interrupt generator 2 status

// Bitmasks
// unused bit (force zero!)						0b10000000
#define	M_HAL_ACCMAG_IG_SRC2_MASK_IA_UI8		0b01000000
#define	M_HAL_ACCMAG_IG_SRC2_MASK_ZH_UI8		0b00100000
#define	M_HAL_ACCMAG_IG_SRC2_MASK_ZL_UI8		0b00010000
#define	M_HAL_ACCMAG_IG_SRC2_MASK_YH_UI8		0b00001000
#define	M_HAL_ACCMAG_IG_SRC2_MASK_YL_UI8		0b00000100
#define	M_HAL_ACCMAG_IG_SRC2_MASK_XH_UI8		0b00000010
#define	M_HAL_ACCMAG_IG_SRC2_MASK_XL_UI8		0b00000001

// ----------------------------------------------------------------------
// Inertial interrupt generator 2 threshold & duration
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_IG_THS2_UI8		0x36	//!< Inertial interrupt generator 2 threshold
#define	M_HAL_ACCMAG_IG_DUR2_UI8		0x37	//!< Inertial interrupt generator 2 duration

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Double click gesture interrupt
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// ----------------------------------------------------------------------
// Double click gesture config
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_CLICK_CFG_UI8		0x38	//!< Double click gesture config

// Bitmasks
// unused bit (force zero!)						0b10000000
// unused bit (force zero!)						0b01000000
#define	M_HAL_ACCMAG_CLICK_CFG_MASK_ZD_UI8		0b00100000
#define	M_HAL_ACCMAG_CLICK_CFG_MASK_ZS_UI8		0b00010000
#define	M_HAL_ACCMAG_CLICK_CFG_MASK_YD_UI8		0b00001000
#define	M_HAL_ACCMAG_CLICK_CFG_MASK_YS_UI8		0b00000100
#define	M_HAL_ACCMAG_CLICK_CFG_MASK_XD_UI8		0b00000010
#define	M_HAL_ACCMAG_CLICK_CFG_MASK_XS_UI8		0b00000001

// ----------------------------------------------------------------------
// Double click gesture status
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_CLICK_SRC_UI8		0x39	//!< Double click gesture status

// Bitmasks
// unused bit (force zero!)						0b10000000
#define	M_HAL_ACCMAG_CLICK_SRC_MASK_IA_UI8		0b01000000
#define	M_HAL_ACCMAG_CLICK_SRC_MASK_DCLICK_UI8	0b00100000
#define	M_HAL_ACCMAG_CLICK_SRC_MASK_SCLICK_UI8	0b00010000
#define	M_HAL_ACCMAG_CLICK_SRC_MASK_SIGN_UI8	0b00001000
#define	M_HAL_ACCMAG_CLICK_SRC_MASK_Z_UI8		0b00000100
#define	M_HAL_ACCMAG_CLICK_SRC_MASK_Y_UI8		0b00000010
#define	M_HAL_ACCMAG_CLICK_SRC_MASK_X_UI8		0b00000001

// ----------------------------------------------------------------------
// Double click gesture parameters
// ----------------------------------------------------------------------
#define	M_HAL_ACCMAG_CLICK_THS_UI8		0x3A	//!< Double click gesture threshold
#define	M_HAL_ACCMAG_TIME_LIMIT_UI7		0x3B	//!< Double click gesture time limit
#define	M_HAL_ACCMAG_TIME_LATENCY_UI8	0x3C	//!< Double click gesture time latency
#define	M_HAL_ACCMAG_TIME_WINDOW_UI8	0x3D	//!< Double click gesture time window


#endif	//HAL_ACCMAG_REGISTERS_H
