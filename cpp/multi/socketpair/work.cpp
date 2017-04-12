#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>

int main(void) {
    int N = 10;
    int fds[2];
    char buf;

    socketpair(AF_UNIX, SOCK_STREAM, 0, fds);

    if (!fork()) {
        for (int i = 0; i < N; ++i) {
            read(fds[1], &buf, 1);
            printf("child: read '%c'\n", buf);
            buf = toupper(buf);  /* make it uppercase */
            write(fds[1], &buf, 1);
            printf("child: sent '%c'\n", buf);
            sleep(1 + rand() % 4);
        }
    } else { /* parent */
        for (int i = 0; i < N; ++i) {
            write(fds[0], "b", 1);
            printf("parent: sent 'b'\n");
            read(fds[0], &buf, 1);
            printf("parent: read '%c'\n", buf);
            sleep(1 + rand() % 4);
        }
    }
    return 0;
}
