#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/wait.h>
int main(int argc, char* argv[]){
    if(argc <= 1)
        exit(0);
    pid_t pid;
    char* argpass[argc];
    for(int i = 0; i < argc - 1; i++){
        argpass[i] = argv[i+1]; 
    }
    argpass[argc-1] = NULL;
    pid = fork();
    /*Child*/
    if(pid == 0){
        printf("Child is running, processing.\n");
        execvp(argpass[0], argpass);
        printf("Child is done, exiting.\n");
    /*Parent*/
    }else if(pid != -1){
        printf("Parent is waiting...\n");
        wait(NULL);
        printf("Parent is exiting...\n");
    }else{
        perror("Error while calling the fork function");
    }
    //free(argpass);
    return 0;
    
}