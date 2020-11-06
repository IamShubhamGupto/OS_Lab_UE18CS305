#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void consumer();
void producer();

int pipe_array[2];

int main(){
  	pid_t pid;
  	pipe(pipe_array);
  	pid = fork();
  	if(pid < 0){
    	printf("Fork failed!");
    	exit(-1);
  	}
	if(pid == 0){
   		consumer();
 	}else{
		producer();
 	}
  	return 0;
}
void producer(){
	close(pipe_array[0]);
	int produced,i;
	for(i=1; i <= 10; i++){
		produced=i;
		printf("Producer: sent %d\n",i);
		write(pipe_array[1],&produced,sizeof(int));
	}
  	exit(0);
}

void consumer(){
	close(pipe_array[1]);
	int consumed,i;
    for(i=1; i <= 10; i++){
     	read(pipe_array[0],&consumed,sizeof(int));
		printf("Consumer: got %d\n", consumed);
   	}
  	exit(0);
}



