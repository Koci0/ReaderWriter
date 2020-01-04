
#define _GNU_SOURCE // intellisense error with sigaction

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>

#include <signal.h>

#include "const.h"

void clean(int signal);

int main()
{
    struct sigaction action;
    action.sa_handler = clean;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, 0);

    key_t shared_mem_key, semaphore_key;
    int shared_mem_id;
    int semaphore_id;

    int i;

    fprintf(stderr, "  MAIN: Started\n");

    shared_mem_key = ftok(".",'M');
    if (shared_mem_key == -1) {
        perror("Error: ftok (shared_mem_key");
        exit('B');
    }
    shared_mem_id = shmget(shared_mem_key, MAX_IO*sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
        if (shared_mem_id == -1) {
        perror("Error: shmget (shared_mem_id)");
        exit('B');
    }

    semaphore_key = ftok(".", 'S');
    if (semaphore_key == -1) {
        perror("Error: ftok (semaphore_key");
        exit('C');
    }
    semaphore_id = semget(semaphore_key, 2, IPC_CREAT | IPC_EXCL | 0666);
    if (semaphore_id == -1) {
        perror("Error: semget (semaphore_id");
        exit(1);
    }

    if (semctl(semaphore_id, SEM_SP, SETVAL, 1) == -1) {
        perror("Error: semctl (semaphore)");
        exit(1);
    }
    if (semctl(semaphore_id, SEM_W, SETVAL, 1) == -1) {
        perror("Error: semctl (semaphore)");
        exit(1);
    }
        
    for (i=0; i<N_PROCESSES; i++) {
        switch (fork()) {
            case -1:
                perror("Error: fork (mainprog, reader)\n");
                exit(2);
            case 0:
                execl("./build/reader","reader",NULL);
            }

        switch (fork()) {
            case -1:
                perror("Error: fork (mainprog, writer)");
                exit(2);
            case 0:
                execl("./build/writer","writer", NULL);
        }
    }

    for (i=0; i < 2 * N_PROCESSES; i++) {
        wait(NULL);
    }

    //zwalnianie zasobow
    shmctl(shared_mem_id, IPC_RMID, NULL);
    semctl(semaphore_id, 2, IPC_RMID);
    fprintf(stderr, "  MAIN: Finished\n");
}

void clean(int signal)
{
    key_t shared_mem_key = ftok( ".",'M' );
    key_t semaphore_key = ftok( ".",'S' );
    int shared_mem_id = shmget(shared_mem_key, MAX_IO*sizeof(int), IPC_CREAT | 0666);
    int semaphore_id = semget(semaphore_key, 2, IPC_CREAT | 0666);

    shmctl(shared_mem_id,IPC_RMID, NULL);
    semctl(semaphore_id, 2, IPC_RMID, NULL);
    fprintf(stderr, "! MAIN - got signal%d: END.\n",signal);
    exit(1);
}
 
