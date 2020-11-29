#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
void  ChildProcess(int);                /* child process prototype  */

void  main(int argc, char* argv[])
{
    int n;
    if(argc <= 1){
        exit(0);
    }else{
        n = atoi(argv[1]);
    }
    printf("n = %d\n",n);
     pid_t  pid;

     pid = fork();
     if (pid == 0) 
          ChildProcess(n);
}
void ChildProcess(int n)
{
    int a = 0;
    int b = 1;
    //printf("%d %d ",a,b);
    int i = 3;
    if( n <=1){
        printf("%d\n",a);
    }else if(n == 2){
        printf("%d %d ",a,b);
    }else{
        printf("%d %d ",a,b);
        while(i <= n){
            int t = b;
            b = a+b;
            a = t;
            i++;
            printf("%d ",b);
        }
    }
     printf("\n   *** Child process is done ***\n");
}
//PES1201801295