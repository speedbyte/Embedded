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

#define LOCAL_SERVER_PORT 9999
#define BUF 255

using namespace std;

int main(int argc, char * argv[]) {
int s, rc, n;
socklen_t len;
struct sockaddr_in cliAddr, servAddr;
char puffer[BUF];
const int y = 1;
s = socket (AF_INET, SOCK_DGRAM, 0);
if (s < 0) {
printf ("%s: Kann Socket nicht öffnen ...(%s)\n");
return 1;
}

/* Lokalen Server Port bind(en) */
servAddr.sin_family = AF_INET;
servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
servAddr.sin_port = htons (LOCAL_SERVER_PORT);
setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));
rc = bind ( s, (struct sockaddr *) &servAddr,
sizeof (servAddr));
if (rc < 0) {
printf ("%s: Kann Portnummern %d nicht binden (%s)\n");
return 1;
}
printf ("%s: Wartet auf Daten am Port (UDP) %u\n",
argv[0], LOCAL_SERVER_PORT);
/* Serverschleife */
while (1) {
/* Puffer initialisieren */
memset (puffer, 0, BUF);
/* Nachrichten empfangen */
len = sizeof (cliAddr);
n = recvfrom ( s, puffer, BUF, 0,(struct sockaddr *) &cliAddr, &len );
if (n < 0) {
printf ("%s: Kann keine Daten empfangen ...\n",
argv[0] );
continue;
}

/* Erhaltene Nachricht ausgeben */
printf ("%s \n", puffer);

}
return 0;

}
