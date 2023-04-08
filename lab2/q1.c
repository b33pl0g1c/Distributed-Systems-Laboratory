//-------------------------------
//| Pleasse run it on onlinegdb  |
//-------------------------------

#include<stdio.h>

#include <stdlib.h>
struct node {
  int vertex;
  struct node* next;
};
struct Graph {
  int numVertices;
  struct node** adjLists;
};

struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}
struct Graph* createAGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc((vertices) * sizeof(struct node*));

  for (int i = 0; i < vertices; i++)
    graph->adjLists[i] = NULL;

  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int s, int d) {
  // Add edge from s to d
  struct node* newNode = createNode(d);
  newNode->next = graph->adjLists[s];
  graph->adjLists[s] = newNode;/////////////

  // Add edge from d to s
  newNode = createNode(s);
  newNode->next = graph->adjLists[d];
  graph->adjLists[d] = newNode;////////////
}

// Print the graph
void printGraph(struct Graph* graph) {
  int v;
  for (v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjLists[v];
    printf("\n Vertex %d\n: ", v);
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}

int main() {
    int vertex1, vertex2;
    int v, e;  
    int d[25] = {0};
    int adjMat[25][25] = {0};
    printf("Enter the total number of nodes: ");
    scanf("%d", &v);
    printf("Enter the total number of edges: ");
    scanf("%d", &e);
    for(int i = 0 ; i < e; i++) {
        printf("enter the two endings of edge number %d\n", i);
        scanf("%d %d", &vertex1, &vertex2);
        adjMat[vertex1][vertex2] = 1;
        adjMat[vertex2][vertex1] = 1;
        d[vertex1]++;
        d[vertex2]++;
    }

    printf("\n");
    printf("adjacency matrix representing  topology: \n");
    for(int i = 0; i < v; i++) {
        for(int j = 0; j < v; j++) {
            printf("%d ", adjMat[i][j]);
        }
        printf("\n");
    }


    printf("\n");
    printf("degree of all the nodes:\n");
    for(int i = 0; i < v; i++) {
        printf("Vertex of %d node is: %d \n", i,d[i]);
    }

    struct Graph* g = createAGraph(v);
    for(int i = 0 ; i < v ; i++) {
        for(int j = i ; j < v ; j++) {
            if(adjMat[i][j]) {
                addEdge(g, i, j);
            }
        }
    }

    printf("\n");
    printGraph(g);

    return 0;
}