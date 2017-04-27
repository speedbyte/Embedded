/*!
 * \file GPS.h
 */
/*
 * GPS.h
 *
 *  Created on: 12.04.2015
 *      Author: user
 */

#ifndef GPS_H_
#define GPS_H_


/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/21
 *
 * \brief struct with Langitude or Latitude position
 * \details This struct stores either a Longitude or Latitude position. It stores
 * the degree, minute, second and the cardinal direction.
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
struct strPosition
{
	unsigned int l_degree_ui32;
	unsigned int l_minutes_ui32;
	double l_seconds_f64;
	char l_cardinalDirection_ch;
};

/* ---------------------------------------------
AUTHOR: Oliver Breuning (olbrgs00)
DATE OF CREATION: 2014/04/21

INPUT PARAMS: --
OUTPUT: --

DESCRIPTION:
Interfaces to get the GPS datas

CHANGELOG:
none
--------------------------------------------- */

unsigned int g_halGps_getTime_ui32(void);
struct strPosition g_halGps_getLongitude_st(void);
struct strPosition g_halGps_getLatitude_st(void);
char g_halGps_getFix_ch(void);
double g_halGps_getVelocity_f64(void);
double g_halGps_getDirection_f64(void);
unsigned int g_halGps_getDate_ui32(void);
double g_halGps_getHeight_f64(void);
double g_halGps_getGeoid_f64(void);

/* ---------------------------------------------
AUTHOR: Oliver Breuning (olbrgs00)
DATE OF CREATION: 2014/04/21

INPUT PARAMS: --
OUTPUT: --

DESCRIPTION:
Reset old messages if a new one arrives

CHANGELOG:
none
--------------------------------------------- */

void l_resetMessage1Values_vd(void);
void l_resetMessage2Values_vd(void);

/* ---------------------------------------------
AUTHOR: Oliver Breuning (olbrgs00)
DATE OF CREATION: 2014/04/21

INPUT PARAMS: --
OUTPUT: --

DESCRIPTION:
Read and parse new data from the Hardware interface
Byte by Byte

CHANGELOG:
none
--------------------------------------------- */

int g_halGps_getData_i32(void);

#endif /* GPS_H_ */
