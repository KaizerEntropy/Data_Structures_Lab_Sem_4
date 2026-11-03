#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right, *parent;
} Node;

Node* newNode(int val) {
    Node* n = (Node *)malloc(sizeof(Node));
    n->data = val;
    n->left = n->right = n->parent = NULL;
    return n;
}

typedef struct QueueNode {
    Node* tnode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

void enqueue(Queue* q, Node* t) {
    if (!t) return;
    QueueNode* temp = (QueueNode* )malloc(sizeof(QueueNode));
    temp->tnode = t;
    temp->next = NULL;
    if (!q->rear) q->front = q->rear = temp;
    else q->rear->next = temp, q->rear = temp;
}

Node* dequeue(Queue* q) {
    if (!q->front) return NULL;
    QueueNode* temp = q->front;
    Node* t = temp->tnode;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return t;
}

int empty(Queue* q) {
    return q->front == NULL;
}

void printLevelOrder(Node* root) {
    if (!root) return;
    Queue q = {0};
    enqueue(&q, root);
    printf("Heap (Level Order) traveral is as follows: ");
    while (!empty(&q)) {
        Node* t = dequeue(&q);
        printf("%d ", t->data);
        enqueue(&q, t->left);
        enqueue(&q, t->right);
    }
    printf("\n");
}

void heapify_up(Node* node) {
    while (node->parent && node->parent->data < node->data) {
        int t = node->data;
        node->data = node->parent->data;
        node->parent->data = t;
        node = node->parent;
    }
}

Node* insert(Node* root, int val) {
    Node* n = newNode(val);
    if (!root) return n;

    Queue q = {0};
    enqueue(&q, root);

    while (!empty(&q)) {
        Node* temp = dequeue(&q);

        if (!temp->left) {
            temp->left = n;
            n->parent = temp;
            heapify_up(n);
            return root;
        } else enqueue(&q, temp->left);

        if (!temp->right) {
            temp->right = n;
            n->parent = temp;
            heapify_up(n);
            return root;
        } else enqueue(&q, temp->right);
    }
    return root;
}

void heapify_down(Node* root) {
    while (root) {
        Node* largest = root;
        if (root->left && root->left->data > largest->data)
            largest = root->left;
        if (root->right && root->right->data > largest->data)
            largest = root->right;

        if (largest == root) break;

        int t = root->data;
        root->data = largest->data;
        largest->data = t;

        root = largest;
    }
}

Node* deleteMax(Node* root) {
    if (!root) return NULL;

    Queue q = {0};
    enqueue(&q, root);

    Node* last = NULL;
    while (!empty(&q)) {
        last = dequeue(&q);
        enqueue(&q, last->left);
        enqueue(&q, last->right);
    }

    if (last == root) {
        free(root);
        return NULL;
    }

    root->data = last->data;

    if (last->parent->left == last)
        last->parent->left = NULL;
    else
        last->parent->right = NULL;

    free(last);
    heapify_down(root);

    return root;
}

int main() {
    Node* root = NULL;

    printf("Inserting: 13\n");
    root = insert(root, 13);
    printLevelOrder(root);

    printf("Inserting: 27\n");
    root = insert(root, 27);
    printLevelOrder(root);

    printf("Inserting: 18\n");
    root = insert(root, 18);
    printLevelOrder(root);

    printf("Inserting: 17\n");
    root = insert(root, 17);
    printLevelOrder(root);

    printf("Inserting: 15\n");
    root = insert(root, 65);
    printLevelOrder(root);

    printf("Inserting: 2\n");
    root = insert(root, 2);
    printLevelOrder(root);
    
    printf("Inserting: 24\n");
    root = insert(root, 24);
    printLevelOrder(root);

    printf("Deleted the max element!\n");
    root = deleteMax(root);
    printLevelOrder(root);

    return 0;
}

