/*!
 * \file LLD_UART.c
 */
/*
 * UART.c
 *
 *  Created on: 11.04.2015
 *      Author: user
 */

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "LLD_UART.h"
#include <stdio.h>

static FILE * fp=-1;

//opens the GPS_sample file
int LLD_UART_OPEN(void)
{
	fp = fopen ("GPS_sample.txt", "r");
	sleep(3);
	return(0);
}

//Dummy function
int LLD_UART_WRITE(unsigned char *sendBuffer,unsigned int nrToSend)
{
	//not used for test
}

//Dummy function
int LLD_UART_READ(unsigned int nrToRead)
{
	//not used for test
}

//Dummy function
unsigned char* LLD_GET_DATA(void)
{
	//not used for test
}

//Reads one byte from the Hardware interface
char LLD_UART_READBYTE(void)
{
	char rec_char='z';
	int c;

	if (fp == -1)
	{
		LLD_UART_OPEN();
	}

	//read new values if filestream is opened
	if (fp != -1)
	{
		c = fgetc(fp);
		rec_char = (char) c;
		return rec_char;
	}
	return(-1);
}

//closes the before opened file
int LLD_UART_CLOSE(void)
{
	fclose(fp);
	return(0);
}

