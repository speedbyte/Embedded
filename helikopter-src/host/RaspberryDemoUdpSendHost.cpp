/*
* RaspberryDemoUdpSendHost.cpp
*
*  Created on: Oct 23, 2015
*      Author: Chris Mönch
*/

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int main(int argc, char * argv[]) {

cout << "Start\n";

int clientSocket, nBytesMessage, nBytesMessage2;
char message[12] = "Hello_World";
char message2[16] = "AnotherMessage";

nBytesMessage= sizeof(message)/ sizeof(message[0]);
nBytesMessage2 =sizeof(message2)/ sizeof(message2[0]);

struct sockaddr_in serverAddress;
socklen_t addressSize;

/*Create UDP socket*/
clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

/*Configure settings in address struct*/
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(9999);
serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);

/*Initialize size variable to be used later on*/
addressSize = sizeof(serverAddress);

printf("Start Sending Messages\n");

while(1){
sleep(1);
sendto(clientSocket,message,nBytesMessage,0,(struct sockaddr *)&serverAddress,addressSize);
sleep(1);
sendto(clientSocket,message2,nBytesMessage2,0,(struct sockaddr *)&serverAddress,addressSize);
printf("And send again....\n");
}

return 0;
}
