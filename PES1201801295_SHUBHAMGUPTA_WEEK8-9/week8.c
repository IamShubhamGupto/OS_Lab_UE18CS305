#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define SHARED 1
#define BSIZE 10
void *Producer(); 
void *Consumer(); 

sem_t empty;
sem_t full;
sem_t signal; 
int data;

int main(){
	pthread_t producer_th, consumer_th; 
	sem_init(&empty, SHARED, 1);
	sem_init(&full, SHARED, 0); 
	sem_init(&signal, SHARED, 1);
	pthread_create(&producer_th,NULL,Producer,NULL); 
	pthread_create(&consumer_th,NULL,Consumer,NULL); 
	pthread_join(producer_th,NULL); 
	pthread_join(consumer_th,NULL); 
	return 0;
}
void *Producer(){
	sem_wait(&empty);
	sem_wait(&signal); 
	int p_iter;
	for(p_iter=0; p_iter < BSIZE; p_iter++){    
		data=p_iter;               
		printf("Produced item is %d\n",data);
	}
	sem_post(&signal);
	sem_post(&full);
}
void *Consumer(){
	sem_wait(&full);
	sem_wait(&signal);
	int c_iter;
	for(c_iter=0; c_iter < BSIZE; c_iter++){
		printf("Consumed item is %d\n",c_iter);
	}
	sem_post(&signal);
	sem_post(&empty);
}
