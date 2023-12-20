#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

char buffer[BUFFER_SIZE];
pthread_mutex_t mutex;

void* thread_function(void* arg) {
    // Attempt to lock the mutex (note: this is not done correctly here, leading to a race condition)
    pthread_mutex_trylock(&mutex);

    // Unsafe buffer manipulation
    snprintf(buffer, BUFFER_SIZE, "Thread %d", *(int*)arg);
    sleep(1); // Sleep to increase the chance of a race condition
    printf("Buffer set by thread %d: %s\n", *(int*)arg, buffer);

    // Unlock the mutex
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int threadId1 = 1, threadId2 = 2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, NULL, thread_function, &threadId1);
    pthread_create(&thread2, NULL, thread_function, &threadId2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
