
#include "semaphore.h"

int semaphore_wait(int semaphore_id, int number, int flags) {
    struct sembuf tmp[1];
    tmp[0].sem_num = number;
    tmp[0].sem_op = -1;
    tmp[0].sem_flg = 0 | flags;

    if (semop(semaphore_id, tmp, 1) == -1) {
        perror("Error: semop (semaphore_wait)");
        return -1;
    }

    return 1;
}

void semaphore_signal(int semaphore_id, int number) {
    struct sembuf tmp[1];
    tmp[0].sem_num = number;
    tmp[0].sem_op = 1;

    if (semop(semaphore_id, tmp, 1) == -1) {
        perror("Error: semop (semaphore_signal)");
    }
}
