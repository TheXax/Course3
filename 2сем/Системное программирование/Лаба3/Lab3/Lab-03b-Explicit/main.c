#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef int (*BSearchIterative)(int*, int, int);
typedef int (*BSearchRecursive)(int*, int, int, int);
typedef const int* ArrayPtr;

void print_usage() {
    printf("Usage: Lab-03b-ex.exe <Library> <FunctionName or Ordinal> [TargetNumber]\n");
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        if (argc < 2) {
            printf("No library specified!\n");
        }
        else {
            printf("No function specified!\n");
        }
        print_usage();
        return 1;
    }

    const char* lib_name = argv[1];
    const char* func_name = argv[2];

    HMODULE hLib = LoadLibraryA(lib_name);
    if (!hLib) {
        printf("Library \"%s\" not found!\n", lib_name);
        return 1;
    }

    ArrayPtr test_array = (ArrayPtr)GetProcAddress(hLib, (LPCSTR)3);
    if (!test_array) {
        printf("Failed to get array from library (ordinal 3)!\n");
        FreeLibrary(hLib);
        return 1;
    }

    printf("%d %d %d\n", test_array[0], test_array[1], test_array[2]);

    int target = 0;
    if (argc >= 4) {
        target = atoi(argv[3]);
    }
    else {
        printf("Enter the number to search: ");
        if (scanf_s("%d", &target) != 1) {
            printf("Invalid input!\n");
            FreeLibrary(hLib);
            return 1;
        }
    }

    int result = -1;
    FARPROC func = NULL;

    // Try ordinal
    char* endptr = NULL;
    int ordinal = strtol(func_name, &endptr, 10);
    if (*endptr == '\0') {
        func = GetProcAddress(hLib, (LPCSTR)ordinal);
    }
    else {
        func = GetProcAddress(hLib, func_name);
    }
    if (!func && strcmp(func_name, "binarySearchRecursive") == 0) {
        func = GetProcAddress(hLib, "?binarySearchRecursive@@YAHPEAHHHH@Z");
    }

    if (!func) {
        printf("Function \"%s\" not found in library \"%s\"!\n", func_name, lib_name);
        FreeLibrary(hLib);
        return 1;
    }

    // Dispatch
    if (strcmp(func_name, "SearchIterative") == 0 || strcmp(func_name, "binarySearchIterative") == 0 || ordinal == 2) {
        BSearchIterative search = (BSearchIterative)func;
        result = search((int*)test_array, 1024, target);
    }
    else if (strcmp(func_name, "SearchRecursive") == 0 || strcmp(func_name, "binarySearchRecursive") == 0 || ordinal == 1) {
        BSearchRecursive search = (BSearchRecursive)func;
        result = search((int*)test_array, 0, 1023, target);
    }
    else {
        printf("Function \"%s\" not handled by this program.\n", func_name);
        FreeLibrary(hLib);
        return 1;
    }

    if (result == -1) {
        printf("%s: Target number not found!\n", func_name);
    }
    else {
        printf("%s: Number %d found at position %d!\n", func_name, target, result);
    }

    FreeLibrary(hLib);
    return 0;
}
