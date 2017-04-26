/*!
 * \file matrixLib.h
 */
/*
 * matrixLib.h
 *
 *  Created on: May 17, 2015
 *      Author: user
 */

#ifndef SIG_MATRIXLIB_MATRIXLIB_H_
#define SIG_MATRIXLIB_MATRIXLIB_H_

#define M_ROWS_UI8								3
#define M_COLS_UI8								3

#define M_SIG_MATRIXLIB_SUCCESS_BOOL 			0
#define M_SIG_MATRIXLIB_FAILED_BOOL 			1


/* -----------------------------------------------------------------------
 * AUTHOR: Oliver Breuning (olbrgs00)
 * DATE OF CREATION: 2015/05/17
 *
 * DESCRIPTION:
 * General mathematical functions for Matrices
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
//multiplication of two matrices --> f_matrixResult_pf64 = f_matrixA_pf64 * f_matrixB_pf64
unsigned int g_sigMath_matrixMultiplikation_bool(double* f_matrixResult_pf64,
												double* f_matrixA_pf64,unsigned int f_nrOfRowsA_ui32,unsigned int f_nrOfColsA_ui32,
												double* f_matrixB_pf64,unsigned int f_nrOfRowsB_ui32,unsigned int f_nrOfColsB_ui32);

//Addition of two matrices --> f_matrixResult_pf64 = f_matrixA_pf64 + f_matrixB_pf64
unsigned int g_sigMath_matrixAddition_bool(double* f_matrixResult_pf64,
												double* f_matrixA_pf64,unsigned int f_nrOfRowsA_ui32,unsigned int f_nrOfColsA_ui32,
												double* f_matrixB_pf64,unsigned int f_nrOfRowsB_ui32,unsigned int f_nrOfColsB_ui32);
//unsigned int g_sigMath_matrixAddition_bool(void);



//Subtraction of two matrices --> f_matrixResult_pf64 = f_matrixA_pf64 - f_matrixB_pf64
unsigned int g_sigMath_matrixSubtraktion_bool(double* f_matrixResult_pf64,
												double* f_matrixA_pf64,unsigned int f_nrOfRowsA_ui32,unsigned int f_nrOfColsA_ui32,
												double* f_matrixB_pf64,unsigned int f_nrOfRowsB_ui32,unsigned int f_nrOfColsB_ui32);

//Assign a matrix to another --> f_matrixResult_pf64 = f_matrix_pf64
unsigned int g_sigMath_matrixAssignment_bool(double* f_matrixResult_pf64,unsigned int f_nrOfRowsResult_ui32,unsigned int f_nrOfColsResult_ui32,
												double* f_matrix_pf64,unsigned int f_nrOfRows_ui32,unsigned int f_nrOfCols_ui32);

//Transponize a matrix --> f_matrixResult_pf64 = f_matrix_pf64'
unsigned int g_sigMath_matrixTransponiert_bool(double* f_matrixResult_pf64,
												double* f_matrix_pf64,unsigned int f_nrOfRows_ui32,unsigned int f_nrOfCols_ui32);

//Invert a matrix --> f_matrixResult_pf64 = f_matrix_pf64^(-1)
unsigned int g_sigMath_matrixInverse_bool(double* f_matrixResult_pf64,
												double* f_matrixA_pf64,unsigned int f_nrOfRowsA_ui32,unsigned int f_nrOfColsA_ui32);

//Initialize all elements of a matrix with a given value --> f_matrixResult_pf64[xx][xx] = f_setValue_ui32
unsigned int g_sigMath_matrixInitialize_bool(double* f_matrixResult_pf64,unsigned int f_nrOfRows_ui32,unsigned int f_nrOfCols_ui32, double f_setValue_f64);

//Build a eye matrix --> f_matrixResult_pf64[xx][xx] = 1
unsigned int g_sigMath_matrixEye_bool(double* f_matrixResult_pf64,
		unsigned int f_nrOfRows_ui32, unsigned int f_nrOfCols_ui32);

#endif /* SIG_MATRIXLIB_MATRIXLIB_H_ */
