/*
 * MOTOR.c
 *
 *  Created on: Nov 18, 2015
 *      Author: ezs
 */

#include "MOTOR.h"
/*!**********************************************************************
 * \author Chris Mönch( chmoit00 )
 * \date 2015/04/18
 *
 * \brief Get the I2C addresses orderd by execution (defined in MOTOR.h)
 * \details
 *
 * \param[ in ] Array where the I2C Addresses will be stored
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
void getBLCtrlADRExecuteOrder(char BLCtrlADRExecuteOrder[]){
#if defined(Quadro_X) || defined(Quadro_Plus)
	int BLCTRLADR[4] = {DEFMotorNo1_BLCtrlADR, DEFMotorNo2_BLCtrlADR, DEFMotorNo3_BLCtrlADR, DEFMotorNo4_BLCtrlADR};

	BLCtrlADRExecuteOrder[DEFMotorNo1_OrderIDX ]=BLCTRLADR[0];
					BLCtrlADRExecuteOrder[DEFMotorNo2_OrderIDX]=BLCTRLADR[1];
					BLCtrlADRExecuteOrder[DEFMotorNo3_OrderIDX]=BLCTRLADR[2];
					BLCtrlADRExecuteOrder[DEFMotorNo4_OrderIDX]=BLCTRLADR[3];

#endif

#ifdef Okto_Plus
	int BLCTRLADR[8] = {DEFMotorNo1_BLCtrlADR, DEFMotorNo2_BLCtrlADR, DEFMotorNo3_BLCtrlADR
				DEFMotorNo4_BLCtrlADR, DEFMotorNo5_BLCtrlADR, DEFMotorNo6_BLCtrlADR,
				DEFMotorNo7_BLCtrlADR, DEFMotorNo8_BLCtrlADR};

	BLCtrlADRExecuteOrder[DEFMotorNo1_OrderIDX]=BLCTRLADR[0];
	BLCtrlADRExecuteOrder[DEFMotorNo2_OrderIDX]=BLCTRLADR[1];
	BLCtrlADRExecuteOrder[DEFMotorNo3_OrderIDX]=BLCTRLADR[2];
	BLCtrlADRExecuteOrder[DEFMotorNo4_OrderIDX]=BLCTRLADR[3];
	BLCtrlADRExecuteOrder[DEFMotorNo5_OrderIDX]=BLCTRLADR[4];
	BLCtrlADRExecuteOrder[DEFMotorNo6_OrderIDX]=BLCTRLADR[5];
	BLCtrlADRExecuteOrder[DEFMotorNo7_OrderIDX]=BLCTRLADR[6];
	BLCtrlADRExecuteOrder[DEFMotorNo8_OrderIDX]=BLCTRLADR[7];

#endif
}


