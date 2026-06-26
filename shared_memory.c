#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void sem_op(int semid, int op) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = op;
    sb.sem_flg = 0;

    if (semop(semid, &sb, 1) == -1) {
        perror("semop failed");
        exit(1);
    }
}

int main() {
    key_t key = IPC_PRIVATE;
    int shmid, semid;
    char *shm_ptr;
    pid_t pid;
    union semun argument;

    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid < 0) {
        perror("semget failed");
        exit(1);
    }

    argument.val = 0;
    semctl(semid, 0, SETVAL, argument);

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid > 0) {

        shm_ptr = (char *)shmat(shmid, NULL, 0);
        if (shm_ptr == (char *)-1) {
            perror("Parent shmat failed");
            exit(1);
        }

        printf("[Parent] Writing data to shared memory...\n");

        strncpy(shm_ptr,
                "Hello from the Parent Process! Shared memory works.",
                SHM_SIZE);

        printf("[Parent] Message written. Signaling child...\n");

        sem_op(semid, 1);

        shmdt(shm_ptr);

        wait(NULL);

        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID, argument);

        printf("[Parent] Shared memory cleaned up.\n");
    }
    else {

        shm_ptr = (char *)shmat(shmid, NULL, 0);
        if (shm_ptr == (char *)-1) {
            perror("Child shmat failed");
            exit(1);
        }

        printf("[Child] Waiting for parent...\n");

        sem_op(semid, -1);

        printf("[Child] Data read: \"%s\"\n", shm_ptr);

        shmdt(shm_ptr);

        printf("[Child] Detached and exiting.\n");

        exit(0);
    }

    return 0;
}
