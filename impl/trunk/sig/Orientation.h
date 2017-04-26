/*!
 * \file Orientation.h
 */
/*
 * Orientation.h
 *
 *  Created on: May 17, 2015
 *      Author: user
 */

#ifndef SIG_KALMANORIENTATION_KALMANORIENTATION_H_
#define SIG_KALMANORIENTATION_KALMANORIENTATION_H_

//define array and matrix size
#define SIZEOFARRAY_UI8	3
//define PI
#define PI_F64				3.14159

/*!**********************************************************************
 * \author 	Oliver Breuning (olbrgs00)
 * \date 	2015/05/31
 *
 * \brief	Struct of rotation angles
 * \details	Stores all calculated sensor rotations from the Inertial
 * 			measurement unit within one dedicated type.
 * 			All values within are floats
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
typedef struct{
	double roll_f64;
	double pitch_f64;
	double yaw_f64;
}HAL_ANGLE_PAYLOAD_ST;

/* -----------------------------------------------------------------------
 * AUTHOR: Oliver Breuning (olbrgs00)
 * DATE OF CREATION: 2015/05/31
 *
 * DESCRIPTION:
 * Interfaces of getting rotation angles
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
HAL_ANGLE_PAYLOAD_ST g_getAnglesComplementary_bool(void);
double g_getPitchComplementary_bool(void);
double g_getRollComplementary_bool(void);
double g_getYawComplementary_bool(void);

HAL_ANGLE_PAYLOAD_ST g_getAnglesKalman_bool(void);
double g_getPitchKalman_bool(void);
double g_getRollKalman_bool(void);
double g_getYawKalman_bool(void);

HAL_ANGLE_PAYLOAD_ST g_getAnglesGyroPerStep_bool(void);
HAL_ANGLE_PAYLOAD_ST g_getAnglesAccMagCalc_bool(void);

/* -----------------------------------------------------------------------
 * AUTHOR: Oliver Breuning (olbrgs00)
 * DATE OF CREATION: 2015/05/31
 *
 * DESCRIPTION:
 * Initialization functions
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
unsigned int g_initImuSensors_bool(void);
unsigned int g_initMatrices_bool(void);
void g_initBuildReferenceValues_bool();

/* -----------------------------------------------------------------------
 * AUTHOR: Oliver Breuning (olbrgs00)
 * DATE OF CREATION: 2015/05/31
 *
 * DESCRIPTION:
 * Functions calculating of the orientation
 * (Kalman-Filter or Complementary-Filter)
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
void g_calcKalmanOrientation_bool(void);
void g_calcComplementaryOrientation_bool(void);



#endif /* SIG_KALMANORIENTATION_KALMANORIENTATION_H_ */
