#include<stdio.h>
#include<stdlib.h>

struct tree {
    struct tree* lchild;
    int data;
    struct tree* rchild;
};

struct node {
    struct tree* data;
    struct node* next;
};


struct tree *root;

// global declaration
struct node* front = NULL;
struct node* rear = NULL;

int isempty(){
    if(front == NULL) return 1;
    else return 0;
}

void enqueue(struct tree* val){
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = val;
    newnode->next = NULL;
    if(rear == NULL){
        // empty linked list no node is there
        front = newnode;
        rear = newnode;
    }
    else{
        rear->next = newnode;
        rear = newnode;
    }
}

struct tree* dequeue(){
    if(isempty()){
        printf("No element in the queue");
        exit(1);
    }
    struct node* p = front;
    struct tree* val = p->data;
    front = front->next;

    if(front == NULL){
        rear = NULL;
    }
    
    free(p);
    return val;
}


void create(char filename[]){
    FILE* fp = fopen(filename,"r");
    if(fp == NULL){
        printf("Error opening the file\n");
        return;
    }

    struct tree *p, *t;
    int x;
    if(fscanf(fp,"%d",&x) == 1){
        root = (struct tree*)malloc(sizeof(struct tree));
        root->data = x;
        root->lchild = NULL;
        root->rchild = NULL;
        enqueue(root);
    }
    else{
        return;
    }

    while(! isempty()){
        p = dequeue();
        if(fscanf(fp,"%d",&x) == 1){
            t = (struct tree*)malloc(sizeof(struct tree));
            t->data = x;
            t->lchild = NULL;
            t->rchild = NULL;
            p->lchild = t;
            enqueue(t);
        }
        else{
            return;
        }

        if(fscanf(fp,"%d",&x) == 1){
            t = (struct tree*)malloc(sizeof(struct tree));
            t->data = x;
            t->lchild = NULL;
            t->rchild = NULL;
            p->rchild = t;
            enqueue(t);
        }
        else{
            return;
        }
    }

}


int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1; // Indicate error
    }


    printf("Hello!\n");
    create(argv[1]);
    printf("Tree successfully created!\n");
    return 0;
}
