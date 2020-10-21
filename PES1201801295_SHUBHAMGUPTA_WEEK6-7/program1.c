#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define BUFFER_SIZE 15
int in;
int out;
int buffer[BUFFER_SIZE];

void *producer();
void *consumer();

int main(){
    pthread_t producer_thread_id, consumer_thread_id;
    pthread_create(&producer_thread_id, NULL, producer, NULL);
    pthread_create(&consumer_thread_id, NULL, consumer, NULL);
    pthread_join(producer_thread_id, NULL);
    pthread_join(consumer_thread_id, NULL);
    return 0;
}
void* producer(){
    int produced = 1;
    while(1){
        printf("Job %d started\n", produced);
        produced++;
        //spinlock while buffer is full
        while(((in + 1) % BUFFER_SIZE) == out); 
        buffer[in] = produced;
        in = (in + 1) % BUFFER_SIZE;
    }
}

void* consumer(){
    int consumed = -1;
    while(1){
        //spinlock while no items are left to consume
        while(in == out);
        consumed = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Job %d finished\n", consumed);
    }
}

