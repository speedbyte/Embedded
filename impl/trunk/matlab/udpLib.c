/*!
 * \file udpLib.c
 */
#ifdef __linux__
	#include<arpa/inet.h>
	#include<sys/socket.h>
#elif _WIN32
	#include<winsock2.h>
	#pragma comment(lib,"ws2_32.lib")
#endif

#include<string.h>
#include<stdlib.h>
#include<string.h>
#ifdef __linux__
    #include<unistd.h>
	#include<time.h>
#endif

#include "udpLib.h"

static halMatlab_socketData m_socketManagementBuffer_rg8st[M_HAL_MATLAB_MAX_NUM_OF_SOCKETS_UI8];

/*
 * -----------------------------------------------------------------------
 *  STATIC FUNCTIONS
 * -----------------------------------------------------------------------
 */

#ifdef _WIN32
// local redefinition for Windows-Systems
int clock_gettime(clockid_t clk_id, struct timespec *res)
{
	struct timespec l_timestampDummy_st;

	l_timestampDummy_st.tv_sec = 0;
	l_timestampDummy_st.tv_nsec = 0;

    *res = l_timestampDummy_st;
    
	return 0;
}
#endif

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/17
 *
 * \brief	Finds a free slot in the socket management buffer
 * \details	Since this module encapsulates the configuration data for each
 * 			initialized socket, a free slot number (=internal index number
 * 			of the management buffer) can be required, in order to create
 * 			a new socket. This function helps to find a free slot in the
 * 			socket management buffer.
 *
 * 	\param[out] returns a free internal slot number of the socket
 * 				management buffer. If all slots are filled,	the value -1
 * 				will be returned
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
static signed short l_findFreeSocketSlot_i16(void)
{
	signed short l_socketIndex_i16 = 0;

	// find empty slot in socket library
	while( 		(m_socketManagementBuffer_rg8st[l_socketIndex_i16].socketHandler_i32 > 0)
			&& 	(l_socketIndex_i16 < M_HAL_MATLAB_MAX_NUM_OF_SOCKETS_UI8) )
	{
		l_socketIndex_i16++;
	}

	// if all slots are occupied, do not open a new one
	if (l_socketIndex_i16 >= M_HAL_MATLAB_MAX_NUM_OF_SOCKETS_UI8)
	{
		return M_HAL_MATLAB_ERROR_I8;
	}

	return l_socketIndex_i16;
}

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/17
 *
 * \brief	Finds the slot number of a given socket handler
 * \details	Since this module encapsulates the configuration data for each
 * 			initialized socket, the slot number (=internal index number of
 * 			the management buffer) is required. This function performs a
 * 			lookup are returns the corresponding slot number.
 *
 * 	\param[in]	f_socketHandler_i32 specifies the socket handler number
 * 				that shall be found
 * 	\param[out] returns the the internal slot number of the socket
 * 				management buffer. If requested socket is not present,
 * 				the value -1 will be returned
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
static signed short l_findSocket_i16(signed int f_socketHandler_i32)
{
	signed short l_socketIndex_i16 = 0;

	if (f_socketHandler_i32 <= 0 )
	{
		return M_HAL_MATLAB_ERROR_I8;
	}

	// find socket handler
	for( l_socketIndex_i16=0; l_socketIndex_i16 < M_HAL_MATLAB_MAX_NUM_OF_SOCKETS_UI8; l_socketIndex_i16++ )
	{
		if ( m_socketManagementBuffer_rg8st[l_socketIndex_i16].socketHandler_i32 == f_socketHandler_i32 )
		{
			break;
		}
	}

	// if all slots are occupied, do not open a new one
	if (l_socketIndex_i16 >= M_HAL_MATLAB_MAX_NUM_OF_SOCKETS_UI8)
	{
		return M_HAL_MATLAB_ERROR_I8;
	}

	return l_socketIndex_i16;
}

/*
 * -----------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
 * -----------------------------------------------------------------------
 */

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/17
 *
 * \brief	Create and init an UDP-Socket for given incoming port
 * \details	This function creates a UDP-Socket with a given incoming port.
 *
 * 	\param[in]	f_udpListenPort_ui16 specifies the port number of the UDP
 * 				socket to listen to
 * 	\param[out] returns the requested socket handler number. -1 if no
 * 				socket slot is free (max number of sockets opened)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
int g_halMatlab_initSocket_i32(	unsigned short f_udpListenPort_ui16 )
{
	signed short 			l_socketSlotCtr_i16 = 0;
	halMatlab_socketData* 	l_freeSocketSlot_pst;
#ifdef _WIN32
    WSADATA wsa;
#endif
    
	if ( (l_socketSlotCtr_i16 = l_findFreeSocketSlot_i16()) < 0)
	{
		return M_HAL_MATLAB_ERROR_I8;
	}


	l_freeSocketSlot_pst = &m_socketManagementBuffer_rg8st[l_socketSlotCtr_i16];

	//windows specific startup requirements
#ifdef _WIN32
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		return M_HAL_MATLAB_ERROR_I8;
	}
#endif
	// open socket
	if ( (l_freeSocketSlot_pst->socketHandler_i32 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1 )
	{
		l_freeSocketSlot_pst->socketHandler_i32 = 0;
		return M_HAL_MATLAB_ERROR_I8;
	}

	// bind ip
	// -->zero out the structure
	memset(	(char*)&(l_freeSocketSlot_pst->sockAddrListen_st), 0, sizeof(l_freeSocketSlot_pst->sockAddrListen_st) );

	l_freeSocketSlot_pst->sockAddrListen_st.sin_family 		= AF_INET;
	l_freeSocketSlot_pst->sockAddrListen_st.sin_port 		= htons((uint16_t)f_udpListenPort_ui16);
	l_freeSocketSlot_pst->sockAddrListen_st.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind socket to port
	if( bind(	l_freeSocketSlot_pst->socketHandler_i32 ,
				(struct sockaddr*)&(l_freeSocketSlot_pst->sockAddrListen_st),
				sizeof(l_freeSocketSlot_pst->sockAddrListen_st)
				)
		== -1 )
	{
		l_freeSocketSlot_pst->socketHandler_i32 = 0;
		return M_HAL_MATLAB_ERROR_I8;
	}

	return l_freeSocketSlot_pst->socketHandler_i32;
}

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/19
 *
 * \brief	Creates, inits and configures an UDP-Socket for a symmetric
 * 			connection setup
 * \details	This function creates a UDP-Socket with for a given remote
 * 			machine (destination ip) and a given standard listen port
 * 			(given port is supposed to be used as listen port on both
 * 			machines: this machine and remote machine!)\n
 * 			\verbatim
 *          Example:
 *          ----------------------+ <Remote machine<  +-----------------------
 *                                | <sends to 5000 <  |
 *              Listen-Port: 5000 o<---<----<----<----o Outgoing port: 23413
 *                                |                   |
 *           Outgoing-Port: 23413 o---->---->---->--->o Listen-Port: 5000
 *                                |  >Local machine>  |
 *          ----------------------+  >sends to 5000>  +-----------------------
 *              Local machine                               Remote machine
 *          \endverbatim
 *
 *  \param[in]	f_destIpv4_rg4ui8 specifies the IPv4 number of the remote
 *  			machine
 * 	\param[in]	f_udpListenPort_ui16 specifies the port number of the UDP
 * 				connection that is used to listen for incoming messages
 * 				and as destination port for the remote machine
 * 	\param[out] returns the requested socket handler number. -1 if no
 * 				socket slot is free (max number of sockets opened)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
int 	g_halMatlab_initConnection_i32(const unsigned char* const f_destIpv4_rg4ui8, unsigned short f_udpConnectionPort_ui16 )
{
	int	l_socketHandler_i32;

	// create socket
	if ( ( l_socketHandler_i32 = g_halMatlab_initSocket_i32(f_udpConnectionPort_ui16) ) <= 0 )
	{
		// error occurred
		return M_HAL_MATLAB_ERROR_I8;
	}

	/*
	 * configure socket for a symmetric connection
	 * -> listen-port = send-port for both sides
	 *
	 *  Example:
	 *  ----------------------+ <Remote machine<  +-----------------------
	 *                        | <sends to 5000 <  |
	 *      Listen-Port: 5000 o<---<----<----<----o Outgoing port: 23413
	 *                        |                   |
	 *   Outgoing-Port: 23413 o---->---->---->--->o Listen-Port: 5000
	 *                        |  >Local machine>  |
	 *  ----------------------+  >sends to 5000>  +-----------------------
	 *     Local machine                               Remote machine
	 *
	 */
	if ( g_halMatlab_configSocket_bl(l_socketHandler_i32, f_destIpv4_rg4ui8, f_udpConnectionPort_ui16) != M_HAL_MATLAB_SUCCESS_UI8 )
	{
		// error occurred
		return M_HAL_MATLAB_ERROR_I8;
	}

	return l_socketHandler_i32;
}

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/17
 *
 * \brief	Closes the given socket and cleans up
 * \details	This function closes a given UDP-Socket properly and does
 * 			cleanup, if necessary.
 *
 * 	\param[in]	f_socketHandler_i32 specifies socket handler number to be
 * 				closed
 * 	\param[out] returns a boolean value, indicating the occurrence of
 * 				failures\n
 * 				0 .... indicates success (no errors)\n
 * 				1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halMatlab_closeSocket_bl(int f_socketHandler_i32)
{
	signed short l_socketSlotNumber_i16 = 0;

	// get slot number of requested socket handler
	if ( ( l_socketSlotNumber_i16 = l_findSocket_i16(f_socketHandler_i32) ) < 0 )
	{
		return M_HAL_MATLAB_FAILED_UI8;
	}

#ifdef __linux__
	/* close socket */
	close( m_socketManagementBuffer_rg8st[l_socketSlotNumber_i16].socketHandler_i32 );
#elif _WIN32
    closesocket(m_socketManagementBuffer_rg8st[l_socketSlotNumber_i16].socketHandler_i32);
    WSACleanup();
#endif
	/* free slot */
	m_socketManagementBuffer_rg8st[l_socketSlotNumber_i16].socketHandler_i32 = 0;

	return M_HAL_MATLAB_SUCCESS_UI8;
}

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/17
 *
 * \brief	Sends a packet of data via a given UDP-Socket
 * \details	This function sends a data packet via a given UDP-Socket. The
 * 			payload is the given send buffer.
 *
 * 	\param[in]	f_socketHandler_i32 specifies socket handler number used
 * 				for the data transmission
 * 	\param[in]	f_sendBuffer_pui8 is a pointer to the sending buffer
 * 				containing the relevant payload data
 * 	\param[in]	f_sendBufferSize_ui32 specifies the number of payload
 * 				bytes in the sending buffer
 * 	\param[out] returns a boolean value, indicating the occurrence of
 * 				failures\n
 * 				0 .... indicates success (no errors)\n
 * 				1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halMatlab_sendPacket_bl(	int f_socketHandler_i32,
										const unsigned char* const f_sendBuffer_pui8,
										unsigned int f_sendBufferSize_ui32
										)
{
	int						l_sendSuccess_i32		= -1;
	signed short 			l_socketSlotNumber_i16 	= 0;
	halMatlab_socketData* 	l_socketConfig_pst		= 0;
	unsigned int			l_socketStructSize_ui32	= 0;

	// get slot number of requested socket handler
	if ( ( l_socketSlotNumber_i16 = l_findSocket_i16(f_socketHandler_i32) ) < 0 )
	{
		return M_HAL_MATLAB_FAILED_UI8;
	}

	// get a pointer to the specific socket config data (for code-readability)
	l_socketConfig_pst = &(m_socketManagementBuffer_rg8st[l_socketSlotNumber_i16]);

	// send telegram
	l_socketStructSize_ui32 = sizeof(l_socketConfig_pst->sockAddrRemote_st);
	l_sendSuccess_i32 = sendto(	f_socketHandler_i32,
								f_sendBuffer_pui8,
								f_sendBufferSize_ui32,
								0 ,
								(struct sockaddr *)&l_socketConfig_pst->sockAddrRemote_st,
								l_socketStructSize_ui32 );

	if ( l_sendSuccess_i32 == M_HAL_MATLAB_ERROR_I8 )
	{
		return M_HAL_MATLAB_FAILED_UI8;
	}else{
		return M_HAL_MATLAB_SUCCESS_UI8;
	}
}

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/17
 *
 * \brief	Sends a packet of data with timestamp via a given UDP-Socket
 * \details	This function sends a data packet via a given UDP-Socket. The
 * 			current timestamp is added to the payload to get some sort of
 * 			realtime behavior.\n
 * 			Remark: This function is intended to be use in combination
 * 			        with an corresponding MATLAB Simulink Block for a
 * 			        soft realtime data transmission (time-stamped data).
 *
 * 	\param[in]	f_socketHandler_i32 specifies socket handler number used
 * 				for the data transmission
 * 	\param[in]	f_sendBuffer_pui8 is a pointer to the sending buffer
 * 				containing the relevant payload data
 * 	\param[in]	f_sendBufferSize_ui32 specifies the number of payload
 * 				bytes in the sending buffer
 * 	\param[out] returns a boolean value, indicating the occurrence of
 * 				failures\n
 * 				0 .... indicates success (no errors)\n
 * 				1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halMatlab_sendRtDataPacket_bl(	int f_socketHandler_i32,
												const unsigned char* const f_sendBuffer_pui8,
												unsigned int f_sendBufferSize_ui32)
{
	struct timespec			l_timestamp_st;
	unsigned char			l_sendBuffer_rgXi8[M_HAL_MATLAB_SEND_BUFFER_SIZE_UI16];
	unsigned int			l_sizePayload_ui32		= 0;

	/*
	 * first of all: get an accurate timestamp for this data telegram
	 * Hint: ensure that 'librt' is also linked in the project!
	 *       Eclipse: Goto Project->Properties.
	 *                Select C/C++-Build->Settings
	 *                Select tab view 'Tool Settings'.
	 *                Select 'Cross G++ Linker'->Libraries
	 *                and add the entry 'rt' to 'Libraries (-l)'
	 *
	 *       GCC on the commandline: simply add '-lrt' to your gcc options
	 */
	if ( clock_gettime(CLOCK_REALTIME, &l_timestamp_st) != M_HAL_MATLAB_SUCCESS_UI8)
	{
		return M_HAL_MATLAB_FAILED_UI8;
	}

	// add timestamp to payload data
	memcpy(	l_sendBuffer_rgXi8,
			&l_timestamp_st,
			sizeof(l_timestamp_st) );
	memcpy(	(l_sendBuffer_rgXi8+sizeof(l_timestamp_st)),
			f_sendBuffer_pui8,
			f_sendBufferSize_ui32 );

	// adjust size of telegram's payload (due to added timestamp)
	l_sizePayload_ui32 = f_sendBufferSize_ui32 + sizeof(l_timestamp_st);

	return g_halMatlab_sendPacket_bl(f_socketHandler_i32, l_sendBuffer_rgXi8, l_sizePayload_ui32);
}

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/17
 *
 * \brief	Reads a packet of data via a given UDP-Socket
 * \details	This function reads a data packet via a given UDP-Socket.
 *
 * 	\param[in]	f_socketHandler_i32 specifies socket handler number used
 * 				for the data transmission
 * 	\param[in]	f_sendBuffer_pui8 is a pointer to the receiving buffer
 * 	\param[in]	f_sendBufferSize_ui32 size (in bytes) of the receiving
 * 				buffer
 *  \param[in]	f_blocking_bl defines the blocking behavior of the
 *  			UDP packet reading.\n
 *  			== 0 ... function blocks until packet received (default)
 *  			!= 0 ... function is non-blocking
 * 	\param[out] returns the number of payload bytes written to the
 * 				receiving buffer. returns -1 in case of an error.
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halMatlab_recvPacket_ui32( int f_socketHandler_i32,
		unsigned char* const f_recvBuffer_pui8,
		unsigned int f_recvBufferSize_ui32)
{
	signed short 			l_socketSlotNumber_i16 	= 0;
	halMatlab_socketData* 	l_socketConfig_pst		= 0;
	int						l_recvFromFlag_i32		= 0;	// blocking behavior (standard)
	unsigned int			l_socketStructSize_ui32	= 0;

	// get slot number of requested socket handler
	if ( ( l_socketSlotNumber_i16 = l_findSocket_i16(f_socketHandler_i32) ) < 0 )
	{
		return M_HAL_MATLAB_FAILED_UI8;
	}

	// get a pointer to the specific socket config data (for code-readability)
	l_socketConfig_pst = &(m_socketManagementBuffer_rg8st[l_socketSlotNumber_i16]);

//	// define blocking behavior of receive-function
//	if ( f_blocking_bl != 0 )
//	{
//		// non-blocking behavior
//		l_recvFromFlag_i32 = MSG_DONTWAIT;
//	}else{
//		// blocking behavior (standard)
//		l_recvFromFlag_i32 = 0;
//	}

	// recv telegram (blocking!)
	l_socketStructSize_ui32 = sizeof(l_socketConfig_pst->sockAddrRemote_st);
	return recvfrom(	f_socketHandler_i32,
						f_recvBuffer_pui8,
						f_recvBufferSize_ui32,
						l_recvFromFlag_i32,
						(struct sockaddr *)&l_socketConfig_pst->sockAddrRemote_st,
						&l_socketStructSize_ui32);
}

/*!**********************************************************************
 * \author 	Juergen Schmidt (juscgs00)
 * \date 	2014/05/17
 *
 * \brief	Configures a given UDP-Socket to communicate with a specific
 * 			remote host
 * \details	This function sets the properties and binding of the given
 * 			socket such that a proper communication with the destination
 * 			address and destination port can be established.
 *
 * 	\param[in]	f_socketHandler_i32 specifies socket handler number used
 * 				for the data transmission
 * 	\param[in]	f_destIpv4_rg4ui8 is a preallocated array of 4 bytes,
 * 				each byte is one quadlet of a IPv4 address
 * 	\param[in]	f_destPort_ui16 determines the port number of the remote
 * 				host that shall be used for the data transmission
 * 	\param[out] returns a boolean value, indicating the occurrence of
 * 				failures\n
 * 				0 .... indicates success (no errors)\n
 * 				1 .... indicates failed (some errors)
 *
 * \internal
 * CHANGELOG:
 * none
 * \endinternal
 ***********************************************************************/
unsigned int g_halMatlab_configSocket_bl(	int f_socketHandler_i32,
		const unsigned char* const f_destIpv4_rg4ui8,
		unsigned short f_destPort_ui16)
{
	signed short 			l_socketSlotNumber_i16 	= 0;
	halMatlab_socketData* 	l_socketConfig_pst		= 0;
	unsigned int			l_ipv4Addr_ui32			= 0;

	// get slot number of requested socket handler
	if ( ( l_socketSlotNumber_i16 = l_findSocket_i16(f_socketHandler_i32) ) < 0 )
	{
		return M_HAL_MATLAB_FAILED_UI8;
	}

	// get a pointer to the specific socket config data (for code-readability)
	l_socketConfig_pst = &(m_socketManagementBuffer_rg8st[l_socketSlotNumber_i16]);

	// set values in l_socketConfig_pst->sockAddrRemote_st
	memset((char*) &l_socketConfig_pst->sockAddrRemote_st, 0, sizeof(l_socketConfig_pst->sockAddrRemote_st));
	l_socketConfig_pst->sockAddrRemote_st.sin_family = AF_INET;
	l_socketConfig_pst->sockAddrRemote_st.sin_port = htons(f_destPort_ui16);

	// assemble 4 bytes of IPv4 address into one 32bit value
	l_ipv4Addr_ui32 = 		( f_destIpv4_rg4ui8[0] << 24 )
						+ 	( f_destIpv4_rg4ui8[1] << 16 )
						+ 	( f_destIpv4_rg4ui8[2] << 8 )
						+ 	( f_destIpv4_rg4ui8[3] );

	l_socketConfig_pst->sockAddrRemote_st.sin_addr.s_addr = htonl( l_ipv4Addr_ui32 );

	return M_HAL_MATLAB_SUCCESS_UI8;
}
