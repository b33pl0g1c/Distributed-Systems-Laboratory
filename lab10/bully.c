#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int generateRandom(){
    return (random()%5)+1;
}
struct process{
    int no;
    int priority;
    int active;
    struct process *next;
};
typedef struct process proc;

struct priority{
    int pri;
    struct priority *next;
    proc *pp;
};
typedef struct priority pri;
//attaching processes and their priorities.
pri* Priority(proc *prochead, pri *prihead){
    
    proc *p1;
    pri *p2,*p3;
    p1=prochead;

    while(p1->next !=prochead){
        //if active.
        if(p1->active==1){
            //if no priority
            if(prihead==NULL){
                prihead=(pri*) malloc(sizeof(pri));
                //assign priority
                prihead->pri=p1->priority;
                prihead->next=NULL;
                //assign process
                prihead->pp=p1;
                p2=prihead;
            }
            else{
                p3=(pri*) malloc(sizeof(pri));
                p3->pri=p1->priority;
                p3->pp=p1;
                p3->next=NULL;
                p2->next=p3;
                p2=p2->next;
            }
            p1=p1->next;
        }
        else{
            //move to next process.
            p1=p1->next;
        }
    }
    p3=(pri*) malloc(sizeof(pri));
    p3->pri=p1->priority;
    p3->pp=p1;
    p3->next=NULL;
    p2->next=NULL;
    p3=prihead;
    return prihead;
}
//find the priority.
int findPriority(pri* prihead){
    pri *p1;
    int max=-1000;
    int prior=0;
    p1=prihead;
    while(p1!=NULL){
        //if greater than max and process is active.
        if(max<p1->pri && p1->pp->active==1){
            max=p1->pri;
            prior=p1->pp->no;
        }
        //move to next process.
        p1=p1->next;
    }
    return prior;
}
//Implementing the Bully Algorithm.
void bully(){
    proc *head;
    proc *p1;
    proc *p2;
    int n,i,pr,maxPriority, active,processId,max,o;

    char ch;
    head=NULL;
    p1=NULL;
    p2=NULL;
    printf("Performing the algorithm for 5 processes:-\n");
    for(int i=0;i<5;i++){
        // pr=generateRandom();
        // printf("The priority of p[%d] generated randomly is:%d\t",i+1,pr);
        printf("Enter the priority for process p[%d]",i+1);
        scanf("%d",&pr);
        printf("Is process[p(%d)] Active? (0/1):",i+1);
        scanf("%d",&active);

        if(head==NULL){
            head = (proc*) malloc(sizeof(proc));
            if(head==NULL){
            printf("Memory Allocation Error............ :(\n");
            exit(0);
            }
        head->no=i+1;
        head->priority=pr;
        head->active=active;
        head->next=head;
        p1=head;
        }
        else{
            p2=(proc*)malloc(sizeof(proc));
            if(p2==NULL){
            printf("Memory Allocation Error............ :(\n");
            exit(0);
            }
            p2->no=i+1;
            p2->priority=pr;
            p2->active=active;
            p1->next=p2;
            p2->next=head;
            p1=p2;
        }
    }
    printf("Enter the Process ID that invokes election algorithm:");
    scanf("%d",&processId);
    p2=head;
    while(p2->next!=head){
        if(p2->no==processId){
            p2=p2->next;
            break;
        }
        p2=p2->next;
    }
    printf("Election has been invoked by Process %d \n",processId);
    printf("Election message sent...................\n");
    while(p2->next!=head){
        if(p2->no>processId){
            printf("%d\t",p2->no);
            sleep(1);
        }
        p2=p2->next;
    }
       printf("%d", p2->no);
       sleep(1);
        p2 = head;
        max = 0;
   while (1) {
      if (p2->priority > max && p2->active == 1)
         max = p2->no;
      p2 = p2->next;
      if (p2 == head)
         break;
   }
   printf("\nProcess with the id %d is the co-ordinator\n", max);
}
void main(){
    bully();
}