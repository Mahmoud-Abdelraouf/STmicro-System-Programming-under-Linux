#include <stdio.h>
#include <stdlib.h>

int main() {
  int n = 5; // Number of elements
  int *arr;

  // Allocate memory for an array of integers with size 'n'
  arr = (int *)calloc(n, sizeof(int));

  if (arr == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }

  // Initialize the elements of the array
  for (int i = 0; i < n; i++) {
    arr[i] = i + 1;
  }

  // Print the elements of the array
  printf("Array elements: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // Free the allocated memory
  free(arr);

  return 0;
}
