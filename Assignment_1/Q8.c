#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* front = NULL;
struct node* rear = NULL;

int isempty(){
    if(front == NULL) return 1;
    else return 0;
}

void enqueue(int val){
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = val;
    newnode->next = NULL;
    if(rear == NULL){
        front = newnode;
        rear = newnode;
    }
    else{
        rear->next = newnode;
        rear = newnode;
    }
}

int dequeue(){
    if(isempty()){
        printf("No element in the queue");
        exit(1);
    }
    struct node* p = front;
    int val = p->data;
    front = front->next;
    free(p);
    return val;
}

void print(){
    if(isempty()){
        printf("No element in the queue\n");
        exit(1);
    }
    struct node* p = front;
    while(p != NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

void create(char* filename){
    FILE* fp = fopen(filename,"r");
    if(fp == NULL){
        printf("Error opening the file\n");
        return ;
    }

    int num;
    while(fscanf(fp,"%d",&num) != EOF){
        enqueue(num);
    }

}


int main(int argc, char* argv[]){
    printf("Hello!\n");
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    create(argv[1]);
    printf("The queue is as follows: \n");
    print();

    while(1){
        int choice;
        printf("Enter your choice:\n");
        printf("Enter 1 for enqueue operation\n");
        printf("Enter 2 for dequeue operation\n");
        printf("Enter 3 to display the queue\n");
        printf("Enter 4 to exit\n");
        scanf("%d",&choice);

        if(choice == 4){
            break;
        }

        switch(choice){
            case 1:{
                printf("Enter the value:");
                int val;
                scanf("%d",&val);
                enqueue(val);
                break;
            }
            case 2: {
                int val = dequeue();
                printf("The value removed is %d\n",val);
                break;
            }
            case 3: {
                print();
                break;
            }
        }
    }
    return 0;
}
