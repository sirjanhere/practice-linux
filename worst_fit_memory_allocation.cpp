#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const int HOLES = 5;
    const int PROCESSES = 5;

    int holeSize[HOLES];
    int processSize[PROCESSES];
    int allocation[PROCESSES]; // allocation[i] = index of hole where process i is placed, -1 if not allocated

    cout << "Enter sizes of " << HOLES << " memory holes:\n";
    for (int i = 0; i < HOLES; i++) {
        cout << "Hole " << (i + 1) << " size: ";
        cin >> holeSize[i];

        if (holeSize[i] < 0) {
            cout << "Size cannot be negative. Setting Hole " << (i + 1) << " size to 0.\n";
            holeSize[i] = 0;
        }
    }

    cout << "\nEnter sizes of " << PROCESSES << " processes:\n";
    for (int i = 0; i < PROCESSES; i++) {
        cout << "Process " << (i + 1) << " size: ";
        cin >> processSize[i];

        if (processSize[i] <= 0) {
            cout << "Process size must be positive. ";
            cout << "This process will not be allocated.\n";
        }
    }

    // Initialize all processes as not allocated
    for (int i = 0; i < PROCESSES; i++) {
        allocation[i] = -1;
    }

    // WORST FIT ALLOCATION
    for (int i = 0; i < PROCESSES; i++) {
        if (processSize[i] <= 0) {
            // Already treated as invalid, keep as not allocated
            continue;
        }

        int worstIndex = -1;
        int worstSize = -1;

        // Find the hole with the largest size that can still accommodate this process
        for (int j = 0; j < HOLES; j++) {
            if (holeSize[j] >= processSize[i]) {
                if (holeSize[j] > worstSize) {
                    worstSize = holeSize[j];
                    worstIndex = j;
                }
            }
        }

        // If we found a suitable hole
        if (worstIndex != -1) {
            allocation[i] = worstIndex;              // assign process i to this hole
            holeSize[worstIndex] -= processSize[i];  // reduce available size in that hole
        }
        // else: allocation[i] stays -1 (not allocated)
    }

    cout << "\nAllocation Result (Worst Fit Strategy):\n";
    cout << left << setw(12) << "Process"
         << setw(15) << "Size"
         << setw(20) << "Allocated Hole\n";
    cout << "---------------------------------------------\n";

    for (int i = 0; i < PROCESSES; i++) {
        cout << left << setw(12) << ("P" + to_string(i + 1))
             << setw(15) << processSize[i];

        if (allocation[i] != -1) {
            // Add 1 to show hole numbers starting from 1 (not 0)
            cout << "Hole " << (allocation[i] + 1) << "\n";
        } else {
            cout << "Not allocated\n";
        }
    }

    cout << "\nRemaining size in each hole after allocation:\n";
    for (int j = 0; j < HOLES; j++) {
        cout << "Hole " << (j + 1) << " remaining size: " << holeSize[j] << "\n";
    }

    return 0;
}
