#include <stdio.h>
#include <stdlib.h>

struct node {
    int vertex;
    struct node* next;
};

struct node* createNode(int);

struct Graph {
    int n;
    struct node** adjLists;
    int *degree;
};

struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode -> vertex = v;
    newNode -> next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph -> n = vertices;
    graph -> adjLists = malloc(vertices * sizeof(struct node*));
    graph -> degree = malloc(vertices * sizeof(int));
    int i;
    
    for(i=0; i<vertices; i++) {
        graph -> degree[i] = 0;
        graph -> adjLists[i] = NULL;
    }
    
    return graph;
}

void addEdge(struct Graph* graph, int s, int d) {
    struct node* newNode = createNode(d);
    newNode -> next = graph -> adjLists[s];
    graph -> adjLists[s] = newNode;
    newNode = createNode(s);
    newNode -> next = graph -> adjLists[d];
    graph -> adjLists[d] = newNode;
    graph -> degree[s] += 1;
    graph -> degree[d] += 1;
}

void addEdge_unmarshalling(struct Graph* graph, int s, int d)
{
 struct node* newNode = createNode(d);
 newNode->next = graph->adjLists[s];
 graph->adjLists[s] = newNode;
}

void printGraph(struct Graph* graph) {
    int v;
    printf("\nAdjacency list of the topology: \n");
    
    for(v=0; v<graph->n; v++) {
        struct node* temp = graph -> adjLists[v];
        printf("Node %d", v);
        while(temp) {
            printf("--> %d", temp->vertex);
            temp = temp -> next;
        }
        
        printf("\t(Degree = %d)", graph -> degree[v]);
        printf("\n");
    }
}

