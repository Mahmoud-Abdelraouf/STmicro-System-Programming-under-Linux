/**
 * @file heap_sort.h
 * @brief Header file for Heap Sort functions on an array of strings.
 */

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

/**
 * @brief Rearranges a subarray to satisfy the max heap property.
 *
 * This function is used in the heap sort algorithm to maintain the heap property.
 *
 * @param arr An array of strings.
 * @param n Size of the array.
 * @param i Index of the current root of the subarray.
 */
void heapify(char *arr[], int n, int i);

/**
 * @brief Sorts an array of strings using the Heap Sort algorithm.
 *
 * @param arr An array of strings.
 * @param n Size of the array.
 */
void heapSort(char *arr[], int n);

/**
 * @brief Prints the elements of an array of strings.
 *
 * @param arr An array of strings.
 * @param size Size of the array.
 */
void printArray(char *arr[], int size);

#endif /* HEAP_SORT_H */

