#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>

/*
    parent is producer
    child is consumer 
    buffer size 20
    after 20 production & consumption exit
*/

#define EMPTY_IDX 0
#define FULL_IDX 1
#define MUTEX_IDX 2
#define BUFF_SIZE 20

void sem_wait(int *sem) {
    while ((*sem) <= 0);
    (*sem)--;
}

void sem_signal(int *sem) {
    (*sem)++;
}

int main(){

    int shm_id1;
    int shm_id2;
    int shm_id3;

    
    int *buffer, *semaphores, *idx_counter;
    
    key_t sema_key = 1011;
    key_t buff_key = 1022;
    key_t shared_counter = 1024;


    shm_id1 = shmget(sema_key, sizeof(int) * 3, IPC_CREAT | 0666);
    shm_id2 = shmget(buff_key, sizeof(int) * BUFF_SIZE, IPC_CREAT | 0666);
    shm_id3 = shmget(shared_counter, sizeof(int), IPC_CREAT | 0666);

    semaphores = (int *)shmat(shm_id1, NULL, 0);
    buffer = (int *)shmat(shm_id2, NULL, 0);
    idx_counter = (int *)shmat(shm_id3, NULL, 0);
    
    semaphores[0] = BUFF_SIZE; // empty semaphore = 20
    semaphores[1] = 0; // FULL semaphore == 0
    semaphores[2] = 1; // mutex semaphore == 1
    
    *idx_counter = 0;  // idx_counter shared

    pid_t pid = fork();

    if (pid == 0){
        // consumer
        while (1) {

            sleep(1);
            sem_wait(&semaphores[FULL_IDX]); // 0
            sem_wait(&semaphores[MUTEX_IDX]); // 0

            int item = buffer[(*idx_counter) - 1];  // LIFO pop
            (*idx_counter)--;

            printf("Consumer consumed item %d\n", item);
            fflush(stdout);

            sem_signal(&semaphores[MUTEX_IDX]); // 1
            sem_signal(&semaphores[EMPTY_IDX]); // 20
            // sleep(2);
        }

        shmdt(semaphores);
        shmdt(buffer);
        exit(0);

    }

    // producer

    while (1) {
        
        int item = rand() % 100;
        
        sleep(1);
        sem_wait(&semaphores[EMPTY_IDX]); 
        sem_wait(&semaphores[MUTEX_IDX]); 

        buffer[*idx_counter] = item; // critial  LIFO Push

        printf("Producer produced item %d\n", buffer[*idx_counter]);
        fflush(stdout);
        
        (*idx_counter)++;

        sem_signal(&semaphores[MUTEX_IDX]); 
        sem_signal(&semaphores[FULL_IDX]);  // 1

    }

    // waitpid(pid, NULL, 0);
    wait(NULL);

    shmdt(semaphores);
    shmdt(buffer);

    shmctl(shm_id1, IPC_RMID, NULL);
    shmctl(shm_id2, IPC_RMID, NULL);

    return 0;

}
