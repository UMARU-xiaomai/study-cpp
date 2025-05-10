#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

struct message {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate key
    key = ftok("/tmp", 'A');
    if (key == -1) {
        std::cerr << "ftok failed" << std::endl;
        return 1;
    }

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        std::cerr << "msgget failed" << std::endl;
        return 1;
    }

    // Create child process
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed" << std::endl;
        return 1;
    }

    if (pid > 0) {  // Parent process
        // Prepare message
        msg.mtype = 1;
        strcpy(msg.mtext, "Hello from parent process!");

        // Send message
        std::cout << "Parent: Sending message..." << std::endl;
        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
            std::cerr << "msgsnd failed" << std::endl;
            return 1;
        }

        // Wait for child to finish
        wait(NULL);

        // Remove message queue
        msgctl(msgid, IPC_RMID, NULL);
    } else {  // Child process
        // Receive message
        std::cout << "Child: Waiting for message..." << std::endl;
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
            std::cerr << "msgrcv failed" << std::endl;
            return 1;
        }

        std::cout << "Child: Received message: " << msg.mtext << std::endl;
    }

    return 0;
} 