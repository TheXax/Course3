#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define FILE_NAME "fakefile.txt"
#define VIEW_OFFSET 0
#define VIEW_SIZE (512 * 1024 * 1024) // 512 MB

void error_exit(const char *msg) {
    fprintf(stderr, "Error: %s (code: %lu)\n", msg, GetLastError());
    exit(EXIT_FAILURE);
}

int main() {
    HANDLE hFile, hMapping;
    LPVOID pView;
    DWORD bytesWritten;


    printf("Start\n");
    printf("Enter to continue\n");
    getchar();

    hFile = CreateFile(FILE_NAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) error_exit("Failed to open file");

    printf("CreateFile\n");
    printf("Enter to continue\n");
    getchar();

    // Заполнение файла данными
    char* buffer = (char*)malloc(VIEW_SIZE);
    if (buffer == NULL) {
        error_exit("Failed to allocate memory for buffer");
    }

    // Заполнение буфера данными
    for (size_t i = 0; i < VIEW_SIZE; i++) {
        buffer[i] = 'A'; // Заполняем 'A'
    }

    // Запись данных в файл
    if (!WriteFile(hFile, buffer, VIEW_SIZE, &bytesWritten, NULL) || bytesWritten != VIEW_SIZE) {
        free(buffer);
        error_exit("Failed to write data to file");
    }

    free(buffer); // Освобождаем память для буфера

    printf("Data written to file\n");
    printf("Enter to continue\n");
    getchar();

    hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, "Hello?");
    if (!hMapping) error_exit("Failed to create file mapping");

    printf("CreateFileMapping\n");
    printf("Enter to continue\n");
    getchar();

    pView = MapViewOfFile(hMapping, FILE_MAP_READ, 0, VIEW_OFFSET, VIEW_SIZE);
    if (!pView) error_exit("Failed to map view of file");
    printf("Enter to continue\n");

    printf("Content %d:\n%.*s\n", VIEW_OFFSET, VIEW_SIZE, (char*)pView);
    printf("Enter to continue\n");
    getchar();

    UnmapViewOfFile(pView);

    CloseHandle(hMapping);
    CloseHandle(hFile);

    printf("End\n");
    printf("Enter to continue\n");
    getchar();
    
    return 0;
}
