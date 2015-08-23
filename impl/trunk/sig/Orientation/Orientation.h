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
#define M_SIGORI_SIZEOFARRAY_UI8	3
//define PI
#define M_SIGORI_PI_F64				3.14159

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
}sigOri_orientationAngles;

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
sigOri_orientationAngles g_sigOri_getAnglesComplementary_bl(void);
double g_sigOri_getPitchComplementary_bl(void);
double g_sigOri_getRollComplementary_bl(void);
double g_sigOri_getYawComplementary_bl(void);

sigOri_orientationAngles g_sigOri_getAnglesKalman_bl(void);
double g_sigOri_getPitchKalman_bl(void);
double g_sigOri_getRollKalman_bl(void);
double g_sigOri_getYawKalman_bl(void);

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
unsigned int g_sigOri_initImuSensors_bl(void);
unsigned int g_sigOri_initMatrices_bl(void);
void g_sigOri_initBuildReferenceValues_bl();

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
void g_sigOri_calcKalmanOrientation_bl(void);
void g_sigOri_calcComplementaryOrientation_bl(void);


#endif /* SIG_KALMANORIENTATION_KALMANORIENTATION_H_ */
