#include <stdio.h>

#define MAX 1000

void getUnion(int list1[], int n1, int list2[], int n2, int result[], int *n3){
    int i=0, j=0, k=0;
    while (i<n1 && j<n2){
        if(list1[i]==list2[j]){
            result[k++] = list1[i];
            i++;
            j++;
        }
        else if(list1[i]<list2[j]){
            result[k++] = list1[i++];
        }
        else {
            result[k++] = list2[j++];
        }
    }
    while(i<n1){
        result[k++] = list1[i++];
    }
    while(j<n2){
        result[k++] = list2[j++];
    }
    *n3 = k;
}

int main(){
    int arr1[] = {1, 2, 3, 4, 5};
    int n1 = 5;
    int arr2[] = {3, 4, 5, 6, 7, 8};
    int n2 = 6;
    int n3 = MAX;
    int res[n3];
    getUnion(arr1, n1, arr2, n2, res, &n3);
    for (int i=0;i<n3;i++){
        printf("%d ", res[i]);
    }
    printf("\n");
    return 0;
}