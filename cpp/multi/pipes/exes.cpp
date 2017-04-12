#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char **argv) {
    vector<char **> commands;
    char *a0[] = {(char *) "cat", (char *) "/home/ilya/entries.txt", NULL};
    char *a1[] = {(char *) "sort", NULL};
    char *a2[] = {(char *) "uniq", NULL};
    commands.push_back(a0);
    commands.push_back(a1);
    commands.push_back(a2);


    int N = commands.size();
    int N2 = N * 2;

    int *pipes = new int[N2];

    for (int i = 0; i < N; ++i) {
        pipe(pipes + i * 2);
    }

    for (int i = 0; i < N; ++i) {
        if (fork() == 0) {
            if (i != 0) {
                dup2(pipes[2 * (i - 1)], STDIN_FILENO);
            }

            dup2(pipes[2 * i + 1], STDOUT_FILENO);

            for (int j = 0; j < N2; ++j) {
                close(pipes[j]);
            }

            execvp(commands[i][0], commands[i]);

            return 0;
        }
    }

    int exhaust_pipe = N2 - 2;

    for (int j = 0; j < N2; ++j) {
        if (j != exhaust_pipe) {
            close(pipes[j]);
        }
    }

    char *output_filename;

    if (argc == 2) {
        output_filename = argv[1];
    } else {
        output_filename = (char *) "/home/box/result.out";
    }

    int output_file = open(output_filename, O_CREAT | O_WRONLY | O_TRUNC,
                           S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    ssize_t read_len = 0;
    size_t buf_size = 10240;
    char *buf = new char[buf_size];

    while ((read_len = read(pipes[exhaust_pipe], buf, buf_size)) > 0) {
        write(output_file, buf, read_len);
    }

    close(output_file);
    close(pipes[exhaust_pipe]);

    int status;

    for (int j = 0; j < N; ++j) {
        wait(&status);
    }

    return 0;
}
