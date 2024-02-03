#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap_sort.h"

void heapify(char *arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && strcmp(arr[left], arr[largest]) > 0) {
	    largest = left;
    }

    if (right < n && strcmp(arr[right], arr[largest]) > 0) {
	    largest = right;
    }

    if (largest != i) {
        /**< Swap arr[i] and arr[largest] */ 
        char *temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        /**< Recursively heapify the affected sub-tree */ 
        heapify(arr, n, largest);
    }
}

void heapSort(char *arr[], int n) {
    // Build the heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Swap the root (maximum element) with the last element
        char *temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void printArray(char *arr[], int size) {
    for (int i = 0; i < size; ++i)
        printf("%s ", arr[i]);
    printf("\n");
}
