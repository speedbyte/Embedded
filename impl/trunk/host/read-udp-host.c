/*
* RaspberryDemoUdpReceiveHost.cpp
*
*  Created on: Oct 23, 2015
*      Author: Chris Mönch
*/
#ifdef __linux__

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


#elif _WIN32

/* timeserv.c */
/* A simple UDP server that sends the current date and time to the client */
/* Last modified: September 20, 2005 */
/* http://www.gomorgan89.com */
/* Link with library file wsock32.lib */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>
#pragma comment(lib,"ws2_32.lib")

#define BUFFER_SIZE 4096

void usage(void);


int main(int argc, char **argv)
{
	WSADATA w;							/* Used to open windows connection */
	unsigned short port_number;			/* Port number to use */
	int a1=0, a2=0, a3=0, a4=0;					/* Components of address in xxx.xxx.xxx.xxx form */
	int client_length;					/* Length of client struct */
	int bytes_received;					/* Bytes received from client */
	SOCKET sd;							/* Socket descriptor of server */
	struct sockaddr_in server;			/* Information about the server */
	struct sockaddr_in client;			/* Information about the client */
	char buffer[BUFFER_SIZE];			/* Where to store received data */
	struct hostent *hp;					/* Information about this computer */
	char host_name[256];				/* Name of the server */
	time_t current_time;				/* Current time */

	/* Interpret command line */
//	if (argc == 2)
//	{
//		/* Use local address */
//		if (sscanf(argv[1], "%u", &port_number) != 1)
//		{
//			usage();
//		}
//	}
//	else if (argc == 3)
//	{
//		/* Copy address */
//		if (sscanf(argv[1], "%d.%d.%d.%d", &a1, &a2, &a3, &a4) != 4)
//		{
//			usage();
//		}
//		if (sscanf(argv[2], "%u", &port_number) != 1)
//		{
//			usage();
//		}
//	}
//	else
//	{
//		usage();
//	}

	port_number = 5000;
	/* Open windows connection */
	if (WSAStartup(0x0101, &w) != 0)
	{
		fprintf(stderr, "Could not open Windows connection.\n");
		exit(0);
	}

	/* Open a datagram socket */
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == INVALID_SOCKET)
	{
		fprintf(stderr, "Could not create socket.\n");
		WSACleanup();
		exit(0);
	}

	/* Clear out server struct */
	memset((void *)&server, '\0', sizeof(struct sockaddr_in));

	/* Set family and port */
	server.sin_family = AF_INET;
	server.sin_port = htons(port_number);

	/* Set address automatically if desired */
	if (argc == 2)
	{
		/* Get host name of this computer */
		gethostname(host_name, sizeof(host_name));
		hp = gethostbyname(host_name);

		/* Check for NULL pointer */
		if (hp == NULL)
		{
			fprintf(stderr, "Could not get host name.\n");
			closesocket(sd);
			WSACleanup();
			exit(0);
		}

		/* Assign the address */
		server.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr_list[0][0];
		server.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr_list[0][1];
		server.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr_list[0][2];
		server.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr_list[0][3];
	}
	/* Otherwise assign it manually */
	else
	{
		server.sin_addr.S_un.S_un_b.s_b1 = (unsigned char)a1;
		server.sin_addr.S_un.S_un_b.s_b2 = (unsigned char)a2;
		server.sin_addr.S_un.S_un_b.s_b3 = (unsigned char)a3;
		server.sin_addr.S_un.S_un_b.s_b4 = (unsigned char)a4;
	}

	/* Bind address to socket */
	if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) == -1)
	{
		fprintf(stderr, "Could not bind name to socket.\n");
		closesocket(sd);
		WSACleanup();
		exit(0);
	}

	/* Print out server information */
	printf("Server running on %u.%u.%u.%u\n", (unsigned char)server.sin_addr.S_un.S_un_b.s_b1,
											  (unsigned char)server.sin_addr.S_un.S_un_b.s_b2,
											  (unsigned char)server.sin_addr.S_un.S_un_b.s_b3,
											  (unsigned char)server.sin_addr.S_un.S_un_b.s_b4);
	printf("Press CTRL + C to quit\n");

	/* Loop and get data from clients */
	while (1)
	{
		client_length = (int)sizeof(struct sockaddr_in);

		/* Receive bytes from client */
		bytes_received = recvfrom(sd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &client_length);
		printf("%d\n", bytes_received);
		printf("%s\n", buffer);
		if (bytes_received < 0)
		{
			fprintf(stderr, "Could not receive datagram.\n");
			closesocket(sd);
			WSACleanup();
			exit(0);
		}

		/* Check for time request */
// 		if (strcmp(buffer, "GET TIME\r\n") == 0)
// 		{
// 			/* Get current time */
// 			current_time = time(NULL);
//
// 			/* Send data back */
// 			if (sendto(sd, (char *)&current_time, (int)sizeof(current_time), 0, (struct sockaddr *)&client, client_length) != (int)sizeof(current_time))
// 			{
// 				fprintf(stderr, "Error sending datagram.\n");
// 				closesocket(sd);
// 				WSACleanup();
// 				exit(0);
// 			}
// 		}
	}
	closesocket(sd);
	WSACleanup();

	return 0;
}

void usage(void)
{
	fprintf(stderr, "timeserv [server_address] port\n");
	exit(0);
}

#endif
