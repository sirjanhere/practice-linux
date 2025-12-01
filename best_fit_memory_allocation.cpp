#include <iostream>
using namespace std;

int main() {
    int holes[5], processes[5];
    int allocation[5];

    cout << "Enter sizes of 5 memory holes:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Hole " << i + 1 << " size: ";
        cin >> holes[i];
    }

    cout << "\nEnter sizes of 5 processes:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Process " << i + 1 << " size: ";
        cin >> processes[i];
        allocation[i] = -1;   // initially not allocated
    }

    // Best Fit Allocation
    for (int i = 0; i < 5; i++) {
        int bestIndex = -1;
        for (int j = 0; j < 5; j++) {
            if (holes[j] >= processes[i]) {
                if (bestIndex == -1 || holes[j] < holes[bestIndex]) {
                    bestIndex = j;
                }
            }
        }

        if (bestIndex != -1) {
            allocation[i] = bestIndex;          // allocate
            holes[bestIndex] -= processes[i];   // reduce hole size
        }
    }

    cout << "\nAllocation Result (Best Fit):\n";
    for (int i = 0; i < 5; i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " of size " << processes[i]
                 << " allocated to Hole " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " of size " << processes[i]
                 << " could NOT be allocated\n";
    }

    return 0;
}
