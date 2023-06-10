#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>

#define PERMS 0666 


void sem_wait(int *sem){
    while ((*sem) <= 0);
    (*sem)--;
}

void sem_signal(int *sem){
    (*sem)++;
}

int main(){

    srand(time(NULL));
    int shm_id1;
    int shm_id2;
    
    int *semaphores, *shared;

    int sema_key = 1011;
    int shared_var = 1012;

    shm_id1 = shmget(sema_key, sizeof(int) * 2, IPC_CREAT | 0666);
    shm_id2 = shmget(shared_var, sizeof(int) * 2, IPC_CREAT | 0666);

    semaphores = (int *)shmat(shm_id1, NULL, 0);
    shared = (int *)shmat(shm_id2, NULL, 0);

    semaphores[0] = 1; // mutex semphore
    semaphores[1] = 1; // write-lock semaphore
    
    shared[0] = 0; // read-count
    shared[1] = 0; // content holder (container)

    int pid = fork();

    if (pid == 0){
        // reader
        while (1) {
            sem_wait(&semaphores[0]); // lock
            shared[0] ++;
            if (shared[0] == 1){
                sem_wait(&semaphores[1]); // lock write when first reader arrives
            }
            sem_signal(&semaphores[0]); // unlock
            
            printf("Reader read: %d\n", shared[1]);
            fflush(stdout);
            
            sem_wait(&semaphores[0]); // lock
            shared[0] --;
            if (shared[0] == 0){
                sem_signal(&semaphores[1]); // unlock write when last reader leaves
            }
            sem_signal(&semaphores[0]); // unlock
            sleep(1); // simulate read delay
        }

        shmdt(semaphores);
        shmdt(shared);
        
        exit(0);

    }
    // writer 
    while (1) {
        sem_wait(&semaphores[1]);
        
        shared[1] = rand() % 100; // write into shared buffer

        printf("Writer wrote: %d\n", shared[1]);
        fflush(stdout);
        
        sem_signal(&semaphores[1]);
        sleep(4); // simulate write delay
    }

    return 0;
}
