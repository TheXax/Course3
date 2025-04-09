#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define FILE_NAME "testfile.txt"
#define FILE_SIZE 131072
#define VIEW_OFFSET 65536 //смещение первого отображения
#define VIEW_SIZE 200 //размер памяти отображения

void error_exit(const char* msg) {
    fprintf(stderr, "Error: %s (code: %lu)\n", msg, GetLastError());
    exit(EXIT_FAILURE);
}

int main() {
    HANDLE hFile, hMapping;
    LPVOID pView1, pView2; //указатели на области памяти

    FILE* fp = fopen(FILE_NAME, "w");
    if (!fp) error_exit("Failed to create file");
    for (int i = 0; i < FILE_SIZE; i++) {
        fputc('A' + (i % 26), fp);
    }
    fclose(fp);

    hFile = CreateFile(FILE_NAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) error_exit("Failed to open file"); //открыт ли файл

    //создание отображения файла
    hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, "Hello?");
    if (!hMapping) error_exit("Failed to create file mapping");

    printf("Enter to continue");
    getchar();

    //отображение части файла для чтения
    pView1 = MapViewOfFile(hMapping, FILE_MAP_READ, 0, VIEW_OFFSET, VIEW_SIZE);
    if (!pView1) error_exit("Failed to map view of file");

    printf("File content at offset %d:\n%.*s\n", VIEW_OFFSET, VIEW_SIZE, (char*)pView1);
    UnmapViewOfFile(pView1); //Освобождает отображение файла из памяти

    //Отображает ту же область файла в память для записи
    pView2 = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, VIEW_OFFSET, VIEW_SIZE);
    if (!pView2) error_exit("Failed to map view of file for writing");

    memset(pView2, '\0', VIEW_SIZE); //Заполняет область памяти, на которую указывает pView2, нулями. Это очищает 200 байтов в файле, начиная с указанного смещения.
    FlushViewOfFile(pView2, VIEW_SIZE);
    UnmapViewOfFile(pView2);

    CloseHandle(hMapping);
    CloseHandle(hFile);

    printf("File modified successfully. Inspect it manually.\n");
    getchar(); // Ожидание ввода перед выходом
    return 0;
}
