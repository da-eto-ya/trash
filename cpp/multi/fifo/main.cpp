#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main() {
    char in_name[] = "in.fifo";
    char out_name[] = "out.fifo";

    mkfifo(in_name, 0666);
    mkfifo(out_name, 0666);

    int in = open(in_name, O_RDONLY);
    int out = open(out_name, O_WRONLY);

    size_t buf_size = 10240;
    char *buf = new char[buf_size];
    ssize_t read_len;

    while ((read_len = read(in, buf, buf_size)) > 0) {
        write(out, buf, read_len);
    }

    close(out);
    close(in);

    return 0;
}
