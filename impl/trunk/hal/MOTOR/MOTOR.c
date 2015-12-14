/*
 * MOTOR.c
 *
 *  Created on: Nov 18, 2015
 *      Author: ezs
 */

#include "MOTOR.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

/* Global Variables */
char BLCtrlADRExecuteOrder[DEFMotorsCount];
char PWMValue[DEFMotorsCount];

//Flags
char flagRunSendPwmToMotor;

/*!**********************************************************************
 * \author Chris Mönch( chmoit00 )
 * \date 2015/04/18
 *
 *
 * \brief calls every init functions which is needed for motors
 *
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
void InitMotor(){
	SetFlagRunSendPwmToMotor(0);
	SetMotorExecutionOrder();
	SetPwmMotor(DEFMotorALL_PWM, DEFMotorSetpointMIN, 0);
	//Last one always initMotorTimer()
	InitMotorTimer();
	SetFlagRunSendPwmToMotor(1);
}

/*!**********************************************************************
 * \author Chris Mönch( chmoit00 )
 * \date 2015/04/18
 *
 *
 * \brief set Motor Exectution Order
 *
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
void SetMotorExecutionOrder(){
	GetBLCtrlADRExecuteOrder(&BLCtrlADRExecuteOrder[0]);
}

/*!**********************************************************************
 * \author Chris Mönch( chmoit00 )
 * \date 2015/04/18
 *
 *
 * \brief sets PWM Signal of Motor which is in toSet Selected
 * \details toSet = 00001111 sets the first 4 Motoers in Execution Order to pwmValue
 *
 * \param[ in ] toSet - Which Motor to Set
 * \param[ in ] pwmValue - Which Value so Set
 * \param[ in ] optFlag - optional Parameter if !0 flagRunSendPwmToMotor will be set
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
void SetPwmMotor(char toSet , int pwmValue, int optFlag){
	int i=0;
	while(toSet != 0 && i < DEFMotorsCount){

		if(toSet%2){
			PWMValue[i++]= pwmValue;
		}
		toSet= toSet >>1;
	}
	if(optFlag != 0){
		SetFlagRunSendPwmToMotor(1);
	}
}

int GetPwmMotor(int motorNumber){
	return motorNumber < DEFMotorsCount ? PWMValue[motorNumber]: 0;
}


/*!**********************************************************************
 * \author Chris Mönch( chmoit00 )
 * \date 2015/04/18
 *

 * \brief init Timer for the IsrMotor
 * \details
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
void InitMotorTimer(){

	struct sigaction sa;
	struct itimerval timer;

	//Creates Signal, if signal Rising a_handler called
	memset(&sa, 0 , sizeof(sa));
	sa.sa_handler = &IsrSetFlag;
	sigaction(SIGVTALRM, &sa, NULL);

	//Expire the Timer after:
	timer.it_value.tv_sec = 2;
	timer.it_value.tv_usec = 0;
	//And every ... after that:
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 9;
	//upon expiration the signal SIGVTALRM raised
	setitimer(ITIMER_VIRTUAL, &timer , NULL);
}

/*!**********************************************************************
 * \author Chris Mönch( chmoit00 )
 * \date 2015/04/18
 *
 * \brief set flag flagRunIsrMotor
 *
 * \param[ in ] 1 Set Flag, else clear Flag
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
void SetFlagRunSendPwmToMotor(char value){
	if(value == 1){
		flagRunSendPwmToMotor=value;
	}else{
		flagRunSendPwmToMotor=0;
	}
}

/*!**********************************************************************
 * \author Chris Mönch( chmoit00 )
 * \date 2015/04/18
 *
 * \brief ISR for set flag as flagRunIsrMotor
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
void IsrSetFlag(){
	flagRunSendPwmToMotor=1;
}

/*!**********************************************************************
 * \author Chris Mönch( chmoit00 )
 * \date 2015/04/18
 *
 * \brief get flag flagRunIsrMotor
 *
 * \param[out] flag flagRunIsrMotor
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
char GetFlagRunSendPwmToMotor(){
	return flagRunSendPwmToMotor;
}

/*!**********************************************************************
 * \author Chris Mönch( chmoit00 )
 * \date 2015/04/18
 *
 * \brief sends every timer interrupt to the motors the specific pwm values
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
void sendPwmToMotor(){
	int i;
	for(i = 0; i < DEFMotorsCount ;i++)
	{
		g_lldI2c_WriteI2c_bl(BLCtrlADRExecuteOrder[i],&PWMValue[i],1);
	}
}

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
void GetBLCtrlADRExecuteOrder(char BLCtrlADRExecuteOrder[]){
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


void SendManeuver(maneuver m){

}


