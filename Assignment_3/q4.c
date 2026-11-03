#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10

typedef struct node {
    int key;
    struct node *next;
} Node;

Node *chain[TABLE_SIZE]; 

void insert_chaining(int key) {
    int index = key % TABLE_SIZE;
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = chain[index];
    chain[index] = newNode;
}

void display_chaining() {
    printf("\nSeparate Chaining:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d --> ", i);
        Node *temp = chain[i];
        while (temp) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int linear[TABLE_SIZE];

void insert_linear(int key) {
    int index = key % TABLE_SIZE;
    int i = 0;

    while (linear[(index + i) % TABLE_SIZE] != -1)
        i++;

    linear[(index + i) % TABLE_SIZE] = key;
}

void display_linear() {
    printf("\nLinear Probing:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
        printf("%d : %d\n", i, linear[i]);
}

int quadratic[TABLE_SIZE];

void insert_quadratic(int key) {
    int index = key % TABLE_SIZE;
    int i = 0;

    while(quadratic[(index + i*i) % TABLE_SIZE] != -1)
        i++;

    quadratic[(index + i*i) % TABLE_SIZE] = key;
}

void display_quadratic() {
    printf("\nQuadratic Probing:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
        printf("%d : %d\n", i, quadratic[i]);
}

int dbl[TABLE_SIZE];

int h2(int x) {
    return 7 - (x % 7);
}

void insert_double(int key) {
    int index = key % TABLE_SIZE;
    int step = h2(key);
    int i = 0;

    while (dbl[(index + i * step) % TABLE_SIZE] != -1)
        i++;

    dbl[(index + i * step) % TABLE_SIZE] = key;
}

void display_double() {
    printf("\nDouble Hashing:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
        printf("%d : %d\n", i, dbl[i]);
}


int main(int argc, char *argv[]) {
    
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    int keys[100], n = 0;
    while (fscanf(fp, "%d", &keys[n]) != EOF)
        n++;
    fclose(fp);

    for (int i = 0; i < TABLE_SIZE; i++) {
        chain[i] = NULL;
        linear[i] = -1;
        quadratic[i] = -1;
        dbl[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        insert_chaining(keys[i]);
        insert_linear(keys[i]);
        insert_quadratic(keys[i]);
        insert_double(keys[i]);
    }

    display_chaining();
    display_linear();
    display_quadratic();
    display_double();

    return 0;
}
