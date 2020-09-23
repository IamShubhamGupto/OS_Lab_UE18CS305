#include<stdio.h>
#include<stdlib.h>
struct node{
    int job_no_;
    int burst_time_;
    int priority_;
    struct node* next_;
};
typedef struct node node_t;
struct list{
    node_t* root_;
};
typedef struct list queue_t;

queue_t* initialize_queue();
node_t* make_node(int, int, int);
void insert_node(queue_t*,node_t*);
void destroy_queue(queue_t*);
void displaySJF(queue_t*, int);

queue_t* initialize_queue(){
    queue_t* pq = (queue_t*)malloc(sizeof(queue_t));
    pq->root_ = NULL;
    return pq;
}

node_t* make_node(int job_no, int burst_time, int pririorty){
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->job_no_ = job_no;
    node->burst_time_ = burst_time;
    node->priority_ = pririorty;
    node->next_ = NULL;
    return node;
}

void insert_node(queue_t* pq,node_t* node){
    node_t* current = pq->root_;
    node_t* previous = NULL;
    if(current == NULL){
        pq->root_ = node;
        return;
    }
    if(current != NULL && current->priority_ > node->priority_){
        node->next_ = current;
        pq->root_ = node;
        return;
    }
    while(current != NULL && current->priority_ < node->priority_){
        previous = current;
        current = current->next_;
    }
    node->next_ = current;
    previous->next_ = node;
}

void displaySJF(queue_t* pq, int n){
    node_t* current = pq->root_;
    node_t* previous = NULL;
    if(current == NULL)
        return;
    int waiting_time = 0;
    int turnaround_time = 0;
    int ww_time = 0;
    int tt_time = 0;
    printf("\nJob\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time\n");
    
    while(current != NULL){
        turnaround_time += current->burst_time_;
        tt_time += turnaround_time;
        ww_time += waiting_time;
        printf("%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n",current->job_no_,current->priority_,current->burst_time_,waiting_time,turnaround_time);
        waiting_time += current->burst_time_;
        
        current = current->next_;
    }
    //printf("%d %d",waiting_time,turnaround_time);
    printf("\nAverage waiting time = %f\n",(float)ww_time/n);
    printf("Average turnaround time = %f\n",(float)tt_time/n);
    printf("----------------------------------\n");
}

void destroy_queue(queue_t* pq){
    if(pq->root_ == NULL)
        return;
    node_t* current = pq->root_;
    node_t* temp = NULL;
    while(current != NULL){
        temp = current;
        current = current->next_;
        free(temp);
        temp = NULL;
    }
}
int main(){
    printf("**** Priority Scheduling ****\n");
    queue_t* pq = initialize_queue();
    int n,burst_time,priority;
    printf("Enter number of jobs: \n");
    scanf("%d",&n);
    for(int i = 1; i <= n; i++){
        printf("\nEnter Burst Time of process %d \n",i);
        scanf("%d",&burst_time);
        printf("Enter Priority of process %d \n",i);
        scanf("%d",&priority);
        insert_node(pq,make_node(i,burst_time,priority));
    }
    displaySJF(pq,n);
    destroy_queue(pq);
    free(pq);
    pq = NULL;
    return 0;
}