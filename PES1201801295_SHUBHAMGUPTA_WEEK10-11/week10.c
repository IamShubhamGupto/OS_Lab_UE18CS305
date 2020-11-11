#include<stdio.h>
#include<stdlib.h>
struct node{
    int segment_;
    int process_index_;
    struct node* next_;
};
typedef struct node node_t;

struct list{
    node_t* root_;
};
typedef struct list list_t;

static list_t* initialize_list();
static node_t* make_node(int);
static void insert_node(list_t*,node_t*);
static void destroy_list(list_t*);
static void displayBestFit(list_t*, char*, int*, int, int);

static list_t* initialize_list(){
    list_t* pq = (list_t*)malloc(sizeof(list_t));
    pq->root_ = NULL;
    return pq;
}

static node_t* make_node(int segment){
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->segment_ = segment;
    node->process_index_ = -1;
    node->next_ = NULL;
    return node;
}

static void insert_node(list_t* pq,node_t* node){
    node_t* current = pq->root_;
    node_t* previous = NULL;
    
    if(current == NULL || current->segment_ > node->segment_){
        node->next_ = current;
        pq->root_ = node;
        return;
    }
    while(current != NULL && current->segment_ < node->segment_){
        previous = current;
        current = current->next_;
    }
    node->next_ = current;
    previous->next_ = node;
}
static void destroy_list(list_t* pq){
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
static void assign_processes(list_t* pq, int* process_size, int* assigned, int N_s, int N_p){
    node_t* temp;
    node_t* prev;
    for(int i = 0; i < N_p; i++){
        temp = pq->root_;
        prev = NULL;
        while(temp != NULL && temp->segment_ <= process_size[i]){
            prev = temp;
            temp = temp->next_;
        }
        if(prev == NULL){
            if(temp->process_index_ == -1){
                temp->process_index_ = i;
                assigned[i] = 1;
            }else{
                while(temp != NULL && temp->process_index_ != -1){
                    prev = temp;
                    temp = temp->next_;
                }
                if(temp != NULL && temp->process_index_ == -1){
                    temp->process_index_ = i;
                    assigned[i] = 1;
                }else if(temp == NULL && prev->process_index_ == -1){
                    prev->process_index_ = i;
                    assigned[i] = 1;
                }
            }
            
        }else if (prev != NULL && prev->process_index_ == -1 && prev->segment_ >= process_size[i]){
            prev->process_index_ = i;
            assigned[i] = 1;
        }else if(prev != NULL && prev->process_index_ != -1){
            while(temp != NULL && temp->process_index_ != -1){
                prev = temp;
                temp = temp->next_;
            }
            if(temp != NULL && temp->process_index_ == -1){
                temp->process_index_ = i;
                assigned[i] = 1;
            }else if(temp == NULL && prev->process_index_ == -1){
                prev->process_index_ = i;
                assigned[i] = 1;
            }
        }
    }
}
static void displayBestFit(list_t* pq, char* process_name, int* process_size, int N_s, int N_p){
    node_t* curr = pq->root_;
    int i = 0;
    printf("Partition No  Partition Size  Partition Status  Fragment Size\n");
    while(curr != NULL){
        if(curr->process_index_ == -1){
            printf("%d\t\t%d\t\tfree\t\t\n",i,curr->segment_);
        }else{
            printf("%d\t\t%d\t\tallocated(%c)\t\t%d\n",i,curr->segment_,process_name[curr->process_index_],
                curr->segment_ - process_size[curr->process_index_]);
        }
        curr = curr->next_;
        ++i;
    }
}
int main(){
    printf("Enter number of memory segments:\n");
    list_t* pq = initialize_list();
    int N_s, N_p, segment_size;
    //char process_name;
    scanf("%d",&N_s);
    for(int i = 0; i < N_s; i++){
        printf("Enter partition size:\n");
        scanf("%d",&segment_size);
        insert_node(pq, make_node(segment_size));
    }
    printf("Enter number of processes to assign to memory: \n");
    scanf("%d",&N_p);
    int* process_size = (int*)malloc(sizeof(int)*N_p);
    char* process_name = (char*)malloc(sizeof(char)*N_p);
    int* assigned = (int*)calloc(N_p,sizeof(int));
    for(int i = 0; i < N_p; i++){
        printf("Enter name of the process:\n");
        scanf(" %s",process_name+i);
        printf("Enter the size of the process:\n");
        scanf("%d",process_size+i);
    }
    assign_processes(pq,process_size,assigned,N_s,N_p);
    displayBestFit(pq,process_name,process_size, N_s, N_p);
    destroy_list(pq);
    free(process_size);
    free(process_name);
    free(assigned);
    return 0;
}
