#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#define SIZE 1024  // Ðàçìåð ìàññèâà
extern const int test_array[SIZE];

int binarySearchIterative(int *arr, int size, int target);
int binarySearchRecursive(int *arr, int left, int right, int target);


#endif // BINARY_SEARCH_H
