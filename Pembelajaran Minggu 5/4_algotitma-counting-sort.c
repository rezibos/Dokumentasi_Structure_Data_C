#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void countingSort(int array[], int size) {
    int output[10000];
    int max = array[0];
    int i;
    // Find the maximum value in the array
    for (i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    // Cek apakah max melebihi batas
    if (max > 100000) {
        printf("Warning: Maximum value (%d) exceeds MAX_VALUE (%d)\n", max, 100000);
        max = 100000;
    }
    // Initialize the count array
    int count[max + 1];
    memset(count, 0, sizeof(count));
    // Count the occurrences of each element
    for (i = 0; i < size; i++) {
        count[array[i]]++;
    }
    // Update the count array to store cumulative counts
    for (i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    // Build the output array
    for (i = size - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }
    // Copy the sorted elements back to the original array
    for (i = 0; i < size; i++) {
        array[i] = output[i];
    }
}

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    int array[10000];
    int size = 0;
    
    char line[1024];
    while (fgets(line, sizeof(line), file) && size < 10000) {
        char *token = strtok(line, ",\n");
        while (token != NULL && size < 10000) {
            if (strcmp(token, "Angka") != 0) {
                array[size++] = atoi(token);
            }
            token = strtok(NULL, ",\n");
        }
    }

    fclose(file);
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    countingSort(array, size);
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}