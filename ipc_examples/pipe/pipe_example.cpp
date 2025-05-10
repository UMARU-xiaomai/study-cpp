#include <iostream>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];

    // Create pipe
    if (pipe(pipefd) == -1) {
        std::cerr << "Pipe creation failed" << std::endl;
        return 1;
    }

    // Create child process
    pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed" << std::endl;
        return 1;
    }

    if (pid > 0) {  // Parent process
        close(pipefd[0]);  // Close read end
        
        const char* message = "Hello from parent process!";
        std::cout << "Parent: Writing to pipe..." << std::endl;
        write(pipefd[1], message, strlen(message) + 1);
        
        close(pipefd[1]);  // Close write end
        wait(NULL);  // Wait for child to finish
    } else {  // Child process
        close(pipefd[1]);  // Close write end
        
        std::cout << "Child: Reading from pipe..." << std::endl;
        read(pipefd[0], buffer, sizeof(buffer));
        std::cout << "Child: Received message: " << buffer << std::endl;
        
        close(pipefd[0]);  // Close read end
    }

    return 0;
} 