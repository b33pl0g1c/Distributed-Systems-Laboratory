#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<time.h>
#define PORT 8998
#define MAXLINE 1024
int main()
{
	int sockfd;
	char buffer[MAXLINE];
	//creating the sockets.
	struct sockaddr_in servaddr, cliaddr;
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0){
	perror("Error in creating sockets. Exiting!!");
	exit(EXIT_FAILURE);
	}
	//defining values to the socket.
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	//binding the socket.
	if (bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr))< 0){
	perror("Error in binding socket.Exiting!!!");
	exit(EXIT_FAILURE);
	}
	int len;
	int n;
	len=sizeof(cliaddr);
	//Receiving request from client.
	n=recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);
	bzero(buffer, 256);
	time_t tick;
	tick = time(NULL);
	sleep(5);
	snprintf(buffer, sizeof(buffer), "%s", ctime(&tick));
	//sending the time via the buffer to client.
	sendto(sockfd, (char *)buffer, MAXLINE, MSG_CONFIRM, (const struct sockaddr *)&cliaddr,len);
	printf("\nCurrent time at server%s\n", buffer);
	return 0;
}
