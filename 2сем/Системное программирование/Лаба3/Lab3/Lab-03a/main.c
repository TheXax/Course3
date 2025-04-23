#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_search.h" 

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No function specified!\n");
        return 1;
    }

 

    char* functionName = argv[1];
    int value;
    if (argc > 2) {
        value = atoi(argv[2]);  // Преобразуем аргумент в число
    }
    else {
        printf("Enter the number to search for: ");
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid input!\n");
            return 1;
        }
    }

    int result = -1;
    if (strcmp(functionName, "binarySearchIterative") == 0) {
        result = binarySearchIterative(test_array, SIZE, value);
    }
    else if (strcmp(functionName, "binarySearchRecursive") == 0) {
        result = binarySearchRecursive(test_array, 0, SIZE - 1, value);
    }
    else {
        fprintf(stderr, "Unknown function!\n");
        return 1;
    }

    if (result == -1) {
        printf("%s: The specified number was not found!\n", functionName);
    }
    else {
        printf("%s: The number %d was found at position %d!\n", functionName, value, result);
    }

    return 0;
}
