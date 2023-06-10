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

/*
    process -> P1
    create shared_mem -> shmget()
    attach shared_mem to the process p1 -> shmat()
    ....... work on the memory segment .........
    wait for other process's completion
    detach shared_mem -> shmdt()
    remove shared_mem -> shmctl() 
*/

/*
    process -> P2
    get the shared mem with key created by P1 -> shmget()
    attach shared_mem to the process P2 -> shmat()
    ....... work on the memory segment .........
    signal P1 to stop waiting
    detach shared_mem -> shmdt()
*/


int max(int *arr, int size){
    srand(time(NULL));
    int max = arr[0];
    for (int i = 1; i < size; i++){
        if (arr[i] >= max){
            max = arr[i];
        }
    }
    return max;
}

int min(int *arr, int size){
    int min = arr[0];
    for (int i = 1; i < size; i++){
        if (arr[i] < min){
            min = arr[i];
        }
    }
    return min;
}

float avg(int *arr, int size){
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum += arr[i];
    }
    return ((float)sum / 100);
}

int main(){

    int *data_comm;
    float *result_comm;
    int *mutex_comm;

    pid_t pid;

    key_t seg_key1 = 1011;
    key_t seg_key2 = 1012;
    key_t seg_key3 = 1022;


    size_t seg_size = sizeof(int) * 100;

    size_t shm_id1;
    size_t shm_id2;
    size_t shm_id3;


    shm_id1 = shmget(seg_key1, seg_size, IPC_CREAT | PERMS);
    shm_id2 = shmget(seg_key2, sizeof(float) * 3, IPC_CREAT | PERMS);
    shm_id3 = shmget(seg_key3, sizeof(int), IPC_CREAT | PERMS);

    data_comm = (int *)shmat(shm_id1, NULL, 0);
    result_comm = (float *)shmat(shm_id2, NULL, 0);
    mutex_comm = (int *)shmat(shm_id3, NULL, 0);

    *mutex_comm = 0;

    pid = fork();

    if (pid == 0){
        
        while ((*mutex_comm) == 0); // lock
        
        printf("\n(At child) message from parent process ------ \n");
        for (int i = 0; i < 100; i++){
            printf("%d ", data_comm[i]);
        }

        result_comm[0] = (float)max(data_comm, 100);
        result_comm[1] = (float)min(data_comm, 100);
        result_comm[2] = (float)avg(data_comm, 100);

        printf("\nread completed \n");

        (*mutex_comm) = 0; // exec parent's code
        
        shmdt(data_comm);
        shmdt(result_comm);
        shmdt(mutex_comm);

        exit(1);

    }else{
        //  parent process
        for (int i = 0; i < 100; i++){
            data_comm[i] = (rand() % (2000 - 1 + 1)) + 1;
        }

        printf("\n(At parent) write completed \n");
    
        (*mutex_comm) = 1; // exec child's code

        while ((*mutex_comm) == 1);

        printf("\n(At parent) result from child ----- \n");
        
        printf("max: %f min: %f avg: %f \n", result_comm[0], result_comm[1], result_comm[2]);

        shmdt(data_comm);
        shmdt(result_comm);
        shmdt(mutex_comm);

        shmctl(shm_id1, IPC_RMID, NULL);
        shmctl(shm_id2, IPC_RMID, NULL);
        shmctl(shm_id3, IPC_RMID, NULL);


        wait(NULL);
    }

    return 0;
}
