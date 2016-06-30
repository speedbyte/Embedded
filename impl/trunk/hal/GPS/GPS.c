/*!
 * \file GPS.c
 */
/*
 * GPS.c
 *
 *  Created on: 12.04.2015
 *      Author: user
 */

#include "../LLD_IF/LLD_UART.h"
#include "GPS.h"

// Variables which can be read by get Functions
static struct strPosition l_gps_longitude_st;
static struct strPosition l_gps_latitude_st;
static unsigned int l_time_ui32;
static char l_fix_ch;
static double l_velocity_f64;
static double l_direction_f64;
static unsigned int l_date_ui32;
static double l_height_f64;
static double l_geoid_f64;

// Permanent Variables for the getData Function
static char l_rec_Data_ch='0';
static char l_header_position_ch=0;
static char l_message_ch=0;
static char l_data_position_ch=0;
static char l_message_position_ch=0;
static int l_fieldpointer_i32=0;
static int l_decimal_place_factor_i32=10;
static int l_succeded_i32;


/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/18
 *
 * \brief Get Time from GPS module
 * \details Interface of reading Time which is received by the GPS module.
 * This value is GMT.
 *
 * \param[ in ] no parameter
 * \param[ out ] Time of GPS receiver
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
unsigned int g_halGps_getTime_ui32(void)
{
    return l_time_ui32;
}


/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/18
 *
 * \brief Get Longitude from GPS module
 * \details Interface of reading struct Longitude which is received by the GPS module
 *
 * \param[ in ] no parameter
 * \param[ out ] Longitude of GPS receiver
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
struct strPosition g_halGps_getLongitude_st(void)
{
    return l_gps_longitude_st;
}


/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/18
 *
 * \brief Get Latitude from GPS module
 * \details Interface of reading struct Latitude which is received by the GPS module
 *
 * \param[ in ] no parameter
 * \param[ out ] Latitude of GPS receiver
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
struct strPosition g_halGps_getLatitude_st(void)
{
    return l_gps_latitude_st;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/18
 *
 * \brief Get Fix from GPS module
 * \details Interface of reading if the GPS module has a Fix.
 * This means it has good signal
 *
 * \param[ in ] no parameter
 * \param[ out ] Fix of GPS receiver
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
char g_halGps_getFix_ch(void)
{
    return l_fix_ch;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/18
 *
 * \brief Get Velocity from GPS module
 * \details Interface of reading the velocity which is calculated by the GPS module.
 * So the Receiver moves with a velocity which is accessible here in a certain direction.
 *
 * \param[ in ] no parameter
 * \param[ out ] Velocity of GPS receiver
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
double g_halGps_getVelocity_f64(void)
{
    return l_velocity_f64;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/18
 *
 * \brief Get Direction from GPS module
 * \details Interface of reading the direction of move which is calculated by the GPS module.
 * So the Receiver moves with a velocity in the direction which is accessible here.
 *
 * \param[ in ] no parameter
 * \param[ out ] Direction of GPS receiver
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
double g_halGps_getDirection_f64(void)
{
    return l_direction_f64;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/18
 *
 * \brief Get Date from GPS module
 * \details Interface of reading the Date which is received by the GPS module.
 * This value is based on GMT.
 *
 * \param[ in ] no parameter
 * \param[ out ] Date of GPS receiver
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
unsigned int g_halGps_getDate_ui32(void)
{
    return l_date_ui32;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/18
 *
 * \brief Get Height from GPS module
 * \details Interface of reading the Height which is calculated by the GPS module.
 *
 * \param[ in ] no parameter
 * \param[ out ] Height of GPS receiver
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
double g_halGps_getHeight_f64(void)
{
    return l_height_f64;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/18
 *
 * \brief Get Geoid from GPS module
 * \details Interface of reading the Geoid which is received by the GPS module.
 *
 * \param[ in ] no parameter
 * \param[ out ] Geoid of GPS receiver
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
double g_halGps_getGeoid_f64(void)
{
    return l_geoid_f64;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/21
 *
 * \brief Reset Values of Message 1
 * \details Resetting the values of Message 1 - $GPGGA .... when a new message arrives
 *
 * \param[ in ] no parameter
 * \param[ out ] no parameter
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
void l_resetMessage1Values_vd(void)
{
    l_time_ui32=0;
    l_gps_longitude_st.l_degree_ui32=0;
    l_gps_longitude_st.l_minutes_ui32=0;
    l_gps_longitude_st.l_seconds_f64=0;
    l_gps_longitude_st.l_cardinalDirection_ch=' ';
    l_gps_latitude_st.l_degree_ui32=0;
    l_gps_latitude_st.l_minutes_ui32=0;
    l_gps_latitude_st.l_seconds_f64=0;
    l_gps_latitude_st.l_cardinalDirection_ch=' ';
    l_height_f64=0;
    l_geoid_f64=0;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/21
 *
 * \brief Reset Values of Message 2
 * \details Resetting the values of Message 2 - $GPRMC .... when a new message arrives
 *
 * \param[ in ] no parameter
 * \param[ out ] no parameter
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
void l_resetMessage2Values_vd(void)
{
    l_time_ui32=0;
    l_fix_ch=' ';
    l_gps_longitude_st.l_degree_ui32=0;
    l_gps_longitude_st.l_minutes_ui32=0;
    l_gps_longitude_st.l_seconds_f64=0;
    l_gps_longitude_st.l_cardinalDirection_ch=' ';
    l_gps_latitude_st.l_degree_ui32=0;
    l_gps_latitude_st.l_minutes_ui32=0;
    l_gps_latitude_st.l_seconds_f64=0;
    l_gps_latitude_st.l_cardinalDirection_ch=' ';
    l_velocity_f64=0;
    l_direction_f64=0;
    l_date_ui32=0;
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/21
 *
 * \brief Parse Data from Uart into variables
 * \details Reads data from the Hardware Driver and parses it in the specific
 * important variables.
 * Checks just the GPGGA and GPRMC Messages which are received from the GPS module.
 * The return value gives back how many important Bytes are received.
 *
 * Description of counting successfully received values
 * total min: 35 max 38
 * $GPGGA ,205003.000 ,4841.9261 ,N ,00918.7276 ,E ,1 ,06 ,1.12 ,283.5 ,M ,48.0 ,M , ,*6D
 * ||||||  ||||||      |||| ||||  |  ||||| ||||  |               ||| |     || |
 *
 * total min: 44 max 47
 * $GPRMC ,205003.000 ,A ,4841.9261 ,N ,00918.7276 ,E ,0.33 ,184.26 ,100415 , , , A*63
 * ||||||  ||||||      |  |||| ||||  |  ||||| ||||  |  | ||  ||| ||  ||||||
 *
 *
 * Remark message can be shorter if for example value is less than 283.5, so e.g. 83.5
 *
 * \param[ in ] no parameter
 * \param[ out ] return of successfully important received characters
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
int g_halGps_getData_i32(void)
{

    l_rec_Data_ch=g_lldUart_readByte_ch();

    if(!l_message_position_ch)//check which message is received
    {
        if(l_rec_Data_ch=='$')
        {l_header_position_ch=1;l_succeded_i32=0;l_succeded_i32++;}
        else if (l_header_position_ch==1 && l_rec_Data_ch=='G')
        {l_header_position_ch=2;l_succeded_i32++;}
        else if (l_header_position_ch==2 && l_rec_Data_ch=='P')
        {l_header_position_ch=3;l_succeded_i32++;}
        else if (l_header_position_ch==3 && l_rec_Data_ch=='G')
        {l_header_position_ch=14;l_succeded_i32++;}
        else if (l_header_position_ch==3 && l_rec_Data_ch=='R')
        {l_header_position_ch=24;l_succeded_i32++;}
        else if (l_header_position_ch==14 && l_rec_Data_ch=='G')
        {l_header_position_ch=15;l_succeded_i32++;}
        else if (l_header_position_ch==24 && l_rec_Data_ch=='M')
        {l_header_position_ch=25;l_succeded_i32++;}
        else if (l_header_position_ch==15 && l_rec_Data_ch=='A')
        {    l_message_ch=1;l_resetMessage1Values_vd();l_data_position_ch=0;l_message_position_ch=1; l_succeded_i32++;}
        else if (l_header_position_ch==25 && l_rec_Data_ch=='C')
        {    l_message_ch=2;l_resetMessage2Values_vd();l_data_position_ch=0; l_message_position_ch=1; l_succeded_i32++;}
    }
    else
    {
        switch (l_message_ch)//check data within the two important messages
        {
        case 1://$GPGGA ,205003.000 ,4841.9261 ,N ,00918.7276 ,E ,1 ,06 ,1.12 ,283.5 ,M ,48.0 ,M , ,*6D        38
            switch (l_rec_Data_ch)
            {
            case ',':
                l_data_position_ch++;
                l_fieldpointer_i32=0;
                l_decimal_place_factor_i32=10;
                break;
            case 10://LF found
                l_succeded_i32=l_succeded_i32+100;    //short comment
                l_message_position_ch=0;
                l_header_position_ch=0;
                break;
            default:
                switch (l_data_position_ch)
                {
                case 1://Time
                    if(l_fieldpointer_i32<6)
                    {
                        l_time_ui32=l_time_ui32*10+(l_rec_Data_ch-48);
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 2://Latitude
                    if(l_fieldpointer_i32<2)
                    {
                        l_gps_latitude_st.l_degree_ui32=l_gps_latitude_st.l_degree_ui32*10+(l_rec_Data_ch-48);
                        l_succeded_i32++;
                    }
                    else if(l_fieldpointer_i32<4)
                    {
                        l_gps_latitude_st.l_minutes_ui32=l_gps_latitude_st.l_minutes_ui32*10+(l_rec_Data_ch-48);
                        l_succeded_i32++;
                    }
                    else if(l_fieldpointer_i32>=5 && l_fieldpointer_i32<9)
                    {
                        l_gps_latitude_st.l_seconds_f64=l_gps_latitude_st.l_seconds_f64*10+(l_rec_Data_ch-48)*0.006;
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 3://cardinal direction
                    if(l_fieldpointer_i32<1)
                    {
                        l_gps_latitude_st.l_cardinalDirection_ch=l_rec_Data_ch;
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 4://Longitude
                    if(l_fieldpointer_i32<3)
                    {
                        l_gps_longitude_st.l_degree_ui32=l_gps_longitude_st.l_degree_ui32*10+(l_rec_Data_ch-48);
                        l_succeded_i32++;
                    }
                    else if(l_fieldpointer_i32<5)
                    {
                        l_gps_longitude_st.l_minutes_ui32=l_gps_longitude_st.l_minutes_ui32*10+(l_rec_Data_ch-48);
                        l_succeded_i32++;
                    }
                    else if(l_fieldpointer_i32>=6 && l_fieldpointer_i32<10)
                    {
                        l_gps_longitude_st.l_seconds_f64=l_gps_longitude_st.l_seconds_f64*10+(l_rec_Data_ch-48)*0.006;
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 5://cardinal direction
                    if(l_fieldpointer_i32<1)
                    {
                        l_gps_longitude_st.l_cardinalDirection_ch=l_rec_Data_ch;
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 9://Height
                    if(l_rec_Data_ch!='.' && l_fieldpointer_i32==0)
                    {
                        l_height_f64=l_height_f64*10+(double)(l_rec_Data_ch-48);
                        l_succeded_i32++;

                    }
                    else if (l_rec_Data_ch=='.')
                    {
                        l_fieldpointer_i32++;
                    }
                    else
                    {
                        l_height_f64=l_height_f64+(double)(l_rec_Data_ch-48)/l_decimal_place_factor_i32;
                        l_decimal_place_factor_i32=l_decimal_place_factor_i32*10;
                        l_succeded_i32++;
                    }
                    break;
                case 11://Geoid
                    if(l_rec_Data_ch!='.' && l_fieldpointer_i32==0)
                    {
                        l_geoid_f64=l_geoid_f64*10+(double)(l_rec_Data_ch-48);
                        l_succeded_i32++;

                    }
                    else if (l_rec_Data_ch=='.')
                    {
                        l_fieldpointer_i32++;
                    }
                    else
                    {
                        l_geoid_f64=l_geoid_f64+(double)(l_rec_Data_ch-48)/l_decimal_place_factor_i32;
                        l_decimal_place_factor_i32=l_decimal_place_factor_i32*10;
                        l_succeded_i32++;
                    }
                    break;
                }
                break;
            }
            break;


        case 2://$GPRMC ,205003.000 ,A ,4841.9261 ,N ,00918.7276 ,E ,0.33 ,184.26 ,100415 , , , A*63      44- 46
            switch (l_rec_Data_ch)
            {
            case ',':
                l_data_position_ch++;
                l_fieldpointer_i32=0;
                l_decimal_place_factor_i32=10;
                break;
            case 10://LF found
                l_succeded_i32=l_succeded_i32+200;
                l_message_position_ch=0;
                l_header_position_ch=0;
                break;
            default:
                switch (l_data_position_ch)
                {
                case 1://Time
                    if(l_fieldpointer_i32<6)
                    {
                        l_time_ui32=l_time_ui32*10+(l_rec_Data_ch-48);
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 2://Fix
                    if(l_fieldpointer_i32<2)
                    {
                        l_fix_ch=l_rec_Data_ch;
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 3://Latitude
                    if(l_fieldpointer_i32<2)
                    {
                        l_gps_latitude_st.l_degree_ui32=l_gps_latitude_st.l_degree_ui32*10+(l_rec_Data_ch-48);
                        l_succeded_i32++;
                    }
                    else if(l_fieldpointer_i32<4)
                    {
                        l_gps_latitude_st.l_minutes_ui32=l_gps_latitude_st.l_minutes_ui32*10+(l_rec_Data_ch-48);
                        l_succeded_i32++;
                    }
                    else if(l_fieldpointer_i32>=5 && l_fieldpointer_i32<9)
                    {
                        l_gps_latitude_st.l_seconds_f64=l_gps_latitude_st.l_seconds_f64*10+(double)(l_rec_Data_ch-48)*0.006;
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 4://cardinal direction
                    if(l_fieldpointer_i32<1)
                    {
                        l_gps_latitude_st.l_cardinalDirection_ch=l_rec_Data_ch;
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 5://Longitude
                    if(l_fieldpointer_i32<3)
                    {
                        l_gps_longitude_st.l_degree_ui32=l_gps_longitude_st.l_degree_ui32*10+(l_rec_Data_ch-48);
                        l_succeded_i32++;
                    }
                    else if(l_fieldpointer_i32<5)
                    {
                        l_gps_longitude_st.l_minutes_ui32=l_gps_longitude_st.l_minutes_ui32*10+(l_rec_Data_ch-48);
                        l_succeded_i32++;
                    }
                    else if(l_fieldpointer_i32>=6 && l_fieldpointer_i32<10)
                    {
                        l_gps_longitude_st.l_seconds_f64=l_gps_longitude_st.l_seconds_f64*10+(double)(l_rec_Data_ch-48)*0.006;
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 6://cardinal direction
                    if(l_fieldpointer_i32<1)
                    {
                        l_gps_longitude_st.l_cardinalDirection_ch=l_rec_Data_ch;
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 7://Velocity
                    if(l_fieldpointer_i32<1)
                    {
                        l_velocity_f64=l_velocity_f64*10+(double)(l_rec_Data_ch-48)*0.01;
                        l_succeded_i32++;
                    }
                    else if(l_fieldpointer_i32>=2 && l_fieldpointer_i32<4)
                    {
                        l_velocity_f64=l_velocity_f64*10+(double)(l_rec_Data_ch-48)*0.01;
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                case 8://Direction
                    if(l_rec_Data_ch!='.' && l_fieldpointer_i32==0)
                    {
                        l_direction_f64=l_direction_f64*10+(double)(l_rec_Data_ch-48);
                        l_succeded_i32++;

                    }
                    else if (l_rec_Data_ch=='.')
                    {
                        l_fieldpointer_i32++;
                    }
                    else
                    {
                        l_direction_f64=l_direction_f64+(double)(l_rec_Data_ch-48)/l_decimal_place_factor_i32;
                        l_decimal_place_factor_i32=l_decimal_place_factor_i32*10;
                        l_succeded_i32++;
                    }
                    break;
                case 9://Date
                    if(l_fieldpointer_i32<6)
                    {
                        l_date_ui32=l_date_ui32*10+(l_rec_Data_ch-48);
                        l_succeded_i32++;
                    }
                    l_fieldpointer_i32++;
                    break;
                }
                break;
            }
            break;
        }
    }
    return(l_succeded_i32);
}
