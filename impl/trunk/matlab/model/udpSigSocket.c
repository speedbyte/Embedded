/*!
 * \file udpSigSocket.c
 */
/*
 * Important remark:
 * =================
 * To compile this S-function code, change into the MasterQuad2015
 * SVN-tree (/impl/trunk/matlab/model) and type the command:
 *             >> mex udpSigSocket.c ../*.c
 * Otherwise, the necessary libraries cannot be found by the mex-compiler!
 *
 * File: udpSigSocket.c
 *
 *
  *
  *   --- THIS FILE GENERATED BY S-FUNCTION BUILDER: 3.0 ---
  *
  *   This file is an S-function produced by the S-Function
  *   Builder which only recognizes certain fields.  Changes made
  *   outside these fields will be lost the next time the block is
  *   used to load, edit, and resave this file. This file will be overwritten
  *   by the S-function Builder block. If you want to edit this file by hand, 
  *   you must change it only in the area defined as:  
  *
  *        %%%-SFUNWIZ_defines_Changes_BEGIN
  *        #define NAME 'replacement text' 
  *        %%% SFUNWIZ_defines_Changes_END
  *
  *   DO NOT change NAME--Change the 'replacement text' only.
  *
  *   For better compatibility with the Simulink Coder, the
  *   "wrapper" S-function technique is used.  This is discussed
  *   in the Simulink Coder's Manual in the Chapter titled,
  *   "Wrapper S-functions".
  *
  *  -------------------------------------------------------------------------
  * | See matlabroot/simulink/src/sfuntmpl_doc.c for a more detailed template |
  *  ------------------------------------------------------------------------- 
 * Created: Mon Jun  1 22:22:34 2015
 * 
 *
 */

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME udpSigSocket
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/* %%%-SFUNWIZ_defines_Changes_BEGIN --- EDIT HERE TO _END */
#define NUM_INPUTS           0

#define NUM_OUTPUTS          7
/* Output Port  0 */
#define OUT_PORT_0_NAME      Raw_Accelerometer_xyz
#define OUTPUT_0_WIDTH       3
#define OUTPUT_DIMS_0_COL    1
#define OUTPUT_0_DTYPE       real_T
#define OUTPUT_0_COMPLEX     COMPLEX_NO
#define OUT_0_FRAME_BASED    FRAME_NO
#define OUT_0_BUS_BASED      0
#define OUT_0_BUS_NAME       
#define OUT_0_DIMS           1-D
#define OUT_0_ISSIGNED        1
#define OUT_0_WORDLENGTH      8
#define OUT_0_FIXPOINTSCALING 1
#define OUT_0_FRACTIONLENGTH  3
#define OUT_0_BIAS            0
#define OUT_0_SLOPE           0.125
/* Output Port  1 */
#define OUT_PORT_1_NAME      Raw_Gyrometer_rpy
#define OUTPUT_1_WIDTH       3
#define OUTPUT_DIMS_1_COL    1
#define OUTPUT_1_DTYPE       real_T
#define OUTPUT_1_COMPLEX     COMPLEX_NO
#define OUT_1_FRAME_BASED    FRAME_NO
#define OUT_1_BUS_BASED      0
#define OUT_1_BUS_NAME       
#define OUT_1_DIMS           1-D
#define OUT_1_ISSIGNED        1
#define OUT_1_WORDLENGTH      8
#define OUT_1_FIXPOINTSCALING 1
#define OUT_1_FRACTIONLENGTH  3
#define OUT_1_BIAS            0
#define OUT_1_SLOPE           0.125
/* Output Port  2 */
#define OUT_PORT_2_NAME      Raw_Compass_xyz
#define OUTPUT_2_WIDTH       3
#define OUTPUT_DIMS_2_COL    1
#define OUTPUT_2_DTYPE       real_T
#define OUTPUT_2_COMPLEX     COMPLEX_NO
#define OUT_2_FRAME_BASED    FRAME_NO
#define OUT_2_BUS_BASED      0
#define OUT_2_BUS_NAME       
#define OUT_2_DIMS           1-D
#define OUT_2_ISSIGNED        1
#define OUT_2_WORDLENGTH      8
#define OUT_2_FIXPOINTSCALING 1
#define OUT_2_FRACTIONLENGTH  3
#define OUT_2_BIAS            0
#define OUT_2_SLOPE           0.125
/* Output Port  3 */
#define OUT_PORT_3_NAME      Raw_Barometer_z
#define OUTPUT_3_WIDTH       1
#define OUTPUT_DIMS_3_COL    1
#define OUTPUT_3_DTYPE       real_T
#define OUTPUT_3_COMPLEX     COMPLEX_NO
#define OUT_3_FRAME_BASED    FRAME_NO
#define OUT_3_BUS_BASED      0
#define OUT_3_BUS_NAME       
#define OUT_3_DIMS           1-D
#define OUT_3_ISSIGNED        1
#define OUT_3_WORDLENGTH      8
#define OUT_3_FIXPOINTSCALING 1
#define OUT_3_FRACTIONLENGTH  3
#define OUT_3_BIAS            0
#define OUT_3_SLOPE           0.125
/* Output Port  4 */
#define OUT_PORT_4_NAME      Raw_Temperature
#define OUTPUT_4_WIDTH       1
#define OUTPUT_DIMS_4_COL    1
#define OUTPUT_4_DTYPE       real_T
#define OUTPUT_4_COMPLEX     COMPLEX_NO
#define OUT_4_FRAME_BASED    FRAME_NO
#define OUT_4_BUS_BASED      0
#define OUT_4_BUS_NAME       
#define OUT_4_DIMS           1-D
#define OUT_4_ISSIGNED        1
#define OUT_4_WORDLENGTH      8
#define OUT_4_FIXPOINTSCALING 1
#define OUT_4_FRACTIONLENGTH  3
#define OUT_4_BIAS            0
#define OUT_4_SLOPE           0.125
/* Output Port  5 */
#define OUT_PORT_5_NAME      Kalman_Angles_rpy
#define OUTPUT_5_WIDTH       3
#define OUTPUT_DIMS_5_COL    1
#define OUTPUT_5_DTYPE       real_T
#define OUTPUT_5_COMPLEX     COMPLEX_NO
#define OUT_5_FRAME_BASED    FRAME_NO
#define OUT_5_BUS_BASED      0
#define OUT_5_BUS_NAME       
#define OUT_5_DIMS           1-D
#define OUT_5_ISSIGNED        1
#define OUT_5_WORDLENGTH      8
#define OUT_5_FIXPOINTSCALING 1
#define OUT_5_FRACTIONLENGTH  3
#define OUT_5_BIAS            0
#define OUT_5_SLOPE           0.125
/* Output Port  6 */
#define OUT_PORT_6_NAME      Complementary_Angles_rpy
#define OUTPUT_6_WIDTH       3
#define OUTPUT_DIMS_6_COL    1
#define OUTPUT_6_DTYPE       real_T
#define OUTPUT_6_COMPLEX     COMPLEX_NO
#define OUT_6_FRAME_BASED    FRAME_NO
#define OUT_6_BUS_BASED      0
#define OUT_6_BUS_NAME       
#define OUT_6_DIMS           1-D
#define OUT_6_ISSIGNED        1
#define OUT_6_WORDLENGTH      8
#define OUT_6_FIXPOINTSCALING 1
#define OUT_6_FRACTIONLENGTH  3
#define OUT_6_BIAS            0
#define OUT_6_SLOPE           0.125

#define NPARAMS              2
/* Parameter  1 */
#define PARAMETER_0_NAME      sampleTime
#define PARAMETER_0_DTYPE     real_T
#define PARAMETER_0_COMPLEX   COMPLEX_NO
/* Parameter  2 */
#define PARAMETER_1_NAME      ListenPort
#define PARAMETER_1_DTYPE     real_T
#define PARAMETER_1_COMPLEX   COMPLEX_NO

#define SAMPLE_TIME_0        0.1
#define NUM_DISC_STATES      0
#define DISC_STATES_IC       [0]
#define NUM_CONT_STATES      0
#define CONT_STATES_IC       [0]

#define SFUNWIZ_GENERATE_TLC 0
#define SOURCEFILES "__SFB__"
#define PANELINDEX           6
#define USE_SIMSTRUCT        1
#define SHOW_COMPILE_STEPS   0                   
#define CREATE_DEBUG_MEXFILE 0
#define SAVE_CODE_ONLY       0
#define SFUNWIZ_REVISION     3.0
/* %%%-SFUNWIZ_defines_Changes_END --- EDIT HERE TO _BEGIN */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "simstruc.h"

#include "../udpSigLib.h"

#define PARAM_DEF0(S) ssGetSFcnParam(S, 0)
#define PARAM_DEF1(S) ssGetSFcnParam(S, 1)

#define IS_PARAM_DOUBLE(pVal) (mxIsNumeric(pVal) && !mxIsLogical(pVal) &&\
!mxIsEmpty(pVal) && !mxIsSparse(pVal) && !mxIsComplex(pVal) && mxIsDouble(pVal))

#define REMOTE_HOST_IPADDR_RG4UI8	{192,168,22,161}
#define REMOTE_HOST_PORT_UI16		5000

static int	m_simSocket_i32 = 0;

/*====================*
 * S-function methods *
 *====================*/
#define MDL_CHECK_PARAMETERS
 #if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
   /* Function: mdlCheckParameters =============================================
     * Abstract:
     *    Validate our parameters to verify they are okay.
     */
    static void mdlCheckParameters(SimStruct *S)
    {
     int paramIndex  = 0;
     bool validParam = false;
     /* All parameters must match the S-function Builder Dialog */
     

	 {
	  const mxArray *pVal0 = ssGetSFcnParam(S,0);
	  if (!IS_PARAM_DOUBLE(pVal0)) {
	    validParam = true;
	    paramIndex = 0;
	    goto EXIT_POINT;
	  }
	 }

	 {
	  const mxArray *pVal1 = ssGetSFcnParam(S,1);
	  if (!IS_PARAM_DOUBLE(pVal1)) {
	    validParam = true;
	    paramIndex = 1;
	    goto EXIT_POINT;
	  }
	 }
      
     EXIT_POINT:
      if (validParam) {
          char parameterErrorMsg[1024];
          sprintf(parameterErrorMsg, "The data type and or complexity of parameter  %d does not match the "
                  "information specified in the S-function Builder dialog. "
                  "For non-double parameters you will need to cast them using int8, int16, "
                  "int32, uint8, uint16, uint32 or boolean.", paramIndex + 1);
	  ssSetErrorStatus(S,parameterErrorMsg);
      }
	return;
    }
 #endif /* MDL_CHECK_PARAMETERS */
/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(outputDimsInfo);
    ssSetNumSFcnParams(S, NPARAMS);  /* Number of expected parameters */
      #if defined(MATLAB_MEX_FILE)
	if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {
	  mdlCheckParameters(S);
	  if (ssGetErrorStatus(S) != NULL) {
	    return;
	  }
	 } else {
	   return; /* Parameter mismatch will be reported by Simulink */
	 }
      #endif

    ssSetNumContStates(S, NUM_CONT_STATES);
    ssSetNumDiscStates(S, NUM_DISC_STATES);

    if (!ssSetNumInputPorts(S, NUM_INPUTS)) return;

    if (!ssSetNumOutputPorts(S, NUM_OUTPUTS)) return;
    /* Output Port 0 */
    ssSetOutputPortWidth(S, 0, OUTPUT_0_WIDTH);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 0, OUTPUT_0_COMPLEX);
    /* Output Port 1 */
    ssSetOutputPortWidth(S, 1, OUTPUT_1_WIDTH);
    ssSetOutputPortDataType(S, 1, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 1, OUTPUT_1_COMPLEX);
    /* Output Port 2 */
    ssSetOutputPortWidth(S, 2, OUTPUT_2_WIDTH);
    ssSetOutputPortDataType(S, 2, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 2, OUTPUT_2_COMPLEX);
    /* Output Port 3 */
    ssSetOutputPortWidth(S, 3, OUTPUT_3_WIDTH);
    ssSetOutputPortDataType(S, 3, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 3, OUTPUT_3_COMPLEX);
    /* Output Port 4 */
    ssSetOutputPortWidth(S, 4, OUTPUT_4_WIDTH);
    ssSetOutputPortDataType(S, 4, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 4, OUTPUT_4_COMPLEX);
    /* Output Port 5 */
    ssSetOutputPortWidth(S, 5, OUTPUT_5_WIDTH);
    ssSetOutputPortDataType(S, 5, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 5, OUTPUT_5_COMPLEX);
    /* Output Port 6 */
    ssSetOutputPortWidth(S, 6, OUTPUT_6_WIDTH);
    ssSetOutputPortDataType(S, 6, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 6, OUTPUT_6_COMPLEX);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
		     SS_OPTION_WORKS_WITH_CODE_REUSE));
}

/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    double* l_sampleTime_pf64;
    
    //get smaple time, configured in block parameters
    l_sampleTime_pf64 = mxGetPr( ssGetSFcnParam(S, 0) );
    printf("Set sampling time to %lf\n",*l_sampleTime_pf64);
    
    ssSetSampleTime(S, 0, (time_T)*l_sampleTime_pf64 );
    ssSetOffsetTime(S, 0, 0.0);
}


#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
	  unsigned char l_remoteIpAddr_rg4ui8[4] = REMOTE_HOST_IPADDR_RG4UI8;
      double* l_listenPort_pf64;
    
      //get smaple time, configured in block parameters
      l_listenPort_pf64 = mxGetPr( ssGetSFcnParam(S, 1) );
      printf("Listening to port %lf\n",*l_listenPort_pf64);
	  
      m_simSocket_i32 = g_halMatlab_initConnection_i32( l_remoteIpAddr_rg4ui8 , (unsigned short)*l_listenPort_pf64);
  }
#endif /*  MDL_START */

#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
   ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}
/* Function: mdlOutputs =======================================================
 *
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
    real_T        *Raw_Accelerometer_xyz  = (real_T *)ssGetOutputPortRealSignal(S,0);
    real_T        *Raw_Gyrometer_rpy  = (real_T *)ssGetOutputPortRealSignal(S,1);
    real_T        *Raw_Compass_xyz  = (real_T *)ssGetOutputPortRealSignal(S,2);
    real_T        *Raw_Barometer_z  = (real_T *)ssGetOutputPortRealSignal(S,3);
    real_T        *Raw_Temperature  = (real_T *)ssGetOutputPortRealSignal(S,4);
    real_T        *Kalman_Angles_rpy  = (real_T *)ssGetOutputPortRealSignal(S,5);
    real_T        *Complementary_Angles_rpy  = (real_T *)ssGetOutputPortRealSignal(S,6);
    const int_T   p_width0  = mxGetNumberOfElements(PARAM_DEF0(S));
    const int_T   p_width1  = mxGetNumberOfElements(PARAM_DEF1(S));
    const real_T  *sampleTime  = (const real_T *)mxGetData(PARAM_DEF0(S));
    const real_T  *ListenPort  = (const real_T *)mxGetData(PARAM_DEF1(S));

    halMatlab_rtSigAllStatePayload 		l_udpPayload_st;

	l_udpPayload_st = g_halMatlab_recvSigAllStates_bl( m_simSocket_i32 );

    printf("Remote time: %ld.%ld\n", l_udpPayload_st.timestamp_st.tv_sec,l_udpPayload_st.timestamp_st.tv_nsec);
    
	Raw_Accelerometer_xyz[0] = l_udpPayload_st.imuState_st.acc.x_f64;
	Raw_Accelerometer_xyz[1] = l_udpPayload_st.imuState_st.acc.y_f64;
	Raw_Accelerometer_xyz[2] = l_udpPayload_st.imuState_st.acc.z_f64;

	Raw_Gyrometer_rpy[0] = l_udpPayload_st.imuState_st.gyro.l_roll_f64;
	Raw_Gyrometer_rpy[1] = l_udpPayload_st.imuState_st.gyro.l_pitch_f64;
	Raw_Gyrometer_rpy[2] = l_udpPayload_st.imuState_st.gyro.l_yaw_f64;

	Raw_Compass_xyz[0] = l_udpPayload_st.imuState_st.mag.x_f64;
	Raw_Compass_xyz[1] = l_udpPayload_st.imuState_st.mag.y_f64;
	Raw_Compass_xyz[2] = l_udpPayload_st.imuState_st.mag.z_f64;

	Raw_Barometer_z[0] = l_udpPayload_st.imuState_st.pressure_f64;

	Raw_Temperature[0] = l_udpPayload_st.imuState_st.temperature_f64;
    
    Kalman_Angles_rpy[0] = l_udpPayload_st.kalmanSigState_st.roll_f64;
	Kalman_Angles_rpy[1] = l_udpPayload_st.kalmanSigState_st.pitch_f64;
	Kalman_Angles_rpy[2] = l_udpPayload_st.kalmanSigState_st.yaw_f64;
    
    Complementary_Angles_rpy[0] = l_udpPayload_st.complementarySigState_st.roll_f64;
	Complementary_Angles_rpy[1] = l_udpPayload_st.complementarySigState_st.pitch_f64;
	Complementary_Angles_rpy[2] = l_udpPayload_st.complementarySigState_st.yaw_f64;
}



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    unsigned int l_closeState_ui32;
    
    printf("Closing socket\n");
    
    l_closeState_ui32 = g_halMatlab_closeSocket_bl(m_simSocket_i32);
}
#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


