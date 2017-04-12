#include <stdio.h>
#include <mqueue.h>

static const size_t max_msg_len = 1000;
static const size_t max_msg_cnt = 10;

int main(int argc, char **argv) {
    const char *pathname = "/test.mq";

    // create queue
    mq_attr attr;
    attr.mq_maxmsg = max_msg_cnt;
    attr.mq_msgsize = max_msg_len;
    mqd_t mq = mq_open(pathname, O_CREAT | O_RDWR, 0777, &attr);

    // wait message
    unsigned int sender;
    char content[max_msg_len + 1];
    ssize_t sz = mq_receive(mq, content, max_msg_len, &sender);
    content[sz] = '\0';

    // show message
    printf("%s\n", content);

    return 0;
}
