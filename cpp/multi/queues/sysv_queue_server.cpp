#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

struct message {
    long mtype;
    char mtext[80];
};

int main(int argc, char **argv) {
    const char *pathname = "/tmp/msg.temp";
    const size_t message_len = sizeof(((message *) 0)->mtext);

    // create file slot
    int fd = open(pathname, O_CREAT, 0777);
    close(fd);

    // create queue
    key_t key = ftok(pathname, 1);
    int mq_id = msgget(key, IPC_CREAT | 0777);

    // wait message
    message *cb = new message;
    cb->mtype = 0;
    cb->mtext[0] = '\0';

    msgrcv(mq_id, cb, message_len, 0, 0);

    // show message
    printf("%s\n", cb->mtext);

    return 0;
}
