/*!
 * \file ADCTest.c
 */
#include <stdio.h>
#include "../ADC/HAL_ADC.h"
#include <stdlib.h>


int main() {

  float erg=0;

  //erg = g_halADC_get_ui16(1);
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
