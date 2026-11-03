#include<stdio.h>
#include<stdlib.h>
#define MAX 100

void createHeap(int heap[],int n){
    int i = n;
    int temp = heap[n];

    while(i>1 && temp>heap[i/2]){
        heap[i] = heap[i/2];
        i = i/2;
    }
    
    heap[i] = temp;
}

int main(int argc, char* argv[]){
    printf("The max heap is as follows:\n");
    if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    FILE* fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("Error in opening file\n");
        return 0;
    }

    int num;
    int heap[MAX];
    heap[0] = 0;
    int size=1;

    while(fscanf(fp,"%d",&num) != EOF){
        heap[size] = num;
        size++;
    }

    // Function to create the heap
    for(int i=2;i<size;i++){
        createHeap(heap,i);
    }

    for(int i=0;i<size;i++){
        printf("%d  ",heap[i]);
    }
    printf("\n");
    return 0;
}