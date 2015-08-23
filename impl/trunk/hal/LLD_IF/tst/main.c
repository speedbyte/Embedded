/*!
 * \file main.c
 */
/*
 * main.cpp
 *
 *  Created on: 29.03.2015
 *      Author: user
 */

#include <stdio.h>
#include "GPS.h"

int main (void)
{
	char rec_char='z';
	char *ptr_rec_char=&rec_char;
	FILE * fp=-1;

	//open file to write received data from GPS
	fp = open ("GPS_logging.txt",100 | 01,400);
	sleep(1);

	while(1)
	{
		rec_char=g_lldUart_readByte_ch();
		//save read values if filestream is opened
		if (fp != -1)
		{
			write(fp,ptr_rec_char,1);
		}
	}

	fclose(fp);

	return 0;
}



