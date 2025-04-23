#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_search.h"  // подключает test_array, binarySearchIterative, SearchRecursive

__declspec(dllimport) int binarySearchIterative(int*, int, int); 
__declspec(dllimport) int SearchRecursive(int*, int, int, int);
__declspec(dllimport) const int test_array[SIZE];
void print_usage() {
    printf("Usage: Lab03bImplicit.exe <FunctionName or Ordinal> [TargetNumber]\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("No function specified!\n");
        print_usage();
        return 1;
    }

    const char* func_name = argv[1];
    int target = 0;

    if (argc >= 3) {
        target = atoi(argv[2]);
    }
    else {
        printf("Enter the number to search: ");
        if (scanf_s("%d", &target) != 1) {
            printf("Invalid input!\n");
            return 1;
        }
    }

    int result = -1;

    // --- Проверка: вызов по ординалу(пордковому номеру) ---
    char* endptr = NULL;
    long ordinal = strtol(func_name, &endptr, 10);

    if (*endptr == '\0') {
        if (ordinal == 1) {
            result = binarySearchIterative((int*)test_array, SIZE, target);
            if (result == -1)
                printf("Ordinal %ld: Target number not found!\n", ordinal);
            else
                printf("Ordinal %ld: Number %d found at position %d!\n", ordinal, target, result);
            return 0;
        }
        else {
            printf("Ordinal %ld not supported!\n", ordinal);
            return 1;
        }
    }

    // --- Вызов по имени ---
    if (strcmp(func_name, "binarySearchIterative") == 0) {
        result = binarySearchIterative((int*)test_array, SIZE, target);
    }
    else if (strcmp(func_name, "SearchRecursive") == 0 || strcmp(func_name, "binarySearchRecursive") == 0) {
        result = SearchRecursive((int*)test_array, 0, SIZE - 1, target);
    }
    else {
        printf("Function \"%s\" not found!\n", func_name);
        return 1;
    }

    // --- Результат ---
    if (result == -1) {
        printf("%s: Target number not found!\n", func_name);
    }
    else {
        printf("%s: Number %d found at position %d!\n", func_name, target, result);
    }

    return 0;
}
