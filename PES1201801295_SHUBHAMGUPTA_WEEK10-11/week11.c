#include<stdio.h>
#include<stdlib.h>
#define DEBUG 0
int min(int* last_visited, int frames){
    int minimum = 0;
    for(int i = 1 ; i < frames; i++){
        //printf("last visted array %d ",last_visited[i]);
        //printf("\nlast visited of miniym = %d, last visited i %d\n", last_visited[minimum],last_visited[i]);
        if( last_visited[i] < last_visited[minimum]){
            if(DEBUG){
                printf("new minimum = %d\n",i);
            }
            minimum = i;
        }
            
    }
    return minimum;
}
int main(){
    printf("Enter the length of reference string -- \n");
    int length, frames, mem, i,j,found = 0;
    scanf("%d",&length);
    int* reference_strings = (int*)malloc(sizeof(int)*length);
    
    printf("Enter the reference string -- \n");
    for(i = 0; i < length; i++){
        scanf("%d",reference_strings+i);
    }
    printf("Enter the number of frames -- \n");
    scanf("%d",&frames);
    int* frame_array = (int*)malloc(sizeof(int)*frames);
    int* last_visited = (int*)calloc(frames, sizeof(int));
    for(i = 0; i < frames; i++){
        frame_array[i] = -1;
        last_visited[i] = -1;
    }
    int replace_this = 0,pf = 0;
    //LRU starts here
    for(i = 0; i < length; i++){
        found  = 0;
        for(j = 0; j < frames; j++){
            if(frame_array[j] == reference_strings[i]){
                if(DEBUG){
                    printf("FOUND at %d\n",j);
                }
                last_visited[j]=i;
                found =1;
                break;
            }
        }
        if(found){
            for(j = 0; j < frames; j++){
                printf("%d ",frame_array[j]);
            }
            printf("\n");
        }else{
            ++pf;
            replace_this = min(last_visited,frames);
            if(frame_array[replace_this] == -1){
                replace_this = i%frames;
            }
            last_visited[replace_this] = i;
            frame_array[replace_this] = reference_strings[i];
            for(j = 0; j < frames; j++){
                printf("%d ",frame_array[j]);
            }
            printf("PF No. -- %d\n",pf);
        }
    }
    printf("The number of page faults using LRU is %d\n",pf);
    free(reference_strings);
    free(last_visited);
    free(frame_array);
    return 0;
}