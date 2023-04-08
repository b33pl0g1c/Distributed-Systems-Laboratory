#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){
	int len;
	int client_desc;
	struct sockaddr_in server_addr,client_addr;
	char buf[1024];
	//creating the socket.
	client_desc=socket(AF_INET,SOCK_DGRAM,0);
	if(client_desc<0){
		printf("Error in socket creation\n");
		exit(1);
	}

	//binding
	bzero(&server_addr,sizeof(server_addr));
	bzero(&client_addr,sizeof(client_addr));
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(8800);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	while(1){
		len=sizeof(server_addr);
		//send msg to server.		
		fgets(buf,sizeof(buf),stdin);
		sendto(client_desc,buf,1024,0,(struct sockaddr*)&server_addr,sizeof(server_addr));
		printf("Message sent to server\n");
		//receive from server.
		recvfrom(client_desc,buf,sizeof(buf),0,(struct sockaddr*)&server_addr,&len);
		printf("Message from server:%s\n",buf);
	
	}

	return 0;

}

