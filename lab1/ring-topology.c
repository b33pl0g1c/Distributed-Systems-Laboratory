#include<stdio.h>
#include<stdlib.h>
int n=5;
struct node
{
    int value;
    struct node *next;
};
void adjacencyMatrix(int matrix[n][n],int edges[][2],int edge)
{
    for(int i=0;i<edge;++i)
    {
        matrix[edges[i][0]-1][edges[i][1]-1]=1;
        matrix[edges[i][1]-1][edges[i][0]-1]=1;
    }
    printf("The Adjacency Matrix:\n");
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            printf(" %d ",matrix[i][j]);
        }
        printf("\n");
    }
}
void adjacentList(int matrix[n][n],int edges[][2],int edge)
{
    struct node* list[5]={NULL,NULL,NULL,NULL,NULL};
    for(int i=0;i<n;++i)
    {
        struct node *temp=(struct node*)malloc(sizeof(struct node));
        list[i]=temp;
        temp->value=i+1;
        temp->next=NULL;
        for(int j=0;j<n;++j)
        {
            if(matrix[i][j]==1)
            {
                temp->next=(struct node*)malloc(sizeof(struct node));
                temp=temp->next;
                temp->value=j+1;
                temp->next=NULL;
            }
        }
    }
    printf("\nThe Adjacency List:\n");
    for(int i=0;i<n;++i)
    {
        struct node *temp=list[i];
        printf("Node %d is connected to: ",temp->value);
        temp=temp->next;
        while(temp!=NULL)
        {
            printf(" %d ",temp->value);
            temp=temp->next;
        }
        printf("\n");
    }
}
int main()
{
    int degree[5];
    int edges[5][2]={{1,2},{2,3},{3,4},{4,5},{1,5}};   
    int edge=5;
    int matrix[n][n];
    for(int i=0;i<n;++i)
    for(int j=0;j<n;++j)
    matrix[i][j]=0;
    adjacencyMatrix(matrix,edges,edge);
    adjacentList(matrix,edges,edge);
    printf("\nThe Degree of the nodes is: \n");
    for(int i=0;i<n;++i)
    {
        int count=0;
        for(int j=0;j<n;++j)
        {
            if(matrix[i][j]==1)
            ++count;
        }
        printf("The degree of node %d is %d\n",i+1,count);
    }
    return 0;
}