#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a>b)?a:b;
}

int min(int a, int b) {
    return (a<b)?a:b;
}

int *addPolynomial(int poly1[], int poly2[], int n1, int n2){
    int size = max(n1, n2);
    int *result = malloc(size*sizeof(int));
    if (result == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        int coeff1 = (i < n1)?poly1[i]:0;
        int coeff2 = (i < n2) ? poly2[i]:0;
        result[i] = coeff1+coeff2;
    }
    return result;
}


int main() {
    int poly1[] = {1, 0, 0, 3, 6};
    int n1 = 5;

    int poly2[] = {0, 2, 0, 4, 3, 1};
    int n2 = 6;

    int size = max(n1, n2);
    int *res = addPolynomial(poly1, poly2, n1, n2);

    for (int i=0; i<size; i++)
        printf("%d ", res[i]);

    printf("\n");

    free(res);
    return 0;
}
