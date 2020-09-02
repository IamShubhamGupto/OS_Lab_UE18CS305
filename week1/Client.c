#include<stdio.h>
#include<stdlib.h>
#include "Header.h"
int main(){
    int n;
    printf("ENTER SIZE OF THE ARRAY : \n");
    scanf("%d",&n);
    int* arr = (int*)malloc(sizeof(int)*n);
    printf("ENTER ELEMENTS OF THE ARRAY : \n");
    for(int i = 0; i < n; i++){
        scanf("%d",(arr+i));
    }
    print_array(arr, n);
    print_reverse_array(arr,n);
    return 0;
}