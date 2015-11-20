#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

//Header File inclusion
//Variable declarations
int SerSock,CliSock;
struct sockaddr_in SerAddr;
struct sockaddr_in CliAddr;
struct hostent *he;
char host[100];
char str_port[10];
char SerRecvBuff[1024];
char SerSendBuff[1024];
int SerRecv,SerSend;
char fname[20];

int main(int argc, char *argv[])
{
	
	unsigned short port;
	FILE *fptr;
	int RecSize=sizeof(CliAddr);
	memset(&SerAddr,0,sizeof(SerAddr));
	memset(&CliAddr,0,sizeof(CliAddr));
	SerSock=socket(AF_INET, SOCK_DGRAM,0);
	gethostname(host,100);
	puts(host);
	he=gethostbyname(host);
	if(he==NULL)
	{
		herror("\nSomething wrong with gethostbyname");
		exit(1);
	}
	printf("\nHost name: %s",he->h_name);
	printf("\nIP Address: %s\n",inet_ntoa(*(struct in_addr*)he->h_addr));
	if(argc!=6)
	{
		puts("\nNumber of paramenters not sufficient (should be in the format ./filename -server -t <topologyfile> -i <routinginterval>)");
	}


	strcpy(fname,argv[3]);
	fptr=fopen(fname,"r");

	if(SerSock<0)
		{
			perror("\nSocket could not be  created");
		}
		SerAddr.sin_family=AF_INET;
		port=3430;
		SerAddr.sin_port=htons(port);
		SerAddr.sin_addr.s_addr=inet_addr(inet_ntoa(*(struct in_addr*)he->h_addr));
		
		//Binding Phase
		if(bind(SerSock,(struct sockaddr *) &SerAddr, sizeof(SerAddr))<0)
		{
			perror("\nBinding error");
			exit(1);
		}
		while(1)
		{
		//Receiving phase
			
			if(recvfrom(SerSock,SerRecvBuff,sizeof(SerRecvBuff),0, (struct sockaddr *) &CliAddr, &RecSize)<0)
			{
				perror("ReceiveFrom");
			}

			if(sendto(SerSock,SerSendBuff,sizeof(SerSendBuff),0, (struct sockaddr *) &CliAddr, sizeof(CliAddr))<0)
			{
				perror("SendTo");
			}
		}

	
	return 0;
}
