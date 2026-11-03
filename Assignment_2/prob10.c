#include<stdio.h>
#include<stdlib.h>

struct node{
    struct node* lchild;
    int data;
    int height;
    struct node* rchild;
};
struct node* root = NULL;

int nodeHeight(struct node* p){
    int hl,hr;
    if(p && p->lchild) hl = p->lchild->height;
    else hl = 0;

    if(p && p->rchild) hr = p->rchild->height;
    else hr = 0;

    return (hl > hr ? hl : hr) + 1;
}

int balanceFactor(struct node* p){
    int hl = (p && p->lchild) ? p->lchild->height : 0;
    int hr = (p && p->rchild) ? p->rchild->height : 0;
    return hl - hr;
}

struct node* rotationLL(struct node* p){
    struct node* pl = p->lchild;
    struct node* plr = pl->rchild;

    pl->rchild = p;
    p->lchild = plr;

    p->height = nodeHeight(p);
    pl->height = nodeHeight(pl);

    if(root == p) root = pl;
    return pl;
}

struct node* rotationRR(struct node* p){
    struct node* pr = p->rchild;
    struct node* prl = pr->lchild;

    pr->lchild = p;
    p->rchild = prl;

    p->height = nodeHeight(p);
    pr->height = nodeHeight(pr);

    if(root == p) root = pr;
    return pr;
}

struct node* rotationLR(struct node* p){
    struct node* pl = p->lchild;
    struct node* plr = pl->rchild;

    pl->rchild = plr->lchild;
    p->lchild = plr->rchild;

    plr->lchild = pl;
    plr->rchild = p;

    p->height = nodeHeight(p);
    pl->height = nodeHeight(pl);
    plr->height = nodeHeight(plr);

    if(root == p) root = plr;
    return plr;
}

struct node* rotationRL(struct node* p){
    struct node* pr = p->rchild;
    struct node* prl = pr->lchild;

    p->rchild = prl->lchild;
    pr->lchild = prl->rchild;

    prl->lchild = p;
    prl->rchild = pr;

    p->height = nodeHeight(p);
    pr->height = nodeHeight(pr);
    prl->height = nodeHeight(prl);

    if(root == p) root = prl;
    return prl;
}

struct node* insert(struct node* p, int key){
    struct node* temp;
    if(p == NULL){
        temp = (struct node*)malloc(sizeof(struct node));
        temp->data = key;
        temp->lchild = temp->rchild = NULL;
        temp->height = 1;
        return temp;
    }

    if(key < p->data) p->lchild = insert(p->lchild,key);
    else if(key > p->data) p->rchild = insert(p->rchild,key);

    p->height = nodeHeight(p);

    int bf = balanceFactor(p);

    if(bf == 2 && balanceFactor(p->lchild) == 1) return rotationLL(p);
    if(bf == 2 && balanceFactor(p->lchild) == -1) return rotationLR(p);
    if(bf == -2 && balanceFactor(p->rchild) == -1) return rotationRR(p);
    if(bf == -2 && balanceFactor(p->rchild) == 1) return rotationRL(p);

    return p;
}

struct node* minValueNode(struct node* p){
    while(p->lchild != NULL)
        p = p->lchild;
    return p;
}

struct node* deleteNode(struct node* p, int key){
    if(p == NULL) return NULL;

    if(key < p->data)
        p->lchild = deleteNode(p->lchild, key);

    else if(key > p->data)
        p->rchild = deleteNode(p->rchild, key);

    else {
        if(p->lchild == NULL || p->rchild == NULL){
            struct node* temp = p->lchild ? p->lchild : p->rchild;

            if(temp == NULL){
                temp = p;
                p = NULL;
            }
            else {
                *p = *temp;
            }
            free(temp);
        }
        else {
            struct node* temp = minValueNode(p->rchild);
            p->data = temp->data;
            p->rchild = deleteNode(p->rchild, temp->data);
        }
    }

    if(p == NULL) return p;

    p->height = nodeHeight(p);

    int bf = balanceFactor(p);

    if(bf == 2 && balanceFactor(p->lchild) >= 0) return rotationLL(p);
    if(bf == 2 && balanceFactor(p->lchild) < 0)  return rotationLR(p);

    if(bf == -2 && balanceFactor(p->rchild) <= 0) return rotationRR(p);
    if(bf == -2 && balanceFactor(p->rchild) > 0)  return rotationRL(p);

    return p;
}

void inorder(struct node* root){
    if(root){
        inorder(root->lchild);
        printf("%d ", root->data);
        inorder(root->rchild);
    }
}

int main(int argc, char* argv[]){

    FILE* fp = fopen(argv[1], "r");
    int num;

    while(fscanf(fp, "%d", &num) != EOF)
        root = insert(root, num);

    fclose(fp);

    printf("Before deletion: \n");
     printf("The value of the tree inorder: ");
    inorder(root);
    printf("\n");

    int delKey;
    printf("Enter value to delete: ");
    scanf("%d", &delKey);

    root = deleteNode(root, delKey);

    printf("After deletion: \n");
    printf("The value of the tree inorder: ");
    inorder(root);
    printf("\n");

    return 0;
}
