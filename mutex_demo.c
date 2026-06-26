#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

int counter = 0;
pthread_mutex_t mutex;

void *increment(void *arg) {
    pthread_mutex_lock(&mutex);

    counter++;
    printf("Thread %ld incremented counter to %d\n", (long)arg, counter);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (long i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, increment, (void *)i);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("\nFinal Counter = %d\n", counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}
