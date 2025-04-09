#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FILE_NAME "testfile.txt"
#define FILE_SIZE 8192
#define OFFSET 4096 

void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    long page_size = sysconf(_SC_PAGE_SIZE); 

    if (page_size != -1) {
        printf("Page size: %ld bytes\n", page_size);
    } else {
        perror("sysconf");
    }

    int fd;
    void *mapped;
    
    fd = open(FILE_NAME, O_RDWR | O_CREAT, 0666); //0600 - приватный доступ
    if (fd == -1) error_exit("Failed to open file");

    if (ftruncate(fd, FILE_SIZE) == -1) error_exit("Failed to set file size");

    mapped = mmap(NULL, FILE_SIZE - OFFSET, PROT_READ | PROT_WRITE, MAP_SHARED, fd, OFFSET);
    if (mapped == MAP_FAILED) error_exit("Failed to map file");

    printf("Original content: %.*s\n", FILE_SIZE - OFFSET, (char *)mapped);

    strcpy((char *)mapped, "Hello, mmap!");

    if (msync(mapped, FILE_SIZE - OFFSET, MS_SYNC) == -1) {
        error_exit("Failed to sync file");
    }

    printf("Enter to continue");
    getchar();

    if (munmap(mapped, FILE_SIZE - OFFSET) == -1) error_exit("Failed to unmap memory");
    close(fd);

    printf("Modification complete. Check %s manually.\n", FILE_NAME);

    return 0;
}
