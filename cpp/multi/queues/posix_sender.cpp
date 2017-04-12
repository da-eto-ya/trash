#include <fcntl.h>
#include <stdio.h>
#include <mqueue.h>
#include <string.h>

static const size_t max_msg_len = 1000;

int main(int argc, char **argv) {
    const char *pathname = "/test.mq";

    // create queue
    mqd_t mq = mq_open(pathname, O_RDWR);

    // wait message
    unsigned int sender = 0;
    const char *const content = "Hi my master";
    mq_send(mq, content, strlen(content), sender);

    // show message
    printf("%s\n", content);

    return 0;
}
