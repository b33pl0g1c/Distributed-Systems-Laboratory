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
int dist[MAX]; // The output array. 
void initialize(int n)
{
    //initialize matrix
    memset(adjMat, 0, sizeof(adjMat));
}

//finds the minimum distance.
int minDistance(int map[] , int n)
{
	// Initialize min value
	int min = 100001 , min_index;
	for (int v = 0; v < n; v++){
		if (map[v] == 0 && dist[v] <= min){
			min = dist[v], min_index = v;
		}
	}
	return min_index;
}
//print the constructed distance array
void printSolution(int dist[] , int n)
{
	printf("Vertex \t\t Distance from Source\n");
	for (int i = 0; i < n; i++)
		printf("%d \t\t %d\n", i, dist[i]);
}
//implementation of the djikstra's algorithm.
void dijkstra(int adjMat[MAX][MAX], int src, int n)
{	
	int map[n]; 
	// Initialize all distances as INFINITE/MAX VAL and map[] as false/unvisited for all nodes.
	for (int i = 0; i < n; i++){
		dist[i] = 100001, map[i] = 0;
	}
	// Distance of source vertex from itself is always 0
	dist[src] = 0;
	// Find shortest path for all vertices
	for (int count = 0; count < n - 1; count++) 
    {
		// Pick the minimum distance vertex from the set of
		// vertices not yet processed. u is always equal to
		// src in the first iteration.
		int u = minDistance(map , n);
		// Mark the picked vertex as processed
		map[u] = 1;
		// Update dist value of the adjacent vertices of the
		// picked vertex
		for (int v = 0; v < n; v++)

			if (!map[v] && adjMat[u][v]
				&& dist[u] != 100001
				&& dist[u] + adjMat[u][v] < dist[v])
				dist[v] = dist[u] + adjMat[u][v];
	}
	// print the constructed distance array
	printSolution(dist,n);
}
int main()
{
   int n;
   char *addr = "127.0.0.1";
   int server_sock , client_sock , len;
   int addr_size;
   struct sockaddr_in server , client;
   int buf[1024];
   memset(&client,'\0',sizeof(client));
   memset(&server,'\0',sizeof(server));

//    server creation and verification
   server_sock= socket(AF_INET , SOCK_STREAM,0);
   if(server_sock == -1){
    printf("Server socket creation failed!\n");
    exit(0);
   }
    else{
   printf("Server socket Created !\n");
	}
//    assign IP , PORT
   server.sin_family = AF_INET;
   server.sin_port = htons(8000); //PORT NUMBER:8080
   server.sin_addr.s_addr = inet_addr(addr);

   if(bind(server_sock , (struct sockaddr*) &server , sizeof(server)) < 0){
    printf("ERROR\n");
		return -1;
   }
   else{
   printf(" Bind successful! \n");
   }
   listen(server_sock , 4);
   printf("Listening.... on 8000 port\n");
	while (1)
	{
		addr_size = sizeof(client);
		client_sock = accept(server_sock, (struct sockaddr *)&client, &addr_size);
		printf("Client Connected\n");
		bzero(buf, 1024);
		int n , m; 
		recv(client_sock, buf, sizeof(buf), 0);
		m = buf[1];
		n = buf[0];
		initialize(n);
		printf("Client: Vertices:%d  Edges:%d\n", m, n);
		bzero(buf, 1024);
		bzero(adjMat,n);
		recv(client_sock, adjMat, sizeof(adjMat), 0);
		printf("Adjacency Matrix:\n");
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<n;++j) 
			printf("%d ", adjMat[i][j]);
			printf("\n");

		}
		
		bzero(buf, 1024);
		recv(client_sock, buf, sizeof(buf), 0);
		int source = buf[0];
		int dest = buf[1];
		printf("Source:%d Destination:%d\n", source, dest);
		bzero(buf, 1024);
    //    Dijkstra algorithm implementation
       dijkstra(adjMat, source,n);
	   buf[0] = dist[dest];
	   send(client_sock, buf, sizeof(buf),0);
	   //close the socket connection
		close(client_sock);
	}
	return 0;
}