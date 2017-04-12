#include <pthread.h>
#include <unistd.h>

void *slow(void *arg) {
    sleep(120);

    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, slow, NULL);
    void *result;
    pthread_join(thread, &result);

    return 0;
}
