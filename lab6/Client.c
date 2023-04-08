//Client
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include "graph.c"

#define LISTENQ 10

void error(const char *msg)
{
 perror(msg);
 exit(1);
}

struct Graph* unmarshalling(char str[])
{
    char *token = strtok(str, " ");
    int num, n;
    sscanf(token, "%d", &num);
    struct Graph* g = createGraph(num);
    n=num;
    token = strtok(NULL, " ");
    int i;
    for(i=0; i<n; i++)
    {
        int num1;
        sscanf(token, "%d", &num1);
        int v = num1;
        token = strtok(NULL, " ");
        sscanf(token, "%d", &num1);
        g->degree[v] = num1;
        token = strtok(NULL, " ");
        int j;
        for(int j=0; j < g->degree[v]; j++)
        {
            sscanf(token, "%d", &num1);
            addEdge_unmarshalling(g, v, num1);
            if(token != NULL)
            token = strtok(NULL, " ");
        }
    }
    return g;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr,"usage: %s <IPaddress> port\n", argv[0]);
        exit(1);
    }

    int sockfd, portno, n;
    char buffer[256];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sockfd < 0)
    {
        error("Error in opening socket!!");
    }
    server = gethostbyname(argv[1]);

    if(server == NULL)
    {
        fprintf(stderr, "Error! No such host found!!\n");
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(8080);
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("Connection failed!!");
    bzero(buffer, 256);
    printf("Enter\n1-Tree topology\n2-Ring Topology\n3-Star topology\n");
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if(n < 0)
    error("Error on Writing!!");
    bzero(buffer, 256);
    n= read(sockfd, buffer, 256);
    if(n < 0)
    error("Error on Reading!!");
    printf("Server : %s", buffer);
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    bzero(buffer, 256);
    n= read(sockfd, buffer, 256);
    if(n < 0)
    error("Error on Reading!!");
    struct Graph* g;
    g = unmarshalling(buffer);
    printf("\nTopology received from server :\n");
    printGraph(g);
    close(sockfd);
    return 0;
}
