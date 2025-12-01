#include <iostream>
#include <unistd.h>
using namespace std;

int main() {

    cout << "This line is before fork(). It is executed only once.\n";

    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }

    cout << "\nNow both parent and child will execute this same code block.\n";

    if (pid == 0) {
        cout << ">>> CHILD executing the SAME PROGRAM\n";
        cout << "Child PID: " << getpid() << endl;
        cout << "Parent PID of child: " << getppid() << endl;
    } 
    else {
        cout << ">>> PARENT executing the SAME PROGRAM\n";
        cout << "Parent PID: " << getpid() << endl;
        cout << "Child PID returned by fork(): " << pid << endl;
    }

    cout << "This line is executed by BOTH parent and child.\n";

    return 0;
}
