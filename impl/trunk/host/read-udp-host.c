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

#include "../matlab/udpSigLib.h"

#define BINDADDRESS "0.0.0.0"
#define BINDPORT 5000
#define BUFLEN 200



int main()
{
	int socketreceive = 0;

	struct sockaddr_in clientaddress, remoteaddress;
	int recvlen = 0;
	socklen_t remoteaddrlen;
	char buffer[BUFLEN];
	char str[BUFLEN];

	halMatlab_rtSigAllStatePayload l_rtSigAllPayload_st;

	socketreceive = socket(PF_INET, SOCK_DGRAM, 0);
	clientaddress.sin_family = AF_INET;
	clientaddress.sin_port = htons(BINDPORT);
	/*  the inet_aton converts from dot notation to integer notation and then converts from host byte order to network byte order*/
	(void)inet_aton(BINDADDRESS, &clientaddress.sin_addr);

	remoteaddrlen = sizeof(remoteaddress);
	bind(socketreceive, (struct sockaddr *)&clientaddress, (socklen_t)sizeof(clientaddress));

	while(1)
	{

		printf("waiting for data\n");
		fflush(stdout);
		recvlen = recvfrom(socketreceive, buffer, BUFLEN, 0, (struct sockaddr *)&remoteaddress, &remoteaddrlen);
		if (recvlen == -1 )
		{
			perror("recvfrom()");
		}

		// nano second needs to be reduced to 8 bytes. with 64 bit platform it is eating the next 8 bytes as well hence the acceleration is eaten up.
		//  or one can also put a pad
		printf("data received from address and port %s:%d\n", inet_ntoa(remoteaddress.sin_addr), ntohs(remoteaddress.sin_port));
		printf("Received number of payload %d\n", recvlen);
		memcpy(&l_rtSigAllPayload_st, buffer, sizeof(l_rtSigAllPayload_st));
		//printf("%d and temperature %f", l_rtSigAllPayload_st.timestamp_st.tv_sec,  l_rtSigAllPayload_st.imuState_st.temperature_f64);
		sprintf(str, "sec = %d, nano = %lu\nacc = %f %f %f\nmag = %f %f %f\nyaw, pitch, roll = %f %f %f\ntemperature = %f\npressure = %f\n",
				l_rtSigAllPayload_st.timestamp_st.tv_sec,
				l_rtSigAllPayload_st.timestamp_st.tv_nsec,
				l_rtSigAllPayload_st.imuState_st.acc.x_f64, l_rtSigAllPayload_st.imuState_st.acc.y_f64, l_rtSigAllPayload_st.imuState_st.acc.z_f64,
				l_rtSigAllPayload_st.imuState_st.mag.x_f64, l_rtSigAllPayload_st.imuState_st.mag.y_f64, l_rtSigAllPayload_st.imuState_st.mag.z_f64,
				l_rtSigAllPayload_st.imuState_st.gyro.l_yaw_f64, l_rtSigAllPayload_st.imuState_st.gyro.l_pitch_f64, l_rtSigAllPayload_st.imuState_st.gyro.l_roll_f64,
				l_rtSigAllPayload_st.imuState_st.temperature_f64, l_rtSigAllPayload_st.imuState_st.pressure_f64);
		puts(str);
	}
	return 0;
}
