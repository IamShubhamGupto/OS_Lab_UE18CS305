#include<stdio.h>
#include<stdlib.h>
static void displayRR(char** , int* , int, int);
static void compute_waiting_time(char**, int*, int*, int, int);
static void compute_turnaround_time(char**, int*, int*, int*, int);

int main(){
    printf("Enter number of processes: \n");
    int n;
    int i;
    int quantum;
    scanf("%d",&n);
    char** process_names = (char**)malloc(sizeof(char*)*n);
    int* burst_times = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n; i++){
        process_names[i] = (char*)malloc(sizeof(char)*4);
        printf("\nEnter name of the process:\n");
        scanf("%s",process_names[i]);
        printf("Enter the burst time:\n");
        scanf("%d",(burst_times+i));
    }
    printf("Enter time quantum: \n");
    scanf("%d",&quantum);
    displayRR(process_names, burst_times,n, quantum);
    for(i = 0; i<n; i++){
        free(process_names[i]);
        process_names[i] = NULL;
    }
    free(process_names);
    free(burst_times);    
    return 0;
}

static void compute_waiting_time(char** process_names, int* burst_times, int* waiting_time, int n, int quantum){
    int* copy = (int*)malloc(sizeof(int)*n);
    int i;
    for(i = 0; i < n; i++){
        copy[i] = burst_times[i];
    }
    int current_time = 0;
    while(1){
        int done = 1;
        for(i = 0; i < n; i++){
            if(copy[i] > 0){
                done = 0;
                if(copy[i] > quantum){
                    current_time += quantum;
                    copy[i] -= quantum;
                }else{
                    current_time += copy[i];
                    waiting_time[i] = current_time - burst_times[i];
                    copy[i] = 0;
                }
            }
        }
        if(done)
            break;
    }
    free(copy);
}

static void compute_turnaround_time(char** process_names, int* burst_times, int* waiting_time, int* turnaround_time, int n){
    for(int i = 0; i < n; i++){
        turnaround_time[i] = waiting_time[i] + burst_times[i];
    }
}
static void displayRR(char** process_names, int* burst_times,int n, int quantum){
    int* waiting_time = (int*)malloc(sizeof(int)*n);
    int* turnaround_time = (int*)malloc(sizeof(int)*n);
    int t_waiting_time = 0;
    int t_turnaround_time = 0;
    int i;
    compute_waiting_time(process_names, burst_times, waiting_time, n, quantum);
    compute_turnaround_time(process_names,burst_times, waiting_time, turnaround_time, n);
    printf("Process Name\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for(i = 0; i < n; i++){
        t_waiting_time += waiting_time[i];
        t_turnaround_time += turnaround_time[i];
        printf("%s\t\t%d\t\t%d\t\t%d\n",process_names[i],burst_times[i],waiting_time[i],turnaround_time[i]);
    }
    printf("Average Waiting time is %f\n",((float)t_waiting_time)/n);
    printf("Average Turn around time is %f\n",((float)t_turnaround_time)/n);
    free(turnaround_time);
    free(waiting_time);
}
