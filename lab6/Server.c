#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include "graph.c"

#define LISTENQ 10

void error(const char *msg)
{
 perror(msg);
 exit(1);
}

struct Graph* tree_topology(int n)
{
    struct Graph* g= createGraph(n);
    int i=0;
    while((2*i) +1 <n || (2*i)+2 <n)
    {
        addEdge(g, i, (2*i) +1);
        if((2*i)+2 <n)
        addEdge(g, i, (2*i)+2);
        i++;
    }
    return g;
}

struct Graph* ring_topology(int n)
{
    struct Graph* g = createGraph(n);
    int v;
    for (v = 0; v < n; ++v)
    addEdge(g, v, (v+1)%n);
    return g;
}

struct Graph* star_topology(int n)
{
    struct Graph* g= createGraph(n);
    int v;
    for (v = 1; v < n; ++v)
    addEdge(g, 0, v);
    return g;
}

void marshalling(struct Graph* g, char buffer[])
{
    int v;
    char snum[5];
    sprintf(snum, "%d", g->n);
    strcat(snum, " ");
    strcat(buffer, snum);
    bzero(snum, 5);
    for (v = 0; v < g->n; v++)
    {
        struct node* temp = g->adjLists[v];
        sprintf(snum, "%d", v);
        strcat(snum, " ");
        strcat(buffer, snum);
        bzero(snum, 5);
        sprintf(snum, "%d", g->degree[v]);
        strcat(snum, " ");
        strcat(buffer, snum);
        bzero(snum, 5);
        while (temp) {
            sprintf(snum, "%d", temp->vertex);
            strcat(snum, " ");
            strcat(buffer, snum);
            bzero(snum, 5);
            temp = temp->next;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
    fprintf(stderr,"usage: %s Port\n", argv[0]);
    exit(1);
    }
    printf("\t\t|| Server Is Active ||\t\t\n\n");
    int sockfd, newsockfd, portno, n;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
    error("Error in opening socket!!");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
    error("Binding Failed!!");
    listen(sockfd, LISTENQ);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if(newsockfd <0)
    error("Error on Accept");
    printf("Enter\n1-Tree topology\n2-Ring Topology\n3-Star topology\n");
    bzero(buffer, 256);
    n= read(newsockfd, buffer, 255);
    if(n < 0) error("Error on Reading!!");
    int num;
    sscanf(buffer, "%d", &num);
    printf("Client : %d\n", num);
    bzero(buffer, 255);
    char buffer1[] = "Enter # of nodes:-\n";
    n = write(newsockfd, buffer1, strlen(buffer1));
    if(n < 0)
    error("Error on Writing!!");
    n= read(newsockfd, buffer, 255);
    if(n < 0) error("Error on Reading!!");
    int no_nodes;
    sscanf(buffer, "%d", &no_nodes);
    printf("\nEnter # of nodes:-\n");
    printf("Client : %d\n", no_nodes);
    bzero(buffer, 255);
    struct Graph* g;
    switch(num)
    {
        case 1:
        g = tree_topology(no_nodes);
        marshalling(g, buffer);
        n = write(newsockfd, buffer, strlen(buffer));
        if(n < 0)
        error("Error on Writing!!");
        bzero(buffer, 255);
        break;
        case 2:
        g = ring_topology(no_nodes);
        marshalling(g, buffer);
        n = write(newsockfd, buffer, strlen(buffer));
        if(n < 0)
        error("Error on Writing!!");
        bzero(buffer, 255);
        break;
        case 3:
        g = star_topology(no_nodes);
        marshalling(g, buffer);
        n = write(newsockfd, buffer, strlen(buffer));
        if(n < 0)
        error("Error on Writing!!");
        bzero(buffer, 255);
        break;
        default:
        printf("Wrong Choice entered");
        break;
    }
    printGraph(g);
    printf("\nSending above generated topology to client:- \n");
    close(newsockfd);
    close(sockfd);
    return 0;
}
