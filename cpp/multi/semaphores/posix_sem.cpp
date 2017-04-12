#include <semaphore.h>
#include <fcntl.h>

int main() {
    const char *const pathname = "/test.sem";
    int value = 66;
    sem_open(pathname, O_CREAT, 0777, value);

    return 0;
}
