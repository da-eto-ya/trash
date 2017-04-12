#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h>

int main() {
    auto size = 1UL << 20;
    auto pathname = "/tmp/mem.temp";

    creat(pathname, 0777);

    key_t key = ftok(pathname, 1);
    auto mem_id = shmget(key, size, IPC_CREAT | 0777);
    auto *at = shmat(mem_id, NULL, 0);

    memset(at, 42, size);

    return 0;
}
