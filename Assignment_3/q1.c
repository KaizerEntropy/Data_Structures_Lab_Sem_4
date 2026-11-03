#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long compCount = 0; 
long long swapCount = 0; 

void swap(int *a, int *b) {
    swapCount++;
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition_first(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1;

    for(int j = low + 1; j <= high; j++) {
        compCount++;
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[low], &arr[i - 1]);
    return i - 1;
}
int partition_random(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(&arr[low], &arr[randomIndex]);
    return partition_first(arr, low, high);
}

int median_of_three(int a, int b, int c) {
    if ((a > b) ^ (a > c)) return a;
    if ((b > a) ^ (b > c)) return b;
    return c;
}

int find_median_index(int arr[], int low, int high) {
    int mid = (low + high) / 2;
    int a = arr[low], b = arr[mid], c = arr[high];
    int median = median_of_three(a, b, c);

    if (median == a) return low;
    if (median == b) return mid;
    return high;
}

int partition_median(int arr[], int low, int high) {
    int medianIndex = find_median_index(arr, low, high);
    swap(&arr[low], &arr[medianIndex]); // move median pivot to first
    return partition_first(arr, low, high);
}


void quicksort(int arr[], int low, int high, int mode) {
    if (low < high) {
        int p;

        if (mode == 1)
            p = partition_first(arr, low, high);
        else if (mode == 2)
            p = partition_random(arr, low, high);
        else
            p = partition_median(arr, low, high);

        quicksort(arr, low, p - 1, mode);
        quicksort(arr, p + 1, high, mode);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <inputfile>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Cannot open file %s\n", argv[1]);
        return 1;
    }

    int arr[100], n = 0;

    while (fscanf(fp, "%d", &arr[n]) == 1)
        n++;

    fclose(fp);

    int a1[100], a2[100], a3[100];

    for (int i = 0; i < n; i++) {
        a1[i] = arr[i];
        a2[i] = arr[i];
        a3[i] = arr[i];
    }

    
    compCount = swapCount = 0;
    quicksort(a1, 0, n - 1, 1);
    printf("Pivot = First Element:\n");
    printf("Comparisons: %lld\nSwaps: %lld\n", compCount, swapCount);

    compCount = swapCount = 0;
    quicksort(a2, 0, n - 1, 2);
    printf("\nPivot = Random Element:\n");
    printf("Comparisons: %lld\nSwaps: %lld\n", compCount, swapCount);

    compCount = swapCount = 0;
    quicksort(a3, 0, n - 1, 3);
    printf("\nPivot = Median-of-Three:\n");
    printf("Comparisons: %lld\nSwaps: %lld\n", compCount, swapCount);

    return 0;
}
