/*!
 * \file LLD_UART.h
 */
/*
 * UART.h
 *
 *  Created on: 11.04.2015
 *      Author: user
 */

#ifndef LLD_UART_H_
#define LLD_UART_H_

/* ---------------------------------------------
	AUTHOR: Oliver Breuning (olbrgs00)
DATE OF CREATION: 2014/04/20

INPUT PARAMS: none
OUTPUT: 0 if Hardware interface can be opened
		-1 if Hardware interface can not be opened

DESCRIPTION:
Function opens a Hardware interface as Filepointer

CHANGELOG:
none
--------------------------------------------- */
	int g_lldUart_uartOpen_i32(void);

	/* ---------------------------------------------
	AUTHOR: Oliver Breuning (olbrgs00)
	DATE OF CREATION: 2014/04/20

	INPUT PARAMS: none
	OUTPUT: -1 if no read from filestream is possible
			returns character from GPS if read is possible

	DESCRIPTION:
	Function reads one Byte from the Filepointer,
	initializes if necessary the Filepointer

	CHANGELOG:
	none
	--------------------------------------------- */
	char g_lldUart_readByte_ch(void);

	/* ---------------------------------------------
	AUTHOR: Oliver Breuning (olbrgs00)
	DATE OF CREATION: 2014/04/20

	INPUT PARAMS: none
	OUTPUT: 0 if Function finishes

	DESCRIPTION:
	Function closes a Hardware interface

	CHANGELOG:
	none
	--------------------------------------------- */
	int g_lldUart_uartClose_i32(void);

#endif /* LLD_UART_H_ */
