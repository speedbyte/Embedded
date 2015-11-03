/*!
 * \file main.c
 */
///*
// * main.cpp
// *
// *  Created on: 29.03.2015
// *      Author: user
// */
//
#include <stdio.h>
#include "GPS.h"

//using namespace std;

int main (void)
{
	int i=0;

	struct Position main_longitude;
	struct Position main_latitude;

	while(1)
	{
		g_halGps_getData_i32();
	}

	return 0;
}



