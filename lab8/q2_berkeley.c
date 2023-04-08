#include<stdio.h>
#include<stdlib.h>
#define MAX_NODES 10
#define MASTER_NODE 1

int main(){
    float nodes[MAX_NODES];
    float diff[MAX_NODES];
    int n;
    printf("Enter the no of nodes:\n");
    scanf("%d",&n);
    float sum=0;
    float avg;
    int i;
    //get the clock valuues.
    for (int i = 0; i < n; i++)
    {
        printf("Enter the clock value for node %d:",i);
        scanf("%f",&nodes[i]);
        if(i!=MASTER_NODE){
            sum+=nodes[i];
        }
    }
    //the average time.
    avg=sum/(n-1);


    //Adjust the clock.
    for(int i=0;i<n;i++){
            //difference between the master and slave/
        diff[i]=nodes[i]-avg;
        if(i==0){
            nodes[i]=avg;
        }
        else{
            nodes[i]=nodes[i]-diff[i];
        }
    }
    //print the clock.
    for(int i=0;i<n;i++){
        printf("Node %d has clock:%.2f\n",i,nodes[i]);
    }
    return 0;
    
}