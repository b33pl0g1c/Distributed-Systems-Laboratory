#include <stdio.h>
#define SIZE 9999 
#define INFINITY SIZE*SIZE
#define MAX(a, b) ((a > b) ? (a) : (b))
//defining the data structures.
int numOfEdges = 0;
int numOfVertices = 0;
long distance[SIZE][SIZE];
long shortestPath[SIZE];
//Function to print the shortest path.
void print(void)
{
	int i = 0;

	printf("DJIKSTRA'S ALGORITHM\n\n");
	printf("Vertex Number:");

	for (i = 1; i <= numOfVertices; ++i)
	{
		printf("%10d", i);
	}

	printf("\n\nShortest Path:");

	for (i = 1; i <= numOfVertices; ++i)
	{
		printf("%10ld", shortestPath[i]);
	}

	printf("\n\n");
}
//function implementing dijkstra's algorithm.
void dijkstra(int s) 
{
	int i = 0;
	int j = 0;
	int small = 0;
	int visited[SIZE];

	for (i = 1; i <= numOfVertices; ++i) 
	{
		shortestPath[i] = INFINITY;

		visited[i] = 0;
	}

	shortestPath[s] = 0;
	//checking if a vertex has been visited or not and updating the distance.
	for (j = 1; j <= numOfVertices; ++j)
	{
		small = -1;

		for (i = 1; i <= numOfVertices; ++i)
		{
			if (!visited[i] && ((small == -1) || (shortestPath[i] < shortestPath[small])))
			{
				small = i;
			}
		}

		visited[small] = 1;

		for (i = 1; i <= numOfVertices; ++i)
		{
			if (distance[small][i])
			{
				if (shortestPath[small] + distance[small][i] < shortestPath[i])
				{
					shortestPath[i] = shortestPath[small] + distance[small][i];
				}
			}
		}
	}
}

int main(int argc, char *argv[]) 
{
	int i = 0;
	int j = 0;
	int vertexU = 0;
	int vertexV = 0;
	int vertexW = 0;
	//taking input of the vertex and edges with their weights from dijkstra.txt file.
	//the file must be in the form u v and weight.
	FILE *theFile = fopen("dijkstra.txt", "r");

	fscanf(theFile, "%d", &numOfEdges);

	for (i = 0; i < numOfEdges; ++i)
	{
		for (j = 0; j < numOfEdges; ++j)
		{
			distance[i][j] = 0;
		}
	}

	numOfVertices = -1;

	for (i = 0; i < numOfEdges; ++i) 
	{
		fscanf(theFile, "%d%d%d", &vertexU, &vertexV, &vertexW);

		distance[vertexU][vertexV] = vertexW;

		numOfVertices = MAX(vertexU, MAX(vertexV, numOfVertices));
	}

	fclose(theFile);

	dijkstra(1);

	print();

	return 0;
}

