// write a client TCP program that connects with the server program knowing the IP address and port number
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define MAX 50
#define INT_MAX 100001
int adjMat[MAX][MAX];

void initialize(int n)
{
    //initialize matrix with zero's
    memset(adjMat, 0, sizeof(adjMat));
}
int main()
{
   char *addr = "127.0.0.1"; 
   int server_sock , client_sock , len;
   int addr_size;
   struct sockaddr_in server , client;
   int buf[1024];
   memset(&client,'\0',sizeof(client));
   memset(&server,'\0',sizeof(server));
   client_sock= socket(AF_INET , SOCK_STREAM,0);
   if(client_sock < 0){
    printf("ERROR in socket creation\n");
    exit(1);
   }
   else{
   printf("Client socket Initialized!\n");
   }
   //defining the socket parameters.
   client.sin_family = AF_INET;
   client.sin_port = htons(8000);
   client.sin_addr.s_addr = inet_addr(addr);

   int connection = connect(client_sock , (struct sockaddr*) &client , sizeof(client));
   if(connection<0)
   {
    printf("ERROR\n");
    exit(2);
   }     
      bzero(buf, sizeof(buf));
      //take input for djikstra's algorithm.
      int n , m;
      int src , dest ;
      initialize(n);
      printf("Enter the number of vertices and edges: , \n");
      scanf("%d%d", &n,&m);
      printf("Enter the edges with their weights: \n");
      for(int i=0; i<m; i++)
      {
           int u , v , w;
           scanf("%d%d%d", &u, &v , &w);
           adjMat[u][v] = w;
           adjMat[v][u] = w;
      }
      buf[0] = n;
      buf[1] = m;
      printf("Client:Vertices:%d   Edges: %d\n" , buf[0], buf[1]);
      send(client_sock,buf, sizeof(buf) ,0);
      bzero(buf, sizeof(buf));
      send(client_sock ,adjMat , sizeof(adjMat) , 0);
      bzero(adjMat, sizeof(adjMat));
      bzero(buf, sizeof(buf));
      printf("Enter Source and Destination\n");
      scanf("%d" , &src);
      scanf("%d" , &dest);
      buf[0] = src;
      buf[1] = dest;
      send(client_sock, buf, sizeof(buf), 0);
      bzero(buf, sizeof(buf));
      recv(client_sock, buf, sizeof(buf), 0);
      printf("MInimum Cost to Destination:%d\n" , buf[0]);
      close(client_sock);
   return 0;
}