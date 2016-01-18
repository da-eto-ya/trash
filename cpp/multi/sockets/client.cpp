#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
    const size_t buffer_size = 2048;
    char buffer[buffer_size];

    // specify address
    sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "/tmp/cpp.multi.sockets.sock");

    // create socket
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);

    if (sock == -1) {
        perror("Can't create socket");

        return -1;
    }

    // connect to server
    if (connect(sock, (sockaddr *) &address, sizeof(address)) == -1) {
        perror("Can't connect to server");

        return -2;
    }

    // send data
    while (true) {
        std::string message;
        std::getline(std::cin, message);

        if (message == "quit") {
            break;
        }

        if (message.length() >= buffer_size) {
            std::cerr << "[message truncated to " << buffer_size - 1 << " chars]" << std::endl;
            message = message.substr(0, buffer_size - 1);
        }

        send(sock, message.c_str(), message.length(), MSG_NOSIGNAL);
        recv(sock, buffer, message.length(), MSG_NOSIGNAL);
        buffer[message.length()] = '\0';

        std::cout << buffer << std::endl;
    }

    shutdown(sock, SHUT_RDWR);
    close(sock);

    return 0;
}
