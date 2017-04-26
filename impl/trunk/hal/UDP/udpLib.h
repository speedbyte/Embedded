/*!
 * \file udpLib.h
 */
#ifndef HAL_MATLAB_UDPLIB_H
#define HAL_MATLAB_UDPLIB_H

// make library compatible for linux AND windows (since used with matlab)
#ifdef __linux__
	#include<arpa/inet.h>
#elif _WIN32
	#include<winsock2.h>
	#pragma comment(lib,"ws2_32.lib")
#endif

#define M_HAL_MATLAB_MAX_NUM_OF_SOCKETS_UI8		8
#define M_HAL_MATLAB_SEND_RECV_PORT_DIST_UI8	100
#define M_HAL_MATLAB_SEND_BUFFER_SIZE_UI16		512

#define M_HAL_MATLAB_SUCCESS_UI8				0
#define M_HAL_MATLAB_FAILED_UI8					1
#define M_HAL_MATLAB_ERROR_I8					-1

#ifdef _WIN32

/* dirty workaround - implement precise clock_gettime() for windows if 
 * sending packets from MATLAB (Windows) to Raspberry Pi is required!  
 */
#define CLOCK_REALTIME  0   

struct timespec
{
	long int tv_sec;		/* Seconds.  */
	long int tv_nsec;		/* Nanoseconds.  */
};

//defines for windows
typedef int clockid_t;
typedef unsigned short int	uint16_t;

int clock_gettime(clockid_t clk_id, struct timespec *res);
#endif

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/17
 *
 * \brief	Container for Udp-Socket data
 * \details	Since the Udp-Lib is considered to handle several opened
 * 			sockets at the same time, an encapsulation of all relevant
 * 			socket data in a custom struct type shall be performed.
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
typedef struct{
	struct sockaddr_in 	sockAddrListen_st;		//!<
	struct sockaddr_in 	sockAddrRemote_st;		//!<
	int 				socketHandler_i32;
} udp_socketData;

/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/05/16
 *
 * DESCRIPTION:
 * Interfaces to initialize a udp-connection
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
int 	g_udp_initSocket_i32(	unsigned short f_udpListenPort_ui16 );
int 	g_udp_initConnection_i32(const unsigned char* const f_destIpv4_rg4ui8, unsigned short f_udpConnectionPort_ui16 );

/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/05/16
 *
 * DESCRIPTION:
 * Interfaces to close an opened udp-socket
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
unsigned int g_udp_closeSocket_bool(int f_socketHandler_i32);

/* -----------------------------------------------------------------------
 * AUTHOR: Juergen Schmidt (juscgs00)
 * DATE OF CREATION: 2014/05/16
 *
 * DESCRIPTION:
 * Interfaces to access (send and receive) and configure an opened socket
 *
 * CHANGELOG:
 * none
 * -------------------------------------------------------------------- */
unsigned int g_udp_sendPacket_bool(	int f_socketHandler_i32,
										const unsigned char* const f_sendBuffer_pui8,
										unsigned int f_sendBufferSize_ui32
										);
unsigned int g_udp_sendRtDataPacket_bool(	int f_socketHandler_i32,
										const unsigned char* const f_sendBuffer_pui8,
										unsigned int f_sendBufferSize_ui32
										);
unsigned int g_udp_recvPacket_ui32(	int f_socketHandler_i32,
											unsigned char* const f_recvBuffer_pui8,
											unsigned int f_recvBufferSize_ui32
										);
unsigned int g_udp_configSocket_bool(	int f_socketHandler_i32,
											const unsigned char* const f_destIpv4_rg4ui8,
											unsigned short f_destPort_ui16
										);

#endif //HAL_MATLAB_UDPLIB_H
