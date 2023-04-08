#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8998
#define MAXLINE 1024
int main(){
	int sockfd;
	char buffer[MAXLINE];
	//creating sockets.
	struct sockaddr_in servaddr;
	if((sockfd=socket(AF_INET,SOCK_DGRAM, 0))<0){
	perror("socket creation has failed");
	exit(EXIT_FAILURE);
	}
	//defining socket values.
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	int n;
	int len;
	bzero(buffer, 256);
	//sending value to the buffer.
	fgets(buffer, 255, stdin);
	sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
	printf("Message sent to server!\n");
	bzero(buffer, 256);
	//receiving from server.
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr,&len);
	buffer[n] = '\0';
	printf("Server : %s\n", buffer);
	
	//converting the received time into seconds.
	char timestr[9];
	memcpy(timestr,&buffer[11],8);
	timestr[8] = '\0';
	int req_time;
	char s1[10], s2[10], s3[10];
	sscanf(timestr,"%[^':']:%[^':']:%s", s1, s2, s3);
	req_time = 3600*atoi(s1) + 60*atoi(s2) +atoi(s3); // requested time
	char str[100];
	time_t tick;
	// for current time
	tick = time(NULL);
	snprintf(str, sizeof(str), "%s", ctime(&tick));
	printf("\nCurrent time at client side : %s\n", str);
	bzero(timestr, 9);
	memcpy(timestr,&str[11],8);
	timestr[8] = '\0';
	//for reply time.
	int reply_time;
	char s11[10], s12[10], s13[10];
	sscanf(timestr,"%[^':']:%[^':']:%s", s11, s12, s13);
	reply_time = 3600*atoi(s11) + 60*atoi(s12) +atoi(s13);
	//displaying the difference.
	int diff= reply_time - req_time;
	printf("\nTime difference between request and reply time is : %d sec.\n", diff);
	close(sockfd);
return 0;
}
