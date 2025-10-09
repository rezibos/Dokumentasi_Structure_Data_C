#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RUN 32

// Function to perform insertion sort
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Function to merge two sorted subarrays
void merge(int arr[], int left, int mid, int right) {
    int len1 = mid - left + 1, len2 = right - mid;
    int leftArr[len1], rightArr[len2];  // Array statis (VLA)
    
    for (int i = 0; i < len1; i++) leftArr[i] = arr[left + i];
    for (int i = 0; i < len2; i++) rightArr[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < len1)
        arr[k++] = leftArr[i++];
    while (j < len2)
        arr[k++] = rightArr[j++];
}

// Function to perform TimSort
void timSort(int arr[], int n) {
    for (int i = 0; i < n; i += RUN) {
        int right = (i + RUN - 1 < n - 1) ? i + RUN - 1 : n - 1;
        insertionSort(arr, i, right);
    }
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = ((left + 2 * size - 1) < (n - 1)) ? (left + 2 * size - 1) : (n - 1);
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

// Main function. Modify here to read data from CSV file.
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function dengan array statis
int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    
    char line[256];
    fgets(line, sizeof(line), file);
    int arr[10000];
    int n = 0;
    
    while (fgets(line, sizeof(line), file) && n < 10000) {
        char *token = strtok(line, ",\n");
        while (token != NULL && n < 10000) {
            arr[n] = atoi(token);
            n++;
            token = strtok(NULL, ",\n");
        }
    }
    
    fclose(file);
    printf("Original Array: ");
    printArray(arr, n);
    timSort(arr, n);
    printf("Sorted Array: ");
    printArray(arr, n);
    return 0;
}