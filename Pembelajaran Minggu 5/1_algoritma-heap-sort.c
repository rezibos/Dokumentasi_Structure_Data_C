#include <stdio.h>
#include <stdlib.h>

/// Recursive function heapify. Pahami cara kerjanya
void heapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child
    // Check if left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;
    // Check if right child is larger than the largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;
    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

// Fungsi heap sort dimana menggunakan fungsi rekursif heapify
void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Tampilkan isi data
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* readCSV(const char *filename, int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        *count = 0;
        return NULL;
    }
    
    char line[256];
    fgets(line, sizeof(line), file);
    
    int capacity = 10;
    int *arr = (int *)malloc(capacity * sizeof(int));
    if (arr == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        *count = 0;
        return NULL;
    }
    
    int n = 0;
    int num;
    
    while (fscanf(file, "%d,", &num) == 1 || fscanf(file, "%d", &num) == 1) {
        if (n >= capacity) {
            capacity *= 2;
            int *temp = (int *)realloc(arr, capacity * sizeof(int));
            if (temp == NULL) {
                printf("Error: Memory reallocation failed\n");
                free(arr);
                fclose(file);
                *count = 0;
                return NULL;
            }
            arr = temp;
        }
        arr[n] = num;
        n++;
    }
    
    fclose(file);
    *count = n;
    return arr;
}

// Program utama. Modifikasi untuk dapat menerima dan membaca data file 
int main(int argc, char *argv[]) {
    int n;
    int *arr = readCSV(argv[1], &n);
    
    printf("Original Array: ");
    printArray(arr, n);
    heapSort(arr, n);
    printf("Sorted Array: ");
    printArray(arr, n);
    free(arr);
    return 0;
}