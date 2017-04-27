/*!
 * \file HAL_ADC.c
 */
/*
    ADS1015_I2C.c
*/

#include <stdio.h>
#include "LLD_I2C.h"  // I2C Treiber
#include "HAL_ADC.h"

/*!**********************************************************************
 * \author         Martin Brodbeck (mabrgs00)
 * \date             2015/05/07
 *
 * \brief        Reads analog to digital converted values from ADS1015
 * \details    A detailed descripction about the function, here for creating
 *                     good foos and much more. Multiple lines of description is
 *                     possible. Doxygen will recognize the format automatically.
 *
 * \param[in]        l_input_ui8 is the input which selects input A0-3 to convert
 * \param[out]    converted voltage value, -1 when error on I2C Bus
 *
 * \internal
 * CHANGELOG:
 * 2015/05/08 mabrgs00:
 *  Error handling from I2C included
 *
 * \endinternal
 ***********************************************************************/
float g_halADC_get_ui16(unsigned char l_input_ui8){

  unsigned char l_address_ui8 = 0x49;        // Address of our device on the I2C bus
  unsigned char l_writeBuf_rg24[3];        // Buffer to store the 3 bytes that we write to the I2C device
  unsigned char l_readBuf_rg16[2];        // 2 byte buffer to store the data read from the I2C device
  unsigned char l_mux_ui8;            // Config value depening on input
  unsigned short l_val_ui16;            // (Converted) result of ADC
  unsigned char l_checkerror_bool;            // Variable to store return value

  // Setting Config according to select Input
  switch(l_input_ui8){                   // Standard: 1100 0011  (Bit 15-8) Input A0
    case 1: l_mux_ui8 = 0xC2; break;    // Input: A0
    case 2: l_mux_ui8 = 0xD2; break;
    case 3: l_mux_ui8 = 0xE2; break;
    case 4: l_mux_ui8 = 0xF2; break;    // Input: A3
    default: l_mux_ui8 = 0xC2;
  }
  // First Hex depends on Starting Conversion + the Input, which Pin to read A0-3
  // Second Value is PGA (001)=+-4,099V and continuous Mode (0)


  // These three bytes are written to the ADS1015 to set the config register and start the conversion
  l_writeBuf_rg24[0] = 1;        // This sets the pointer register to write two bytes to the config register
  l_writeBuf_rg24[1] = l_mux_ui8;       // This sets the 8 MSBs of the config register (bits 15-8) to 11000011
  l_writeBuf_rg24[2] = 0x23;          // This sets the 8 LSBs of the config register (bits  7-0) to 00100011

  // First Hex is sample Rate. (001) sets to 250SPS + Comp Mode (0)
  // Second Hex is Comp. config. (0011) disable the comparator


  // Initialize the buffer used to read data from the ADS1015 to 0
  l_readBuf_rg16[0]= 0;
  l_readBuf_rg16[1]= 0;

  // Write l_writeBuf_rg24 to the ADS1015, the 3 specifies the number of bytes we are writing,
  // this begins a continuous conversion
  l_checkerror_bool = g_lldI2c_Write_bool(l_address_ui8,l_writeBuf_rg24,3);
  if (l_checkerror_bool == 1)
    {
    return -1;
    }

  // Read the config register into readBuf
  l_checkerror_bool = g_lldI2c_Read_bool(l_address_ui8,l_readBuf_rg16,2);
  if (l_checkerror_bool == 1)
    {
    return -1;
    }

  // Set pointer register to 0 to read from the conversion register
  l_writeBuf_rg24[0] = 0;
  l_checkerror_bool = g_lldI2c_Write_bool(l_address_ui8, l_writeBuf_rg24,1);
  if (l_checkerror_bool == 1)
    {
    return -1;
    }

  // Read the contents of the conversion register into readBuf
  l_checkerror_bool = g_lldI2c_Read_bool(l_address_ui8,l_readBuf_rg16,2);
  if (l_checkerror_bool == 1)
    {
    return -1;
    }

  // Combine the two bytes of readBuf into a single 16 bit result
  l_val_ui16 = l_readBuf_rg16[0] << 8 | l_readBuf_rg16[1];
  l_val_ui16 = l_val_ui16 >> 4;

  return((float)l_val_ui16*4.096/2047.0);

}






