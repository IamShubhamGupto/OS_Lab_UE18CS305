#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>


void childProcess(int arr[5]);
void parentProcess(int arr[5]);

int main(){
    pid_t pid;
    srand(time(0));
    int* arr = (int*)malloc(sizeof(int)*5);
    for(int i = 0 ; i < 5; i++){
        arr[i] = rand()%10;
    }

    printf("Original Array\n");
    for(int i = 0; i < 5; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");

    pid = fork();
    if(pid == 0){
        childProcess(arr);
    }else{
        parentProcess(arr);
    }
    free(arr);
    return 0;
}

void childProcess(int arr[5]){
    for(int i = 1; i < 5; i++){
        arr[i] += arr[i-1];
    }
    /*
    printf("Array after passing through childProcess\n");
    for(int i = 0; i < 5; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    */
    printf("Partial Sum of array = %d\n",arr[4]);
    
}
void parentProcess(int arr[5]){
    for(int i = 1; i < 5; i++){
        arr[i] *= arr[i-1];
    }
    /*
    printf("Array after passing through parentProcess\n");
    for(int i = 0; i < 5; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    */
    printf("Partial Product of array = %d\n",arr[4]);
}
//PES1201801295