#include <windows.h>
#include <stdio.h>

#define SHARED_MEMORY_NAME "Lab-02"
#define MUTEX_NAME "Lab-02-Mutex"
#define TOTAL_SIZE (640 * 1024)  
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

    hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
    if (!hMutex) error_exit("Failed to create mutex");

    hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TOTAL_SIZE, SHARED_MEMORY_NAME);
    if (!hMapping) error_exit("Failed to create file mapping");

    pView = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, VIEW_SIZE);
    if (!pView) error_exit("Failed to map view of file");

    pData = (int *)pView;

    for (int i = 0; i < ITERATIONS; i++) {
        WaitForSingleObject(hMutex, INFINITE);  

        for (int j = 0; j < (VIEW_SIZE / sizeof(int)); j++) {
            pData[j] = i * 1000 + j;  

            if (i == 5 && j == 1000) {
                printf("Hello\n");
                getchar();
            }
        }

        printf("Writer: Wrote iteration %d\n", i);
        ReleaseMutex(hMutex);  

        Sleep(5000);
    }

    printf("End\n");
    getchar();  

    UnmapViewOfFile(pView);
    CloseHandle(hMapping);
    CloseHandle(hMutex);

    return 0;
}
