/*!
 * \file ADCTest.c
 */
#include <stdio.h>
#include "HAL_ADC.h"

extern float g_halADC_get_ui16(unsigned char );


int main() {
  
  float erg;
  	
  erg = g_halADC_get_ui16(1);
  if(erg<0)
	{
	printf("Fehler");
	return 1;
	}
  else
	{
  printf("Ergebniss: %f\n",erg);
  return 0;
	}
}
