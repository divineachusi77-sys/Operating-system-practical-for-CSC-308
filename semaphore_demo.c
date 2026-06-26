#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREADS 5

int counter = 0;
sem_t semaphore;

void *increment(void *arg)
{
    sem_wait(&semaphore);

    counter++;
    printf("Thread %ld incremented counter to %d\n", (long)arg, counter);

    sem_post(&semaphore);

    return NULL;
}

int main()
{
    pthread_t threads[THREADS];

    sem_init(&semaphore, 0, 1);

    for(long i = 0; i < THREADS; i++)
    {
        pthread_create(&threads[i], NULL, increment, (void *)i);
    }

    for(int i = 0; i < THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("\nFinal Counter = %d\n", counter);

    sem_destroy(&semaphore);

    return 0;
}
