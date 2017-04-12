#include <cstring>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <fcntl.h>
#include <sys/wait.h>

using namespace std;

char *read_cmd() {
    string cmd_str;
    getline(cin, cmd_str);
    char *cmd = new char[cmd_str.length() + 1];
    memcpy(cmd, cmd_str.c_str(), cmd_str.length());
    cmd[cmd_str.length()] = '\0';

    return cmd;
}

char **process_args(char *str) {
    vector<char *> tokens;
    char *token_label;
    static const char *separators = " \t\n\v\r\f";
    char *pos = strtok_r(str, separators, &token_label);

    while (pos != NULL) {
        tokens.push_back(pos);
        pos = strtok_r(NULL, separators, &token_label);
    }

    if (tokens.empty()) {
        return NULL;
    }

    char **args = new char *[tokens.size() + 1];
    memcpy(args, tokens.data(), tokens.size() * sizeof(char *));
    args[tokens.size()] = NULL;

    return args;
}

int main(int argc, char **argv) {
    // prepare command array
    vector<char **> commands;

    char *cmd_str = read_cmd();
    char *token_label;
    static const char *separators = "|";
    char *pos = strtok_r(cmd_str, separators, &token_label);

    while (pos != NULL) {
        char **args = process_args(pos);

        if (args != NULL) {
            commands.push_back(args);
        }

        pos = strtok_r(NULL, separators, &token_label);
    }

    // make children
    int N = commands.size();
    int N2 = N * 2;

    int *pipes = new int[N2];

    for (int i = 0; i < N; ++i) {
        pipe(pipes + i * 2);
    }

    for (int i = 0; i < N; ++i) {
        if (fork() == 0) {
            // children: pipes
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

    // parent: close pipes and collect output
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

    // parent: wait children
    int status;

    for (int j = 0; j < N; ++j) {
        wait(&status);
    }

    return 0;
}
