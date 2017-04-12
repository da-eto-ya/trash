#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message {
    long mtype;
    char mtext[80];
};

int main(int argc, char **argv) {
    const char *pathname = "/tmp/msg.temp";
    const size_t message_len = sizeof(((message *) 0)->mtext);

    // connect to queue
    key_t key = ftok(pathname, 1);
    int mq_id = msgget(key, 0777);

    // create message
    message *msg = new message;
    msg->mtype = 1;
    strcpy(msg->mtext, "Hello, messages!");

    // send message
    msgsnd(mq_id, msg, message_len, IPC_NOWAIT);

    return 0;
}
