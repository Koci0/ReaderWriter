#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>

#include "const.h"
#include "semaphore.h"
#include "utilities.h"

int main()
{
   key_t semaphore_key;
   int semaphore_id;

   fprintf(stderr, "@ Writer %d started\n", getpid());

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

   semaphore_wait(semaphore_id, SEM_W, 0);

   write_num_to_file(FILENAME, getpid());

   semaphore_signal(semaphore_id, SEM_W);

   fprintf(stderr, "@ Writer %d finished\n", getpid());
}
