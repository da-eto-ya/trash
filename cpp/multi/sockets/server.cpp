#include <ctime>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

std::string current_time() {
    std::time_t tm = std::time(NULL);
    std::string t(std::ctime(&tm));

    return t.substr(0, t.length() - 1);
}

int main() {
    const size_t buffer_size = 2048;
    char buffer[buffer_size];

    // specify address
    sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "/tmp/cpp.multi.sockets.sock");
    unlink(address.sun_path);

    // create socket
    int master_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if (master_socket == -1) {
        perror("Can't create socket");

        return -1;
    }

    // bind socket
    if (bind(master_socket, (sockaddr *) &address, sizeof(address)) == -1) {
        perror("Can't bind socket");

        return -2;
    }

    // listen socket
    if (listen(master_socket, SOMAXCONN) == -1) {
        perror("Can't listen socket");

        return -3;
    }

    // accept connections
    while (true) {
        int connection = accept(master_socket, 0, 0);

        if (connection == -1) {
            perror("Can't accept connection");

            return -4;
        }


        std::cout << "[" << current_time() << "]+ " << "New client connected." << std::endl;

        while (true) {
            ssize_t read_count = recv(connection, buffer, buffer_size - 1, MSG_NOSIGNAL);

            if (read_count <= 0) {
                break;
            }

            if (send(connection, buffer, read_count, MSG_NOSIGNAL) == -1) {
                break;
            };

            buffer[read_count] = '\0';
            std::cout << "[" << current_time() << "]> " << buffer << std::endl;
        }

        close(connection);

        std::cout << "[" << current_time() << "]- " << "Client disconnected." << std::endl;
    }

    return 0;
}
