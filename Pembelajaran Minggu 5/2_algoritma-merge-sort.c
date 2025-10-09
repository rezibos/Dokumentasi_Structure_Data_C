#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to merge two subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    // Create temporary arrays
    int leftArr[n1], rightArr[n2];
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    // Merge the temporary arrays back into arr[]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    // Copy remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    // Copy remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Fungsi rekursif merge sort yang memakai fungsi merge untuk gabung
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        // Recursively sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Fungsi utama. Modifikasi agar membaca data file CSV.
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
    printf("Original array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    mergeSort(arr, 0, n - 1);
    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}