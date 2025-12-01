#include <iostream>
#include <unistd.h>
using namespace std;

int main() {

    cout << "Before fork: executed once.\n\n";

    int f = fork();

    if (f < 0) {
        cerr << "Fork error!\n";
        return 1;
    }

    // Now both parent and child execute THIS code:
    cout << "This line is executed by BOTH processes.\n";

    // Differentiate just by f==0 (child) or f>0 (parent)
    if (f == 0)
        cout << "Message from CHILD: still the same code, same program.\n";
    else
        cout << "Message from PARENT: still the same code, same program.\n";

    cout << "End of program reached by BOTH.\n\n";

    return 0;
}
