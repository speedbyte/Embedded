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

	int LLD_UART_OPEN(void);
	int LLD_UART_WRITE(unsigned char *,unsigned int);
	int LLD_UART_READ(unsigned int);
	unsigned char* LLD_GET_DATA(void);
	char LLD_UART_READBYTE(void);
	int LLD_UART_CLOSE(void);

#endif /* LLD_UART_H_ */
