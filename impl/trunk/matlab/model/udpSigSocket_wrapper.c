

/*
 * Include Files
 *
 */
#include "simstruc.h"



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
#include "../udpSensorLib.h"
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/*extern int getSocketNumber();*/
#ifdef MATLAB_MEX_FILE
extern int g_udp_initConnection_i32(const unsigned char* const f_destIpv4_rg4ui8, unsigned short f_udpConnectionPort_ui16 );
#endif
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void udpSigSocket_Outputs_wrapper(real_T *Raw_Accelerometer_xyz,
			real_T *Raw_Gyrometer_rpy,
			real_T *Raw_Compass_xyz,
			real_T *Raw_Barometer_z,
			real_T *Raw_Temperature,
			real_T *Kalman_Angles_rpy,
			real_T *Complementary_Angles_rpy,
			const real_T *sampleTime, const int_T p_width0,
			const real_T *ListenPort, const int_T p_width1,
			SimStruct *S)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
      y0[0] = u0[0]; 
 For complex signals use: y0[0].re = u0[0].re; 
      y0[0].im = u0[0].im;
      y1[0].re = u1[0].re;
      y1[0].im = u1[0].im;
*/
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}
