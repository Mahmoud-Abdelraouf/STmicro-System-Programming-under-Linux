#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binarySearch(char *arr[], char *command, int size) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(command, arr[mid]);

        if (cmp == 0) {
            return mid; /**< Found, return index */ 
        } else if (cmp < 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return -1; /**< Not found, return -1 */ 
}

