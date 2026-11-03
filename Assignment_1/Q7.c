#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAX_SIZE 99
#define STACKS 3
#define STACK_SIZE (MAX_SIZE/STACKS)

int stack[MAX_SIZE];
int tops[STACKS];

void constructStack(){
    for(int i=0;i<STACKS;++i){
        tops[i]=i*STACK_SIZE - 1;        
    }
}

void push(int pos,int val){
    if(pos<0 || pos>=STACKS){
        printf("Invalid stack number\n");
        return;
    }
    if(tops[pos]>=(pos+1)*STACK_SIZE - 1){
        printf("Overflow\n");
        return;
    }
    stack[++tops[pos]]=val;
}

int pop(int pos){
    if(pos<0 || pos>=STACKS){
        printf("Invalid stack number\n");
        return -1;
    }
    if(tops[pos]<=pos*STACK_SIZE - 1){
        printf("Underflow\n");
        return -1;
    }
    return stack[tops[pos]--];
}

void printStack(){
    for(int i=0;i<STACKS;++i){
        if(tops[i] < i*STACK_SIZE)
            printf("Empty");
        else {
            for(int j = i*STACK_SIZE; j <= tops[i]; ++j)
                printf("%d ", stack[j]);
        }
        printf("\n");
    }
}

int main(){
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Failed to open input.txt\n");
        return 1;
    }
    char op[10];
    int val;
    constructStack();

    srand(time(0));
    
    while(fscanf(fp, "%s", op)!=EOF){
        int pos=rand()%STACKS;

        if(strcmp(op, "PUSH")==0){
            fscanf(fp, "%d",&val);
            push(pos, val);
        }
        else if(strcmp(op, "POP")==0){
            pop(pos);
        }
        else{
            printf("INVALID OPERATION: %s\n", op);
        }
    }
    printStack();
    fclose(fp);
}
