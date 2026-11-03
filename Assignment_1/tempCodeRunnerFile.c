#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MAX 1000

struct node {
    int data;
    struct node* next;
};

struct node* top  = NULL;
int stack[MAX];
char infix[MAX];
char postfix[MAX];


void push(int val){
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if(newnode == NULL){
        printf("Stack overflow!!\n");
        return;
    }
    newnode->data = val;
    newnode->next = top;
    top = newnode;

}

int pop(){
    struct node* p = top;
    if(top == NULL){
        printf("Stack underflow!\n");
        exit(1);
    }
    int val = top->data;
    top = top->next;
    free(p);
    return val;
}

int getTop(){
    return top->data;
}

int isEmpty(){
    if(top == NULL) return 1;
    else return 0;
}

void print(){
    struct node* p = top;
    while(p!=NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

int precedence(char symbol){
    switch(symbol){
        case '^': return 3;
        case '*': return 2;
        case '/': return 2;
        case '+': return 1;
        case '-': return 1;
        default: return 0;
    }
}

void infix_postfix(){
    int i = 0, j=0;
    char symbol;
    char next;
    for(int i=0; i<strlen(infix); i++){
        symbol = infix[i];
        switch(symbol){
            case '(':
                push(symbol);
                break;
            case ')':
                while((next = pop()) != '('){
                    postfix[j] = next;
                    j++;
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                while(isEmpty() == 0 && precedence((char)getTop()) >= precedence(symbol)){
                    postfix[j] = pop();
                    j++;
                }
                push(symbol);
                break;
            default:
                postfix[j++] = symbol;
                break;
        }
    }
    while(isEmpty() == 0){
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

void printPostfix(){
    int i=0;
    printf("The postfix expression is:\n");
    while(postfix[i] != '\0'){
        printf("%c",postfix[i]);
        i++;
    }
    printf("\n");
}

int postfix_evaluation(){
    int a, b;
    char ch;
    for(int i=0;i<strlen(postfix);i++){
        ch = postfix[i];
        if(ch>='0' && ch<='9'){
            push(ch-'0');
        }
        else{
            a = pop();
            b = pop();
            switch(ch){
                case '+':
                    push(b+a);
                    break;
                case '-':
                    push(b-a);
                    break;
                case '*':
                    push(b*a);
                    break;
                case '/':
                    push(b/a);
                    break;
                case '^':
                    push(pow(b,a));
                    break;
            }
        }
    }
    return pop();
}

int main(){
    printf("Enter the infix expression:\n");
    gets(infix);
    infix_postfix();
    printPostfix();
    int result;
    result = postfix_evaluation();
    printf("The evaluated reuslt is: %d",result);
    return 0;
}