#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

#define SHM_NAME "/Lab-02"
#define SEM_NAME "/Lab-02-semaphore"
#define BUFFER_SIZE (64 * 1024) 
#define ITERATIONS 10

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    int *buffer = mmap(NULL, BUFFER_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    sem_t *sem = sem_open(SEM_NAME, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    for (int i = 0; i < ITERATIONS; i++) {
        sem_wait(sem); 
        printf("\nReader: Читаю данные, итерация %d\n", i + 1);
        for (int j = 0; j < (BUFFER_SIZE / sizeof(int)); j++) {
            printf("%d ", buffer[j]);
        }
        printf("\n");
        sleep(5);
    }

    munmap(buffer, BUFFER_SIZE);
    close(shm_fd);
    sem_close(sem);
    printf("Reader: Завершение работы\n");

    return 0;
}
