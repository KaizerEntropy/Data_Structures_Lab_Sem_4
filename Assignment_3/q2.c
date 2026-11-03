#include <stdio.h>
#include <stdlib.h>

long long swapcnt = 0;

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    swapcnt++;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2*i +1;
    int right = 2*i +2; 
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Cannot open file %s!\n", argv[1]);
        return 1;
    }
    int arr[100], n = 0;
    while(fscanf(fp, "%d", &arr[n]) == 1)
        n++;
    fclose(fp);

    swapcnt = 0;
    heapSort(arr, n);
    printf("Sorted output is as follows:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\nTotal swap operations = %lld\n", swapcnt);

    return 0;
}
