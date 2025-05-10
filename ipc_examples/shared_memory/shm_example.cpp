#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *shm, *s;

    // Generate key
    key = ftok("/tmp", 'B');
    if (key == -1) {
        std::cerr << "ftok failed" << std::endl;
        return 1;
    }

    // Create shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        std::cerr << "shmget failed" << std::endl;
        return 1;
    }

    // Create child process
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed" << std::endl;
        return 1;
    }

    if (pid > 0) {  // Parent process
        // Attach to shared memory
        shm = (char*)shmat(shmid, NULL, 0);
        if (shm == (char*)-1) {
            std::cerr << "shmat failed" << std::endl;
            return 1;
        }

        // Write to shared memory
        const char* message = "Hello from parent process!";
        std::cout << "Parent: Writing to shared memory..." << std::endl;
        strcpy(shm, message);

        // Wait for child to finish
        wait(NULL);

        // Detach from shared memory
        shmdt(shm);

        // Remove shared memory segment
        shmctl(shmid, IPC_RMID, NULL);
    } else {  // Child process
        // Attach to shared memory
        shm = (char*)shmat(shmid, NULL, 0);
        if (shm == (char*)-1) {
            std::cerr << "shmat failed" << std::endl;
            return 1;
        }

        // Read from shared memory
        std::cout << "Child: Reading from shared memory..." << std::endl;
        std::cout << "Child: Received message: " << shm << std::endl;

        // Detach from shared memory
        shmdt(shm);
    }

    return 0;
} 