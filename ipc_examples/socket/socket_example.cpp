#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#define SOCKET_PATH "/tmp/ipc_socket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    char buffer[100];

    // Create socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    // Remove existing socket file if it exists
    unlink(SOCKET_PATH);

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }

    // Listen for connections
    if (listen(server_fd, 5) == -1) {
        std::cerr << "Listen failed" << std::endl;
        return 1;
    }

    std::cout << "Server: Waiting for connection..." << std::endl;

    // Accept connection
    socklen_t client_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd == -1) {
        std::cerr << "Accept failed" << std::endl;
        return 1;
    }

    // Receive message
    ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        std::cout << "Server: Received message: " << buffer << std::endl;
    }

    // Send response
    const char* response = "Message received!";
    send(client_fd, response, strlen(response), 0);

    // Cleanup
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);

    return 0;
} 