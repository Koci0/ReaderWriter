#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>

#include "const.h"
#include "semaphore.h"
#include "utilities.h"

int *pam;

int main()
{
   key_t shared_mem_key, semaphore_key;
   int shared_mem_id, semaphore_id;

   fprintf(stderr, "@ Writer %d started\n", getpid());

   shared_mem_key = ftok(".",'M');
   if (shared_mem_key == -1) {
      perror("Error: ftok (shared_mem_key");
      exit(1);
   }
   shared_mem_id = shmget(shared_mem_key, MAX_IO*sizeof(int), IPC_CREAT | 0666);
   if (shared_mem_id == -1) {
      perror("Error: shmget (shared_mem_id)");
      exit(1);
   }

   semaphore_key = ftok(".", 'S');
   if (semaphore_key == -1) {
      perror("Error: ftok (semaphore_key");
      exit(1);
   }
   semaphore_id = semget(semaphore_key, 2, IPC_CREAT | 0666);
   if (semaphore_id == -1) {
      perror("Error: semget (semaphore_id");
      exit(1);
   }

   pam = shmat(shared_mem_id, NULL, 0);
   if (pam == -1) {
      perror("Error: shmat (pam)");
      exit(1);
   }

   semaphore_wait(semaphore_id, SEM_W, 0);

   fprintf(stderr, "@ Writer %d writes at index %d\n", getpid(), WRITE_INDEX);
   pam[WRITE_INDEX] = getpid();
   WRITE_INDEX = (WRITE_INDEX + 1) % MAX_BUFFER;

   semaphore_signal(semaphore_id, SEM_W);

   shmdt(pam);

   fprintf(stderr, "@ Writer %d finished\n", getpid());
}
