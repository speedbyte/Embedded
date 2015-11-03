/*!
 * \file main.c
 */
/* \date 27/10/2015
 * \author Vikas Agrawal
 * \brief This function is a test function to test if the GPS values can be acquired over UART and saved into a file
 * \details
 * \param[in]
 * \param[out]
 * \internal
 * \endinternal
 *
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



