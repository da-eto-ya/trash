#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int cond_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static const int MX = 3;

void *producer(void *arg) {
    unsigned int *p = (unsigned int *) arg;

    sleep(*p);
    pthread_mutex_lock(&mutex);
    printf("[producer] locked\n");
    ++cond_count;
    printf("[producer] inc: %d\n", cond_count);
    sleep(*p);

    if (cond_count >= MX) {
        pthread_cond_signal(&cond);
    }

    pthread_mutex_unlock(&mutex);
    printf("[producer] unlocked\n");

    return NULL;
}

void *consumer(void *arg) {
    unsigned int *p = (unsigned int *) arg;

    sleep(*p);

    pthread_mutex_lock(&mutex);
    printf("[consumer] locked\n");

    while (cond_count < MX) {
        pthread_cond_wait(&cond, &mutex);
    }

    cond_count = 0;
    printf("[consumer] dec: %d\n", cond_count);
    sleep(*p);

    pthread_mutex_unlock(&mutex);
    printf("[consumer] unlocked\n");

    return NULL;
}

pthread_barrier_t barrier;

void *barrier_worker(void *arg) {
    unsigned int *p = (unsigned int *) arg;

    printf("[barrier_worker] start\n");
    sleep(*p);
    printf("[barrier_worker] wait\n");

    if (pthread_barrier_wait(&barrier) == PTHREAD_BARRIER_SERIAL_THREAD) {
        printf("[barrier_worker] serial\n");
    } else {
        printf("[barrier_worker] return\n");
    }

    return NULL;
}

int main(int argc, char **argv) {
    if (argc == 2) {
        FILE *f = fopen(argv[1], "w");
        fprintf(f, "%d\n", (int) getpid());
        printf("PID: %d\n\n", (int) getpid());
        fclose(f);
    }

    static const int N = 10;

    pthread_t thread[4 * N];
    int args[4 * N];
    void *results[4 * N];

    for (int i = 0; i < 4 * N; ++i) {
        args[i] = rand() % 15 + 1;
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    for (int i = 0; i < 2 * N; ++i) {
        if (i % 2) {
            pthread_create(&thread[i], NULL, producer, &args[i]);
        } else {
            pthread_create(&thread[i], NULL, consumer, &args[i]);
        }
    }

    pthread_barrier_init(&barrier, NULL, 2 * N);
    for (int i = 2 * N; i < 4 * N; ++i) {
        pthread_create(&thread[i], NULL, barrier_worker, &args[i]);
    }

    for (int i = 0; i < 4 * N; ++i) {
        pthread_join(thread[i], &results[i]);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    pthread_barrier_destroy(&barrier);

    return 0;
}
