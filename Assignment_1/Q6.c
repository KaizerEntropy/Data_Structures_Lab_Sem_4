#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX 100

struct node {
    char* data;
    struct node* next;
};

struct node* top  = NULL;

char infix[MAX];
char postfix[MAX];

void push(char *val){
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if(newnode == NULL){
        printf("Stack overflow!!\n");
        return;
    }
    int string_len = strlen(val);
    char* string = (char*)malloc(sizeof(char)*string_len+1);
    strcpy(string,val);

    newnode->data = string;
    newnode->next = top;
    top = newnode;
}

char* pop(){
    struct node* p = top;
    if(top == NULL){
        printf("Stack underflow!!\n");
        exit(1);
    }
    char* val = top->data;
    top = top->next;
    free(p);
    return val;
}

char* getTop(){
    return top->data;
}

int isEmpty(){
    if(top == NULL) return 1;
    else return 0;
}

void print(){
    struct node* p = top;
    while(p!=NULL){
        printf("%s ",p->data);
        p = p->next;
    }
    printf("\n");
}

char* postfix_infix(){
    char *a, *b;
    char ch;
    for(int i=0;i<strlen(postfix);i++){
        ch = postfix[i];
        if(ch-'0'>=0 && ch-'9'<=9){
            char temp[2];
            temp[0] = ch;
            temp[1] = '\0';
            push(temp);
        }
        else{
            a = pop();
            b = pop();
            char res[MAX];
            strcpy(res,"(");
            strcat(res,b);
            char buffer[2];
            buffer[1] = '\0';
            switch(ch){
                case '+':
                    buffer[0] = '+';
                    break;
                case '-':
                    buffer[0] = '-';
                    break;
                case '*':
                    buffer[0] = '*';
                    break;
                case '/':
                    buffer[0] = '/';
                    break;
                case '^':
                    buffer[0] = '^';
                    break;
            }
            strcat(res,buffer);
            strcat(res,a);
            strcat(res,")");
            push(res);
            free(a);
            free(b);
        }
    }
    printf("%s",pop());
}

int main(){
    printf("Enter the postfix expression:\n");
    fgets(postfix, MAX, stdin);
    size_t len = strlen(postfix);
    if (len > 0 && postfix[len-1] == '\n') {
        postfix[len-1] = '\0';
    }
    printf("The infix expression is:\n");
    postfix_infix();
    printf("\n");
    return 0;
}
