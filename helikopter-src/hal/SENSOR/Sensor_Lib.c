/*!
 * \file Hal_Lib.c
 */
/*
 * Hal_Lib.c
 *
 *  Created on: 07.05.2015
 *      Author: user
 */

#include "Sensor_Lib.h"

int g_halLib_twoComplement2Int(unsigned char* f_buffer_ui8,unsigned int f_nrOfBytes_ui32)
{
    int l_countVariable_i32=0;
    int l_result_i32=0;
    unsigned char l_shift_ui8=0;
    unsigned int l_buffer_ui8[f_nrOfBytes_ui32];

    //copy Parameter buffer to local buffer
    for(l_countVariable_i32=0;l_countVariable_i32<=f_nrOfBytes_ui32-1;l_countVariable_i32++)
    {
        l_buffer_ui8[l_countVariable_i32]=*(f_buffer_ui8+l_countVariable_i32);
    }
//
    //if number is negative
    if ((l_buffer_ui8[0]& M_MASK_NEGATIVE_UI8)!=0)
    {
        for(l_countVariable_i32=0;l_countVariable_i32<=f_nrOfBytes_ui32-1;l_countVariable_i32++)
        {
            l_shift_ui8=f_nrOfBytes_ui32-1-l_countVariable_i32;
            l_result_i32=l_result_i32+(((l_buffer_ui8[l_countVariable_i32])^255)<<(l_shift_ui8*8));
        }
        l_result_i32=l_result_i32+1;
        l_result_i32=l_result_i32*-1;
    }
    else
    {
        for(l_countVariable_i32=0;l_countVariable_i32<=f_nrOfBytes_ui32-1;l_countVariable_i32++)
        {
            l_shift_ui8=f_nrOfBytes_ui32-1-l_countVariable_i32;
            l_result_i32=l_result_i32+(l_buffer_ui8[l_countVariable_i32]<<l_shift_ui8*8);
        }
    }
    return l_result_i32;
}


