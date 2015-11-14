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
int main(int argc, char *argv[])
{
	
	unsigned short port;
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
	printf("\nIP Address: %s",inet_ntoa(*(struct in_addr*)he->h_addr));

	if(SerSock<0)
	{
		perror("\nSocket could not be  created");
	}
	SerAddr.sin_family=AF_INET;
	port=atoi(argv[2]);
	SerAddr.sin_port=htons(port);

	SerAddr.sin_addr.s_addr=*he->h_addr;
	
	return 0;
}
