#include <iostream>
#include <unistd.h>     // fork(), getpid(), getppid()
#include <sys/types.h>  // pid_t

using namespace std;

int main() {
    // Print once, before fork()
    cout << "Program started. This line is printed BEFORE fork(), "
         << "so it runs only once.\n\n";

    // Create a new process
    pid_t pid = fork();

    // Check for fork failure
    if (pid < 0) {
        cerr << "Error: fork() failed. Could not create child process.\n";
        return 1;
    }

    // Child process block: pid == 0 ONLY in the child
    if (pid == 0) {
        cout << "---------------------------\n";
        cout << "       CHILD PROCESS       \n";
        cout << "---------------------------\n";
        cout << "Child PID        : " << getpid() << '\n';
        cout << "Parent PID (PPID): " << getppid() << '\n';
        cout << "Hello, I am child process.\n";
        cout << "I am executing a DIFFERENT code section of the SAME program.\n\n";
    }
    // Parent process block: pid > 0 ONLY in the parent
    else {
        cout << "---------------------------\n";
        cout << "       PARENT PROCESS      \n";
        cout << "---------------------------\n";
        cout << "Parent PID       : " << getpid() << '\n';
        cout << "Child PID (from fork): " << pid << '\n';
        cout << "Hello, I am parent process.\n";
        cout << "I am also executing a DIFFERENT code section of the SAME program.\n\n";
    }

    // This part is executed by BOTH parent and child
    cout << "Common line: This statement is executed by BOTH processes.\n";

    return 0;
}
