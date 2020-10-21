#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define BUFFERSIZE 15
int in=0;
int out=0;
int buffer[BUFFERSIZE];
int item_count = 0;	
int mutex = 1;

void wait(int*);
void signal(int*);
void *producer();
void *consumer();

int main(){
    pthread_t producer_t, consumer_t;
    pthread_create(&producer_t, NULL, producer, NULL);
    pthread_create(&consumer_t, NULL, consumer, NULL);
    pthread_join(producer_t, NULL);
    pthread_join(consumer_t, NULL);
    return 0;
}
//check if items are there in buffer, if no items, spinlock consumer
void wait(int *semaphore){
	while(*semaphore <= 0);
	*semaphore -= 1;
}
//update items semaphore
void signal(int *semaphore){
	*semaphore += 1;
}
//produce item to buffer
void *producer(){
    int produced = 0;
    while(1){
        //lock mutex
        wait(&mutex);
        //critical section
		produced++;
		printf("Job %d started\n", produced);
		buffer[in] = produced;
        in = (in+1)%BUFFERSIZE;
        //update semaphore
		signal(&item_count);
        //release mutex
        signal(&mutex);	
        sleep(1);
    }
}
//consume item from buffer
void *consumer(){
    int consumed = -1;
    while(1){   
        //lock mutex	
        wait(&item_count);
		wait(&mutex);
        //critical section		
		consumed = buffer[out];
		printf("Job %d finished\n", consumed);
        out = (out+1)%BUFFERSIZE;
        //release mutex
		signal(&mutex);
        sleep(1);
    }
}


