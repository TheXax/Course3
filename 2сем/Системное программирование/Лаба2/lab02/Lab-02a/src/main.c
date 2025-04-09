#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define FILE_NAME "testfile.txt"
#define FILE_SIZE 131072
#define VIEW_OFFSET 65536 //�������� ������� �����������
#define VIEW_SIZE 200 //������ ������ �����������

void error_exit(const char* msg) {
    fprintf(stderr, "Error: %s (code: %lu)\n", msg, GetLastError());
    exit(EXIT_FAILURE);
}

int main() {
    HANDLE hFile, hMapping;
    LPVOID pView1, pView2; //��������� �� ������� ������

    FILE* fp = fopen(FILE_NAME, "w");
    if (!fp) error_exit("Failed to create file");
    for (int i = 0; i < FILE_SIZE; i++) {
        fputc('A' + (i % 26), fp);
    }
    fclose(fp);

    hFile = CreateFile(FILE_NAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) error_exit("Failed to open file"); //������ �� ����

    //�������� ����������� �����
    hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, "Hello?");
    if (!hMapping) error_exit("Failed to create file mapping");

    printf("Enter to continue");
    getchar();

    //����������� ����� ����� ��� ������
    pView1 = MapViewOfFile(hMapping, FILE_MAP_READ, 0, VIEW_OFFSET, VIEW_SIZE);
    if (!pView1) error_exit("Failed to map view of file");

    printf("File content at offset %d:\n%.*s\n", VIEW_OFFSET, VIEW_SIZE, (char*)pView1);
    UnmapViewOfFile(pView1); //����������� ����������� ����� �� ������

    //���������� �� �� ������� ����� � ������ ��� ������
    pView2 = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, VIEW_OFFSET, VIEW_SIZE);
    if (!pView2) error_exit("Failed to map view of file for writing");

    memset(pView2, '\0', VIEW_SIZE); //��������� ������� ������, �� ������� ��������� pView2, ������. ��� ������� 200 ������ � �����, ������� � ���������� ��������.
    FlushViewOfFile(pView2, VIEW_SIZE);
    UnmapViewOfFile(pView2);

    CloseHandle(hMapping);
    CloseHandle(hFile);

    printf("File modified successfully. Inspect it manually.\n");
    getchar(); // �������� ����� ����� �������
    return 0;
}
