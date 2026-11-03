#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *left, *right;
};

struct Node* createNode(int data){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int search(int inorder[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value)
            return i;
    }
    return -1;
}

struct Node* buildTree(int inorder[], int preorder[], int inStart, int inEnd, int *preIndex) {
    if (inStart > inEnd)
        return NULL;
    
    struct Node *root = createNode(preorder[*preIndex]);
    (*preIndex)++;

    if (inStart == inEnd)
        return root;

    int pos = search(inorder, inStart, inEnd, root->data);

    root->left = buildTree(inorder, preorder, inStart, pos - 1, preIndex);
    root->right = buildTree(inorder, preorder, pos + 1, inEnd, preIndex);
    return root;
}

void inorderTraversal(struct Node *root) {
   if (!root) return;
   inorderTraversal(root->left);
   printf("%d ", root->data);
   inorderTraversal(root->right);
}

void preorderTraversal(struct Node *root) {
   if (!root) return;
   printf("%d ", root->data);
   preorderTraversal(root->left);
   preorderTraversal(root->right);
}

void postorderTraversal(struct Node *root) {
   if (!root) return;
   postorderTraversal(root->left);
   postorderTraversal(root->right);
   printf("%d ", root->data);
}

int main() {
   int n;

   printf("Enter number of nodes: ");
   scanf("%d", &n);

   int inorder[n], preorder[n];

   printf("Enter inorder traversal:\n");
   for (int i = 0; i < n; i++)
       scanf("%d", &inorder[i]);

   printf("Enter preorder traversal:\n");
   for (int i = 0; i < n; i++)
       scanf("%d", &preorder[i]);

   int preIndex = 0;

   struct Node *root = buildTree(inorder, preorder, 0, n - 1, &preIndex);

   printf("\nTree Reconstructed Successfully.\n");

   printf("\nInorder traversal  : ");
   inorderTraversal(root);

   printf("\nPreorder traversal : ");
   preorderTraversal(root);

   printf("\nPostorder traversal: ");
   postorderTraversal(root);

   printf("\n");

   return 0;
}
