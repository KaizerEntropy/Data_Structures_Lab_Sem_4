#include<stdio.h>
#include<stdlib.h>

struct node{
    struct node* lchild;
    int data;
    struct node* rchild;
};

struct node* root = NULL;

void insert(int key){
    struct node* t = root;
    struct node* r = NULL;
    struct node* p = NULL;

    if(root == NULL){
        p = (struct node*)malloc(sizeof(struct node));
        p->data = key;
        p->lchild = NULL;
        p->rchild = NULL;
        root = p;
        return;
    }

    while(t != NULL){
        r = t;
        if(key < t->data){
            t = t->lchild;
        }
        else if(key > t->data){
            t = t->rchild;
        }
        else return;
    }

    p = (struct node*)malloc(sizeof(struct node));
    p->data = key;
    p->lchild = NULL;
    p->rchild = NULL;

    if(key<r->data) r->lchild = p;
    else r->rchild = p;
}

void inorder(struct node* p) {
    if (p) {
        inorder(p->lchild);
        printf("%d ", p->data);
        inorder(p->rchild);
    }
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1; // Indicate error
    }

    FILE* fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("Error opening the file\n");
        return 1;
    }

    int num;
    while(fscanf(fp,"%d",&num) == 1){
        insert(num);
    }
    fclose(fp);
    
    inorder(root);
    return 0;
}