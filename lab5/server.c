#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){
	int len;
	int server_desc, client_desc;
	struct sockaddr_in server_addr,client_addr;
	char buf[1024];
	//creating the socket.
	server_desc=socket(AF_INET,SOCK_DGRAM,0);
	if(server_desc<0){
		printf("Error in socket creation\n");
		exit(1);
	}

	//binding
	bzero(&server_addr,sizeof(server_addr));
	bzero(&client_addr,sizeof(client_addr));
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(8800);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(bind(server_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		printf("Binding failed");
		exit(1);	
	}

	while(1){
		len=sizeof(client_addr);
		recvfrom(server_desc,buf,1024,0,(struct sockaddr*)&client_addr,&len);
		printf("message received from client: %s",buf);
		strcpy(buf,"hello from server");
		sendto(server_desc,buf,1024,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
	}

	return 0;

}
