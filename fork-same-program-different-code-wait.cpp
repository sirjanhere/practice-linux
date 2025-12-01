#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {

    cout << "This line appears ONCE (before fork).\n\n";

    int f = fork();

    if (f < 0) {
        cerr << "Fork failed.\n";
        return 1;
    }

    // =====================================================
    //     COMMON CODE (executed by BOTH parent & child)
    // =====================================================
    cout << ">>> BOTH PROCESSES ARE EXECUTING THIS SAME CODE.\n";
    cout << ">>> This proves parent and child run the SAME program.\n\n";

    if (f == 0) {
        // =======================
        //       CHILD
        // =======================
        cout << "---- CHILD: Now executing CHILD-ONLY section ----\n";
        for (int i = 1; i <= 3; i++) {
            cout << "Child step " << i << endl;
            sleep(1);
        }
        cout << "Child finished.\n\n";
    } 
    else {
        // PARENT waits for the child to finish
        wait(nullptr);

        // =======================
        //       PARENT
        // =======================
        cout << "---- PARENT: Now executing PARENT-ONLY section ----\n";
        for (int i = 1; i <= 3; i++) {
            cout << "Parent step " << i << endl;
            sleep(1);
        }
        cout << "Parent finished.\n";
    }

    return 0;
}
