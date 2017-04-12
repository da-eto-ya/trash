#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

static const unsigned short sem_count = 16;

int main() {
    const char *const pathname = "/tmp/sem.temp";
    key_t key = ftok(pathname, 1);
    int sem_id = semget(key, sem_count, IPC_CREAT | 0666);
    sembuf sb[sem_count];

    for (unsigned short i = 0; i < sem_count; ++i) {
        sb[i].sem_num = i;
        sb[i].sem_op = i;
        sb[i].sem_flg = 0;
    }

    semop(sem_id, sb, sem_count);
    return 0;
}
