/*!
 * \file _main.c
 */
/*
 * main.cpp
 *
 *  Created on: 29.03.2015
 *      Author: user
 */

#include <stdio.h>
#include "./sig/matrixLib/matrixLib.h"

static	double l_MatrixA_f64[3][3]={{1,2,1},{2,5,4},{1,4,9}};
//static	double l_MatrixA_f64[3][3]={{4,-14,-2},{-14,65,3},{-2,3,3}};
//static	double l_MatrixA_f64[2][3]={{1,2,9},{2,5,9}};
//static	double l_MatrixA_f64[1][3]={{1,2,9}};
static	double l_MatrixB_f64[3][3]={{3,6,7},{2,5,9},{4,6,8}};
//static	double l_MatrixB_f64[3][2]={{3,6},{2,5},{4,6}};
static	double l_outputMatrix_f64[3][3]={{0,0,0},{0,0,0},{0,0,0}};
//static	double l_outputMatrix_f64[3][2]={{0,0},{0,0},{0,0}};


int _main (void)
{



	while(1)
	{
		g_sigMath_matrixEye_bl((double*)l_outputMatrix_f64,3,3);
		sleep(1);
		g_sigMath_matrixInitialize_bl((double*)l_outputMatrix_f64,3,3,1);
		sleep(1);
		g_sigMath_matrixMultiplikation_bl((double*)l_outputMatrix_f64,(double*)l_MatrixA_f64,3,3,(double*)l_MatrixB_f64,3,3);
		sleep(1);
		g_sigMath_matrixAddition_bl((double*)l_outputMatrix_f64,(double*)l_MatrixA_f64,3,3,(double*)l_MatrixB_f64,3,3);
		sleep(1);
		g_sigMath_matrixSubtraktion_bl((double*)l_outputMatrix_f64,(double*)l_MatrixA_f64,3,3,(double*)l_MatrixB_f64,3,3);
		sleep(1);
		g_sigMath_matrixAssignment_bl((double*)l_outputMatrix_f64,3,3,(double*)l_MatrixA_f64,3,3);
		sleep(1);
		g_sigMath_matrixTransponiert_bl((double*)l_outputMatrix_f64,(double*)l_MatrixA_f64,3,3);
		sleep(1);
		g_sigMath_matrixInverse_bl((double*)l_outputMatrix_f64,(double*)l_MatrixA_f64,3,3);
		sleep(1);
	}

	return 0;
}



