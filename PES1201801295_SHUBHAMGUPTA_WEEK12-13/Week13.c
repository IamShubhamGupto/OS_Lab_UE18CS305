#include<stdio.h>
#include<stdlib.h>

int main(){
	int n,head_position,i,sum=0,max_range,difference;
	float time_taken;

	printf("Enter the max range of disk\n");
	scanf("%d",&max_range);
	printf("Enter the size of queue request\n");
	scanf("%d",&n);
	int* queue = (int*)malloc((n+1)*sizeof(int));
	printf("Enter the queue of disk positions to be read\n");

	for(i=1; i <= n; i++)
		scanf("%d",queue+i);
		
	printf("Enter the initial head position\n");
	scanf("%d",&head_position);
	queue[0] = head_position;

	for(i=0; i < n; i++){
		difference = abs(queue[i+1]-queue[i]);
		sum += difference;
		printf("Disk head moves from %d to %d with seek %d\n",queue[i],queue[i+1],difference);
	}

	printf("Total seek time is %d\n",sum);
	time_taken = (float)sum/n;
	printf("Average seek time is %f s\n",time_taken);

	free(queue);
	return 0;
}
