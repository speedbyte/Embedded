/*
 * MOTOR.h
 *
 *  Created on: Nov 18, 2015
 *      Author: ezs
 */

#include "../../MAIN/main.h"

//========================================================================================================rft=
// DEF DEFAULTS
//------------------------------------------------------------------------------------------------------------
// ***** defaults: Motors - dependent on copter type
#ifdef Quadro_Plus
//------------------------------------------------------------------------------------------------------------
// Quadro Plus - hardware configuration
//               motor rotating direction: (>) CW - clockwise / (<) CCW - counterclockwise
//
//                            Nick (+ x-axis)
//
//                                    o MotorNo1(>)
//                                    |
//  Roll (+ y-axis)    MotorNo4(<) o-F|C-o MotorNo3(<)  Roll (- y-axis)
//                                    |
//                        MotorNo2(>) o
//
//                            Nick (- x-axis)
//------------------------------------------------------------------------------------------------------------
  #define DEFMotorsCount                 4          // (CC) Quadrocopter
  #define DEFCopterType               0x50          // (CC) P (ASCII) Plus

  // order to put into execution [IDX]
  #define DEFMotorNo1_OrderIDX           0          // MotorNo1(>)     0 <=> 1st
  #define DEFMotorNo2_OrderIDX           2          // MotorNo2(>)     2 <=> 3rd
  #define DEFMotorNo3_OrderIDX           1          // MotorNo3(<)     1 <=> 2nd
  #define DEFMotorNo4_OrderIDX           3          // MotorNo4(<)     3 <=> 4th
#else

#ifdef Quadro_X
//------------------------------------------------------------------------------------------------------------
// Quadro X    - hardware configuration
//               motor rotating direction: (>) CW - clockwise / (<) CCW - counterclockwise
//
//                            Nick (+ x-axis)
//
//                     MotorNo4(<) o     o MotorNo1(>)
//                                   \ /
//  Roll (+ y-axis)                  F|C                 Roll (- y-axis)
//                                   / \
//                     MotorNo2(>) o     o MotorNo3(<)
//
//                            Nick (- x-axis)
//------------------------------------------------------------------------------------------------------------
  #define DEFMotorsCount                 4          // (CC) Quadrocopter
  #define DEFCopterType               0x58          // (CC) X (ASCII) X

  // order to put into execution [IDX]
  #define DEFMotorNo1_OrderIDX           0          // MotorNo1(>)     0 <=> 1st
  #define DEFMotorNo2_OrderIDX           2          // MotorNo2(>)     2 <=> 3rd
  #define DEFMotorNo3_OrderIDX           1          // MotorNo3(<)     1 <=> 2nd
  #define DEFMotorNo4_OrderIDX           3          // MotorNo4(<)     3 <=> 4th
#else

#ifdef Okto_Plus
//------------------------------------------------------------------------------------------------------------
// Okto Plus(A)- hardware configuration
//               motor rotating direction: (>) CW - clockwise / (<) CCW - counterclockwise
//
//                        Nick (+ x-axis)
//
//                                    o MotorNo1(>)
//                     MotorNo8(<) o  |  o MotorNo2(<)
//                                   \|/
//  Roll (+ y-axis)  MotorNo7(>)  o--F|C--o MotorNo3(>)  Roll (- y-axis)
//                                   /|\
//                     MotorNo6(<) o  |  o MotorNo4(<)
//                        MotorNo5(>) o
//
//                        Nick (- x-axis)
//------------------------------------------------------------------------------------------------------------
  #define DEFMotorsCount                 8          // (CC) Oktocopter
  #define DEFCopterType               0x50          // (CC) P (ASCII) Plus

  // order to put into execution [IDX]
  #define DEFMotorNo1_OrderIDX           0          // MotorNo1(>)     0 <=> 1st
  #define DEFMotorNo2_OrderIDX           1          // MotorNo2(<)     1 <=> 2nd
  #define DEFMotorNo3_OrderIDX           2          // MotorNo3(>)     2 <=> 3rd
  #define DEFMotorNo4_OrderIDX           3          // MotorNo4(<)     3 <=> 4th
  #define DEFMotorNo5_OrderIDX           4          // MotorNo5(>)     4 <=> 5th
  #define DEFMotorNo6_OrderIDX           5          // MotorNo6(<)     5 <=> 6th
  #define DEFMotorNo7_OrderIDX           6          // MotorNo7(>)     6 <=> 7th
  #define DEFMotorNo8_OrderIDX           7          // MotorNo8(<)     7 <=> 8th

/* *** rft !!!not tested!!! ***
//------------------------------------------------------------------------------------------------------------
// Okto Plus(B)- hardware configuration
//               motor rotating direction: (>) CW - clockwise / (<) CCW - counterclockwise
//
//                        Nick (+ x-axis)
//
//                                    o MotorNo1(>)
//                     MotorNo8(<) o  |  o MotorNo2(>)
//                                   \|/
//  Roll (+ y-axis)  MotorNo7(<)  o--F|C--o MotorNo3(<)  Roll (- y-axis)
//                                   /|\
//                     MotorNo6(>) o  |  o MotorNo4(<)
//                        MotorNo5(>) o
//
//                        Nick (- x-axis)
//------------------------------------------------------------------------------------------------------------
  #define DEFMotorsCount                 8          // (CC) Oktocopter
  #define DEFCopterType               0x50          // (CC) P (ASCII) Plus

  // order to put into execution [IDX]
  #define DEFMotorNo1_OrderIDX           0          // MotorNo1(>)     0 <=> 1st
  #define DEFMotorNo2_OrderIDX           4          // MotorNo2(>)     4 <=> 5th
  #define DEFMotorNo3_OrderIDX           1          // MotorNo3(<)     1 <=> 2nd
  #define DEFMotorNo4_OrderIDX           5          // MotorNo4(<)     5 <=> 6th
  #define DEFMotorNo5_OrderIDX           2          // MotorNo5(>)     2 <=> 3rd
  #define DEFMotorNo6_OrderIDX           6          // MotorNo6(>)     6 <=> 7th
  #define DEFMotorNo7_OrderIDX           3          // MotorNo7(<)     3 <=> 4th
  #define DEFMotorNo8_OrderIDX           7          // MotorNo8(<)     7 <=> 8th
*/

#else
#error "*** copter type ***  not defined!!!! (MOTOR.h) ***"
#endif
#endif
#endif

//------------------------------------------------------------------------------------------------------------
// ***** defaults: Motors - common

#define DEFMotorSetpointMIN             10          // [MotorStep] Min Motors RPM Setpoint
#define DEFMotorSetpointMAX            255          // [MotorStep] Max Motors RPM Setpoint

// Brushless Controller adress (i2c-bus) for MotorNo1,..,MotorNo8
// bit7-1[0x52+2*(MotorNo99-1)] bit0[0:write; 1:read]
#define DEFMotorNo1_BLCtrlADR         0x29//0x52          // (CC) BL Ctrl adresse for MotorNo1
#define DEFMotorNo2_BLCtrlADR         0x2a//0x54          // (CC) BL Ctrl adresse for MotorNo2
#define DEFMotorNo3_BLCtrlADR         0x2b//0x56          // (CC) BL Ctrl adresse for MotorNo3
#define DEFMotorNo4_BLCtrlADR         0x2c//0x58          // (CC) BL Ctrl adresse for MotorNo4
#define DEFMotorNo5_BLCtrlADR         0x5a          // (CC) BL Ctrl adresse for MotorNo5
#define DEFMotorNo6_BLCtrlADR         0x5c          // (CC) BL Ctrl adresse for MotorNo6
#define DEFMotorNo7_BLCtrlADR         0x5e          // (CC) BL Ctrl adresse for MotorNo7
#define DEFMotorNo8_BLCtrlADR         0x60          // (CC) BL Ctrl adresse for MotorNo8

//defines for SetPwmMotor toSet parameter:
#define DEFMotorNo1_PWM         0b1
#define DEFMotorNo2_PWM         0b10
#define DEFMotorNo3_PWM         0b100
#define DEFMotorNo4_PWM         0b1000
#define DEFMotorNo5_PWM         0b10000
#define DEFMotorNo6_PWM         0b100000
#define DEFMotorNo7_PWM         0b1000000
#define DEFMotorNo8_PWM		  	0b10000000
#define DEFMotorALL_PWM		  	0xFF
#define DEFMotorCW_PWM_  		0x55
#define DEFMotorCCW_PWM	  		0XAA

#define MAXPitchRollAngel 5
#define MAXBeschleunigung

//structs
typedef struct{
double heightCM; // Flughöhe
double yawAngle; // ZU dem absolutem Winkel ausrichten
}maneuver;

void InitMotor();
void SetMotorExecutionOrder();
void SetPwmMotor(char toSet , int pwmValue, int optFlag);
int GetPwmMotor(int motorNumber);
void InitMotorTimer();
void SetFlagRunSendPwmToMotor(char value);
char GetFlagRunSendPwmToMotor();
void IsrSetFlag();
void sendPwmToMotor();
void GetBLCtrlADRExecuteOrder(char BLCtrlADRExecuteOrder[]);

void SendManeuver(maneuver m);
