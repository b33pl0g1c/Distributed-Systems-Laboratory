#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
int main(){
	int clientSocket;
	struct sockaddr_in clientAddr;
	char buf[1024];
    //Creating The socket
	clientSocket=socket(AF_INET,SOCK_STREAM,0);
	printf("Client Socket Created\n");
	memset(&clientAddr,'\0',sizeof(clientAddr));
	clientAddr.sin_family=AF_INET;
	clientAddr.sin_port=htons(8080);
    //The adjacent IP address was found to be 192.168.124.207.
	clientAddr.sin_addr.s_addr=inet_addr("192.168.124.207");
	//Connecting to the given server address.
    connect(clientSocket,(struct sockaddr*)&clientAddr,sizeof(clientAddr));
	printf("Connected to Server Successfully\n");
	while(1){
        //getting the user input to send as message.
		fgets(buf,1024,stdin);
		send(clientSocket,buf,1024,0);
		recv(clientSocket,buf,1024,0);
	}
    //closing th socket.
	close(clientSocket);
	return 0;
}
