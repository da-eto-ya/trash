#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    auto size = 1UL << 20;

    auto md = shm_open("/test.shm", O_CREAT | O_RDWR | O_TRUNC, 0777);
    ftruncate(md, size);
    auto at = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, md, 0);

    memset(at, 13, size);

    return 0;
}
