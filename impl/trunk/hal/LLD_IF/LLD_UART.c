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

//UART filepointer
static int l_filestream_i32 = -1;

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/20
 *
 * \brief Function opens a Hardware interface as Filepointer
 * \details Function opens a Hardware interface as Filepointer
 *
 * \param[ in ] no parameter
 * \param[ out ] 0 if Hardware interface can be opened;
 * -1 if Hardware interface can not be opened
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
int g_lldUart_uartOpen_i32(void)
{
	l_filestream_i32 = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (l_filestream_i32 == -1)
	{
		//Error UART can not be opened
		return(-1);
	}
	struct termios l_options_st;
	tcgetattr(l_filestream_i32, &l_options_st);
	l_options_st.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	l_options_st.c_iflag = IGNPAR;
	l_options_st.c_oflag = 0;
	l_options_st.c_lflag = 0;
	tcflush(l_filestream_i32, TCIFLUSH);
	tcsetattr(l_filestream_i32, TCSANOW, &l_options_st);
	sleep(3);
	return(0);
}

/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/20
 *
 * \brief Function reads one Byte from the Filepointer
 * \details Function reads one Byte from the Filepointer,
 * initializes if necessary the Filepointer
 *
 * \param[ in ] no parameter
 * \param[ out ] -1 if no read from filestream is possible
 * character from GPS if read is possible
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
char g_lldUart_readByte_ch(void)
{
	char l_recChar_ch='0';
	ssize_t l_nrReadBytes_ssize=0;

	if (l_filestream_i32 == -1)
	{
		g_lldUart_uartOpen_i32();
	}

	//read new values if l_filestream_i32 is opened
	if (l_filestream_i32 != -1)
	{
		while (l_nrReadBytes_ssize!=1)
		{ l_nrReadBytes_ssize=read(l_filestream_i32, &l_recChar_ch, 1);}
		return l_recChar_ch;
	}
	return(-1);
}


/*!**********************************************************************
 * \author Oliver Breuning ( olbrgs00 )
 * \date 2015/04/20
 *
 * \brief Function closes a Hardware interface
 * \details Function closes a Hardware interface
 *
 * \param[ in ] no parameter
 * \param[ out ] 0 if Function finishes
 *
 * \internal
 * CHANGELOG:
 *
 * \endinternal
 ********************************************************************** */
int g_lldUart_uartClose_i32(void)
{
	close(l_filestream_i32);
	return(0);
}

