#include<stdlib.h>
#include<stdio.h>
void print_array(int* arr, int n){
    printf("Input array is\n");
    for(int i = 0; i < n; i++){
        printf("%d",arr[i]);
    }
    printf("\n");
}
void print_reverse_array(int* arr, int n){
    printf("Reversed array is\n");
    for(int i = n-1; i > -1; i--){
        printf("%d",arr[i]);
    }
    printf("\n");
}