/*
* RaspberryDemoUdpReceiveHost.cpp
*
*  Created on: Oct 23, 2015
*      Author: Chris Mönch
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include "../matlab/udpImuLib.h"

#define LOCAL_SERVER_PORT 5000


int main(int argc, char * argv[]) {
	printf("Starting read over UDP\n");
	unsigned char	l_remoteHostAddr_rg4ui8[4] 	= {192,168,22,160};
	unsigned short	l_remoteHostPort_ui16		= LOCAL_SERVER_PORT;
	int				l_udpSocket_i32;
	//unsigned int	l_sendState_bl;

	// open udp connection
	l_udpSocket_i32 = g_halMatlab_initConnection_i32( l_remoteHostAddr_rg4ui8, l_remoteHostPort_ui16 );

	printf ("%s: Wartet auf Daten am Port (UDP) %u\n",
	argv[0], LOCAL_SERVER_PORT);
	/* Serverschleife */
	while (1) {
		halImu_orientationValues 		l_recvImuState_st;
		l_recvImuState_st = g_halMatlab_recvImuState_bl(l_udpSocket_i32);

		/* Erhaltene Nachricht ausgeben */
		printf ("%f \n", l_recvImuState_st.temperature_f64);
		usleep(100000);
	}
return 0;
}

