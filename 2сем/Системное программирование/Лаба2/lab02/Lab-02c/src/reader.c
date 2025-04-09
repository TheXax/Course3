#include <windows.h>
#include <stdio.h>

#define SHARED_MEMORY_NAME "Lab-02"
#define MUTEX_NAME "Lab-02-Mutex"
#define VIEW_SIZE (64 * 1024)    
#define ITERATIONS 10

void error_exit(const char *msg) {
    fprintf(stderr, "Error: %s (code: %lu)\n", msg, GetLastError());
    exit(EXIT_FAILURE);
}

int main() {
    HANDLE hMapping, hMutex;
    LPVOID pView;
    int *pData;

    hMutex = OpenMutex(SYNCHRONIZE, FALSE, MUTEX_NAME);
    if (!hMutex) error_exit("Failed to open mutex");

    hMapping = OpenFileMapping(FILE_MAP_READ, FALSE, SHARED_MEMORY_NAME);
    if (!hMapping) error_exit("Failed to open file mapping");

    pView = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, VIEW_SIZE);
    if (!pView) error_exit("Failed to map view of file");

    pData = (int *)pView; //привязка данных к области памяти

    for (int i = 0; i < ITERATIONS; i++) {
        WaitForSingleObject(hMutex, INFINITE); //ожидает, пока мьютекс не станет доступным, что предотвращает одновременный доступ к данным из нескольких потоков.

        printf("\nReader: Read iteration %d\n", i);
        for (int j = 0; j < (VIEW_SIZE / sizeof(int)); j++) {
            printf("%d ", pData[j]);
        }
        printf("\n");

        ReleaseMutex(hMutex);  //Освобождает мьютекс, позволяя другим потокам или процессам получить доступ к данным
        Sleep(5000);
    }

    printf("End\n");
    getchar(); 

    UnmapViewOfFile(pView);
    CloseHandle(hMapping);
    CloseHandle(hMutex);

    return 0;
}
