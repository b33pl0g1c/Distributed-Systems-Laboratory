#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include<arpa/inet.h>
int main(int argc,char* argv[]){
	int server_sock, client_sock, len;
	struct sockaddr_in server,client;
	char buff[1024];
	memset(&server,'\0',sizeof(server));
	memset(&client,'\0',sizeof(client));
    //Creating the socket
	server_sock=socket(AF_INET,SOCK_STREAM,0);
	printf("Server Socket Created\n");
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
    //Binding the socket.
	bind(server_sock,(struct sockaddr*)&server,sizeof(server));
	printf("Bind Successfully\n");
	//Listening for client.
    listen(server_sock,6);
	len=sizeof(client);
    //If received, accept the connection
	client_sock=accept(server_sock,(struct sockaddr*)&client,&len);
	while(1){
		
		// ssize_t send(int sockfd, const void *buf, size_t len, int flags);
		recv(client_sock,buff,1024,0);
		printf("%s\n",buff);
		send(client_sock,buff,1024,0);
	}
    //closing the socket after receiving the message.
	close(server_sock);
}
