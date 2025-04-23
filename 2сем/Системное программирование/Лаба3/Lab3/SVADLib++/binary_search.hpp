#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#define SIZE 1024

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__((visibility("default")))
#endif

extern "C"  DLL_EXPORT  const int test_array[SIZE];
extern "C"  DLL_EXPORT int binarySearchIterative(int* arr, int size, int target);

DLL_EXPORT int binarySearchRecursive(int* arr, int left, int right, int target);

#endif // BINARY_SEARCH_H