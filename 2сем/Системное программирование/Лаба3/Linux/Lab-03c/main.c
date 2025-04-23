#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

typedef int (*BSearchIterative)(int*, int, int);
typedef int (*BSearchRecursive)(int*, int, int, int);

extern const int test_array[]; // опционально

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("No library specified!\n");
        return 1;
    }
    if (argc < 3) {
        printf("No function specified!\n");
        return 1;
    }

    const char* lib_name = argv[1];
    const char* func_name = argv[2];

    void* handle = dlopen(lib_name, RTLD_LAZY);
    if (!handle) {
        printf("Library not found!\n");
        return 1;
    }

    int* array = (int*)dlsym(handle, "test_array");
    if (!array) {
        printf("Failed to get array from library!\n");
        dlclose(handle);
        return 1;
    }

    void* symbol = dlsym(handle, func_name);
    if (!symbol) {
        printf("Function \"%s\" not found in library \"%s\"!\n", func_name, lib_name);
        dlclose(handle);
        return 1;
    }

    int target = 0;
    if (argc >= 4) {
        target = atoi(argv[3]);
    } else {
        printf("Enter the number to search: ");
        if (scanf("%d", &target) != 1) {
            printf("Invalid input!\n");
            dlclose(handle);
            return 1;
        }
    }

    int result = -1;
    if (strcmp(func_name, "binarySearchIterative") == 0) {
        BSearchIterative func = (BSearchIterative)symbol;
        result = func(array, 1024, target);
    } else if (strcmp(func_name, "binarySearchRecursive") == 0) {
        BSearchRecursive func = (BSearchRecursive)symbol;
        result = func(array, 0, 1023, target);
    } else {
        printf("Unknown function: %s\n", func_name);
        dlclose(handle);
        return 1;
    }

    if (result == -1) {
        printf("%s: Target number not found!\n", func_name);
    } else {
        printf("%s: Number %d found at position %d!\n", func_name, target, result);
    }

    dlclose(handle);
    return 0;
}
