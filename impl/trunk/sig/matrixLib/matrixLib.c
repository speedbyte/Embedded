/*!
 * \file matrixLib.c
 */
/*
 * matrixLib.c
 *
 *  Created on: May 17, 2015
 *      Author: user
 */

#include "matrixLib.h"
#include <math.h>
//memcpy(dest, src, strlen(src)+1);


unsigned int m_getIndex_i32(unsigned int f_maxCol_ui32,unsigned int f_row_ui32,unsigned int f_col_ui32)
{
    return (f_maxCol_ui32*f_row_ui32+f_col_ui32);
}



/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/18
 *
 * \brief    Multiplication of two matrices
 * \details    Multiplies two matrices and stores it in a resulting matrix
 *             f_matrixResult_pf64=f_matrixA_pf64*f_matrixB_pf64
 *
 *     \param[in]    1.Param: Result matrix with double values as Pointer
 *                 2.Param: Matrix A
 *                 3.Param: Number of rows of Matrix A
 *                 4.Param: Number of columns Matrix A
 *                 5.Param: Matrix B
 *                 6.Param: Number of rows of Matrix B
 *                 7.Param: Number of columns Matrix B
 *     \param[out] returns a boolean value, indicating the occurence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_sigMath_matrixMultiplikation_bool(
        double* f_matrixResult_pf64, double* f_matrixA_pf64,
        unsigned int f_nrOfRowsA_ui32, unsigned int f_nrOfColsA_ui32,
        double* f_matrixB_pf64, unsigned int f_nrOfRowsB_ui32,
        unsigned int f_nrOfColsB_ui32)
{
    unsigned int l_rowCounter_ui32=0;
    unsigned int l_colCounter_ui32=0;
    unsigned int l_innerCounter_ui32=0;
    double l_temporalStorage_f64=0;

    if(f_nrOfColsA_ui32!=f_nrOfRowsB_ui32)
    {return M_SIG_MATRIXLIB_FAILED_BL;}
    else
    {
        for(l_rowCounter_ui32=0;l_rowCounter_ui32<f_nrOfRowsA_ui32;l_rowCounter_ui32++)
        {
            for(l_colCounter_ui32=0;l_colCounter_ui32<f_nrOfColsB_ui32;l_colCounter_ui32++)
            {
                for(l_innerCounter_ui32=0;l_innerCounter_ui32<f_nrOfColsA_ui32;l_innerCounter_ui32++)
                {
                    l_temporalStorage_f64+=f_matrixA_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_innerCounter_ui32)]*
                            f_matrixB_pf64[m_getIndex_i32(f_nrOfColsB_ui32,l_innerCounter_ui32,l_colCounter_ui32)];
                }
                f_matrixResult_pf64[m_getIndex_i32(f_nrOfColsB_ui32,l_rowCounter_ui32,l_colCounter_ui32)]=l_temporalStorage_f64;
                l_temporalStorage_f64=0;
            }
        }
        return M_SIG_MATRIXLIB_SUCCESS_BL;
    }
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/18
 *
 * \brief    Addition of two matrices
 * \details    Add two matrices and stores it in a resulting matrix
 *             f_matrixResult_pf64=f_matrixA_pf64+f_matrixB_pf64
 *
 *     \param[in]    1.Param: Result matrix with double values as Pointer
 *                 2.Param: Matrix A
 *                 3.Param: Number of rows of Matrix A
 *                 4.Param: Number of columns Matrix A
 *                 5.Param: Matrix B
 *                 6.Param: Number of rows of Matrix B
 *                 7.Param: Number of columns Matrix B
 *     \param[out] returns a boolean value, indicating the occurence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_sigMath_matrixAddition_bool(double* f_matrixResult_pf64,
        double* f_matrixA_pf64, unsigned int f_nrOfRowsA_ui32,
        unsigned int f_nrOfColsA_ui32, double* f_matrixB_pf64,
        unsigned int f_nrOfRowsB_ui32, unsigned int f_nrOfColsB_ui32)
        {
    unsigned int l_rowCounter_ui32=0;
    unsigned int l_colCounter_ui32=0;

    if(f_nrOfColsA_ui32!=f_nrOfColsB_ui32 && f_nrOfRowsA_ui32!=f_nrOfRowsB_ui32)
    {return M_SIG_MATRIXLIB_FAILED_BL;}
    else
    {
        for(l_rowCounter_ui32=0;l_rowCounter_ui32<f_nrOfRowsA_ui32;l_rowCounter_ui32++)
        {
            for(l_colCounter_ui32=0;l_colCounter_ui32<f_nrOfColsA_ui32;l_colCounter_ui32++)
            {
                f_matrixResult_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_colCounter_ui32)]=
                        f_matrixA_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_colCounter_ui32)]+
                            f_matrixB_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_colCounter_ui32)];
            }
        }
        return M_SIG_MATRIXLIB_SUCCESS_BL;
    }
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/18
 *
 * \brief    Subtraction of two matrices
 * \details    Subtract two matrices and stores it in a resulting matrix
 *             f_matrixResult_pf64=f_matrixA_pf64-f_matrixB_pf64
 *
 *     \param[in]    1.Param: Result matrix with double values as Pointer
 *                 2.Param: Matrix A
 *                 3.Param: Number of rows of Matrix A
 *                 4.Param: Number of columns Matrix A
 *                 5.Param: Matrix B
 *                 6.Param: Number of rows of Matrix B
 *                 7.Param: Number of columns Matrix B
 *     \param[out] returns a boolean value, indicating the occurence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_sigMath_matrixSubtraktion_bool(double* f_matrixResult_pf64,
        double* f_matrixA_pf64, unsigned int f_nrOfRowsA_ui32,
        unsigned int f_nrOfColsA_ui32, double* f_matrixB_pf64,
        unsigned int f_nrOfRowsB_ui32, unsigned int f_nrOfColsB_ui32)
{
    unsigned int l_rowCounter_ui32=0;
    unsigned int l_colCounter_ui32=0;

    if(f_nrOfColsA_ui32!=f_nrOfColsB_ui32 && f_nrOfRowsA_ui32!=f_nrOfRowsB_ui32)
    {return M_SIG_MATRIXLIB_FAILED_BL;}
    else
    {
        for(l_rowCounter_ui32=0;l_rowCounter_ui32<f_nrOfRowsA_ui32;l_rowCounter_ui32++)
        {
            for(l_colCounter_ui32=0;l_colCounter_ui32<f_nrOfColsA_ui32;l_colCounter_ui32++)
            {
                f_matrixResult_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_colCounter_ui32)]=
                            f_matrixA_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_colCounter_ui32)]-
                            f_matrixB_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_colCounter_ui32)];
            }
        }
        return M_SIG_MATRIXLIB_SUCCESS_BL;
    }
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/18
 *
 * \brief    Transponate a matrix
 * \details    Transponate a matrix and store it in a resulting matrix
 *             f_matrixResult_pf64=f_matrixA_pf64^(T)
 *
 *     \param[in]    1.Param: Result matrix with double values as Pointer
 *                 2.Param: Matrix to transponate
 *                 3.Param: Number of rows of Matrix to transponate
 *                 4.Param: Number of columns Matrix to transponate
 *     \param[out] returns a boolean value, indicating the occurence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_sigMath_matrixTransponiert_bool(
        double* f_matrixResult_pf64, double* f_matrix_pf64,
        unsigned int f_nrOfRows_ui32, unsigned int f_nrOfCols_ui32)
{
    unsigned int l_rowCounter_ui32=0;
    unsigned int l_colCounter_ui32=0;

    for(l_rowCounter_ui32=0;l_rowCounter_ui32<f_nrOfRows_ui32;l_rowCounter_ui32++)
    {
        for(l_colCounter_ui32=0;l_colCounter_ui32<f_nrOfCols_ui32;l_colCounter_ui32++)
        {
            f_matrixResult_pf64[m_getIndex_i32(f_nrOfCols_ui32,l_colCounter_ui32,l_rowCounter_ui32)]=
                        f_matrix_pf64[m_getIndex_i32(f_nrOfCols_ui32,l_rowCounter_ui32,l_colCounter_ui32)];
        }
    }
    return M_SIG_MATRIXLIB_SUCCESS_BL;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/18
 *
 * \brief    Invert a matrix
 * \details    Invert a matrix and store it in a resulting matrix
 *             f_matrixResult_pf64=f_matrixA_pf64^(-1)
 *
 *     \param[in]    1.Param: Result matrix with double values as Pointer
 *                 2.Param: Matrix to invert
 *                 3.Param: Number of rows of Matrix to invert
 *                 4.Param: Number of columns Matrix to invert
 *     \param[out] returns a boolean value, indicating the occurence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_sigMath_matrixInverse_bool(double* f_matrixResult_pf64,
        double* f_matrixA_pf64, unsigned int f_nrOfRowsA_ui32,
        unsigned int f_nrOfColsA_ui32)
{
    int l_rowCounter_ui32=0;
    int l_rowCounterInnerLoop_ui32=0;
    int l_colCounter_ui32=0;
    double l_tempValue_f64=0;
    //double l_determinant_f64=0;
    //Matrix for building a lower triangular matrix
    double l_lowerTriangularMatrix_f64[f_nrOfRowsA_ui32][f_nrOfColsA_ui32];
    double* l_lowerTriangularMatrix_pf64=(double*)l_lowerTriangularMatrix_f64;
    //Matrix for solving a system
    double l_lowerInverseTriangularMatrix_f64[f_nrOfRowsA_ui32][f_nrOfColsA_ui32];
    double* l_lowerInverseTriangularMatrix_pf64=(double*)l_lowerInverseTriangularMatrix_f64;

    double l_eyeMatrix_f64[f_nrOfRowsA_ui32][f_nrOfColsA_ui32];
    double* l_eyeMatrix_pf64=(double*)l_eyeMatrix_f64;

    if(f_nrOfRowsA_ui32!=f_nrOfColsA_ui32)
    {return M_SIG_MATRIXLIB_FAILED_BL;}


    //Cholesky for building the lower triangular matrix
    for(l_colCounter_ui32=0;l_colCounter_ui32<f_nrOfColsA_ui32;l_colCounter_ui32++)
    {
        for(l_rowCounter_ui32=l_colCounter_ui32;l_rowCounter_ui32<f_nrOfRowsA_ui32;l_rowCounter_ui32++)
        {
            if(l_rowCounter_ui32==l_colCounter_ui32)
            {
                for(l_rowCounterInnerLoop_ui32=0;l_rowCounterInnerLoop_ui32<l_colCounter_ui32;l_rowCounterInnerLoop_ui32++)
                {
                    l_tempValue_f64+=pow(l_lowerTriangularMatrix_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_rowCounterInnerLoop_ui32)],2);
                }
                if(f_matrixA_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_colCounter_ui32,l_colCounter_ui32)]-l_tempValue_f64<0)
                {return M_SIG_MATRIXLIB_FAILED_BL;}

                l_lowerTriangularMatrix_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_colCounter_ui32)]=
                        sqrt(f_matrixA_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_colCounter_ui32,l_colCounter_ui32)]-l_tempValue_f64);

                l_tempValue_f64=0;
            }
            else
            {
                for(l_rowCounterInnerLoop_ui32=0;l_rowCounterInnerLoop_ui32<l_colCounter_ui32;l_rowCounterInnerLoop_ui32++)
                {
                    l_tempValue_f64+=l_lowerTriangularMatrix_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_rowCounterInnerLoop_ui32)]*
                            l_lowerTriangularMatrix_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_colCounter_ui32,l_rowCounterInnerLoop_ui32)];
                }
                l_lowerTriangularMatrix_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_colCounter_ui32)]=
                                        (f_matrixA_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_colCounter_ui32)]-l_tempValue_f64)/
                                        l_lowerTriangularMatrix_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_colCounter_ui32,l_colCounter_ui32)];
                l_tempValue_f64=0;
            }
        }
    }
//calculate the determinant of A --> not needed here
//    for(l_colCounter_ui32=0;l_colCounter_ui32<f_nrOfColsA_ui32;l_colCounter_ui32++)
//    {
//        l_determinant_f64=l_lowerTriangularMatrix_f64[m_getIndex_i32(f_nrOfRowsA_ui32,l_colCounter_ui32,l_colCounter_ui32)];
//    }
//    l_determinant_f64=pow(l_determinant_f64,2);

//solve linear system

    if(g_sigMath_matrixEye_bool(l_eyeMatrix_f64[0],f_nrOfRowsA_ui32,f_nrOfColsA_ui32)!=0)
    {return M_SIG_MATRIXLIB_FAILED_BL;}
    l_tempValue_f64=0;

    for(l_colCounter_ui32=0;l_colCounter_ui32<f_nrOfColsA_ui32;l_colCounter_ui32++)
    {
        for(l_rowCounter_ui32=0;l_rowCounter_ui32<f_nrOfRowsA_ui32;l_rowCounter_ui32++)
        {
            for(l_rowCounterInnerLoop_ui32=0;l_rowCounterInnerLoop_ui32<l_rowCounter_ui32;l_rowCounterInnerLoop_ui32++)
            {
                l_tempValue_f64-=l_lowerTriangularMatrix_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_rowCounterInnerLoop_ui32)]*
                        l_lowerInverseTriangularMatrix_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounterInnerLoop_ui32,l_colCounter_ui32)];
            }
            l_lowerInverseTriangularMatrix_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_colCounter_ui32)]=
                        (l_eyeMatrix_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_colCounter_ui32)]+l_tempValue_f64)/
                        l_lowerTriangularMatrix_pf64[m_getIndex_i32(f_nrOfColsA_ui32,l_rowCounter_ui32,l_rowCounter_ui32)];
            l_tempValue_f64=0;
        }
    }

    if(g_sigMath_matrixTransponiert_bool((double*)l_lowerTriangularMatrix_f64,(double*)l_lowerInverseTriangularMatrix_f64,
                f_nrOfRowsA_ui32,f_nrOfColsA_ui32)!=0)
    {return M_SIG_MATRIXLIB_FAILED_BL;}

    if(g_sigMath_matrixMultiplikation_bool((double*)f_matrixResult_pf64,(double*)l_lowerTriangularMatrix_f64 ,
            f_nrOfRowsA_ui32,f_nrOfColsA_ui32,(double*)l_lowerInverseTriangularMatrix_f64,f_nrOfRowsA_ui32,f_nrOfColsA_ui32)!=0)
    {return M_SIG_MATRIXLIB_FAILED_BL;}

    return M_SIG_MATRIXLIB_SUCCESS_BL;
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/18
 *
 * \brief    Assign the values of one matrix to another
 * \details    Assign stored values of one matrix to another matrix
 *
 *     \param[in]    1.Param: Result matrix with double values as Pointer
 *                 2.Param: Matrix with values to copy
 *                 3.Param: Number of rows of the result matrix
 *                 4.Param: Number of columns of the result matrix
 *     \param[out] returns a boolean value, indicating the occurence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_sigMath_matrixAssignment_bool(double* f_matrixResult_pf64,
        unsigned int f_nrOfRowsResult_ui32,unsigned int f_nrOfColsResult_ui32,
        double* f_matrix_pf64, unsigned int f_nrOfRows_ui32,
        unsigned int f_nrOfCols_ui32)
{
    unsigned int l_rowCounter_ui32=0;
    unsigned int l_colCounter_ui32=0;

    if(f_nrOfRows_ui32!=f_nrOfRowsResult_ui32 && f_nrOfCols_ui32!=f_nrOfColsResult_ui32)
    {
        return M_SIG_MATRIXLIB_FAILED_BL;
    }
    else
    {
        for(l_colCounter_ui32=0;l_colCounter_ui32<f_nrOfCols_ui32;l_colCounter_ui32++)
        {
            for(l_rowCounter_ui32=0;l_rowCounter_ui32<f_nrOfRows_ui32;l_rowCounter_ui32++)
            {
                f_matrixResult_pf64[m_getIndex_i32(f_nrOfCols_ui32,l_rowCounter_ui32,l_colCounter_ui32)]=
                        f_matrix_pf64[m_getIndex_i32(f_nrOfCols_ui32,l_rowCounter_ui32,l_colCounter_ui32)];
            }
        }
        return M_SIG_MATRIXLIB_SUCCESS_BL;
    }
}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/17
 *
 * \brief    Initialize Matrix
 * \details    This function initializes a given matrix with a a given value
 *
 *     \param[in]    1.Param: Result matrix with double values as Pointer
 *                 2.Param: Number of rows of the result matrix
 *                 3.Param: Number of columns of the result matrix
 *                 4.Param: Value used to initialize
 *     \param[out] returns a boolean value, indicating the occurence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_sigMath_matrixInitialize_bool(double* f_matrixResult_pf64,
        unsigned int f_nrOfRows_ui32, unsigned int f_nrOfCols_ui32,
        double f_setValue_f64)
{
    unsigned int l_rowCounter_ui32=0;
    unsigned int l_colCounter_ui32=0;

    for(l_colCounter_ui32=0;l_colCounter_ui32<f_nrOfCols_ui32;l_colCounter_ui32++)
    {
        for(l_rowCounter_ui32=0;l_rowCounter_ui32<f_nrOfRows_ui32;l_rowCounter_ui32++)
        {
            f_matrixResult_pf64[m_getIndex_i32(f_nrOfCols_ui32,l_rowCounter_ui32,l_colCounter_ui32)]=f_setValue_f64;
        }
    }
    return M_SIG_MATRIXLIB_SUCCESS_BL;

}

/*!**********************************************************************
 * \author     Oliver Breuning (olbrgs00)
 * \date     2015/05/17
 *
 * \brief    Build the Eye-Matrix
 * \details    This function builds the Eye matrix to a given matrix
 *
 *     \param[in]    1.Param: Result matrix with double values as Pointer
 *                 2.Param: Number of rows of the result matrix
 *                 3.Param: Number of columns of the result matrix
 *     \param[out] returns a boolean value, indicating the occurence of
 *                 failures\n
 *                 0 .... indicates success (no errors)\n
 *                 1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_sigMath_matrixEye_bool(double* f_matrixResult_pf64,
        unsigned int f_nrOfRows_ui32, unsigned int f_nrOfCols_ui32)
{
    unsigned int l_rowCounter_ui32=0;
    unsigned int l_colCounter_ui32=0;

    if(f_nrOfRows_ui32!=f_nrOfCols_ui32)
    {
        return M_SIG_MATRIXLIB_FAILED_BL;
    }
    else
    {
        for(l_colCounter_ui32=0;l_colCounter_ui32<f_nrOfCols_ui32;l_colCounter_ui32++)
        {
            for(l_rowCounter_ui32=0;l_rowCounter_ui32<f_nrOfRows_ui32;l_rowCounter_ui32++)
            {
                if(l_rowCounter_ui32==l_colCounter_ui32)
                {
                    f_matrixResult_pf64[m_getIndex_i32(f_nrOfCols_ui32,l_rowCounter_ui32,l_colCounter_ui32)]=1;
                }
                else
                {
                    f_matrixResult_pf64[m_getIndex_i32(f_nrOfCols_ui32,l_rowCounter_ui32,l_colCounter_ui32)]=0;
                }
            }
        }
        return M_SIG_MATRIXLIB_SUCCESS_BL;
    }
}


