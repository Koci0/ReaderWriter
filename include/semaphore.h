
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/errno.h>
#include <sys/wait.h>

int semaphore_wait(int semaphore_id, int number, int flags);
void semaphore_signal(int semaphore_id, int number);
