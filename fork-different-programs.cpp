#include <iostream>
#include <unistd.h>
using namespace std;

int main() {

    cout << "This line prints BEFORE fork(). Only once.\n\n";

    pid_t pid = fork();

    if (pid < 0) {
        cout << "Fork failed.\n";
        return 1;
    }

    if (pid == 0) {
        // CHILD executes a different program
        cout << "Child: Now I will run the DATE command (different program).\n\n";
        execlp("date", "date", (char*)NULL);
        cout << "Child: execlp failed.\n";
    } 
    else {
        // PARENT executes a different program
        cout << "Parent: Now I will run the LS command (different program).\n\n";
        execlp("ls", "ls", (char*)NULL);
        cout << "Parent: execlp failed.\n";
    }

    return 0;
}
