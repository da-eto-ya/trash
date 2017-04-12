#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int mutex_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *mutex_inc(void *arg) {
    unsigned int *p = (unsigned int *) arg;

    sleep(*p);
    pthread_mutex_lock(&mutex);
    printf("[mutex_inc] locked\n");
    ++mutex_count;
    printf("[mutex_inc] inc: %d\n", mutex_count);
    sleep(*p);
    pthread_mutex_unlock(&mutex);
    printf("[mutex_inc] unlocked\n");
    
    return NULL;
}

int spin_count = 0;
pthread_spinlock_t spin;

void *spin_inc(void *arg) {
    unsigned int *p = (unsigned int *) arg;

    sleep(*p);
    pthread_spin_lock(&spin);
    printf("[spin_inc] locked\n");
    ++spin_count;
    printf("[spin_inc] inc: %d\n", spin_count);
    sleep(*p);
    pthread_spin_unlock(&spin);
    printf("[spin_inc] unlocked\n");

    return NULL;
}

int rwlock_count = 0;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void *rwlock_reader(void *arg) {
    unsigned int *p = (unsigned int *) arg;

    sleep(*p);
    pthread_rwlock_rdlock(&rwlock);
    printf("[rwlock_reader] locked\n");
    printf("[rwlock_reader] val: %d\n", rwlock_count);
    sleep(*p);
    pthread_rwlock_unlock(&rwlock);
    printf("[rwlock_reader] unlocked\n");

    return NULL;
}

void *rwlock_writer(void *arg) {
    unsigned int *p = (unsigned int *) arg;

    sleep(*p);
    pthread_rwlock_wrlock(&rwlock);
    printf("[rwlock_writer] locked\n");
    ++rwlock_count;
    printf("[rwlock_writer] inc: %d\n", rwlock_count);
    sleep(*p);
    pthread_rwlock_unlock(&rwlock);
    printf("[rwlock_writer] unlocked\n");

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
    for (int i = 0; i < N; ++i) {
        pthread_create(&thread[i], NULL, mutex_inc, &args[i]);
    }

    pthread_spin_init(&spin, PTHREAD_PROCESS_SHARED);
    for (int i = N; i < 2 * N; ++i) {
        pthread_create(&thread[i], NULL, spin_inc, &args[i]);
    }

    pthread_rwlock_init(&rwlock, NULL);
    for (int i = 2 * N; i < 4 * N; ++i) {
        if (i % 2) {
            pthread_create(&thread[i], NULL, rwlock_reader, &args[i]);
        } else {
            pthread_create(&thread[i], NULL, rwlock_writer, &args[i]);
        }
    }

    for (int i = 0; i < 4 * N; ++i) {
        pthread_join(thread[i], &results[i]);
    }

    pthread_mutex_destroy(&mutex);
    pthread_spin_destroy(&spin);
    pthread_rwlock_destroy(&rwlock);

    return 0;
}
