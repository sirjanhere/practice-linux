#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const int NUM_HOLES = 5;
    const int NUM_PROCESSES = 5;

    int holes[NUM_HOLES];
    int remaining[NUM_HOLES];   // To keep track of remaining space in each hole
    int processes[NUM_PROCESSES];
    int allocation[NUM_PROCESSES]; // allocation[i] = index of hole assigned to process i, -1 if not allocated

    // Input memory holes
    cout << "Enter sizes of " << NUM_HOLES << " memory holes:\n";
    for (int i = 0; i < NUM_HOLES; i++) {
        cout << "Hole " << i + 1 << " size: ";
        cin >> holes[i];
        remaining[i] = holes[i]; // initially remaining = original sizes
    }

    // Input processes
    cout << "\nEnter sizes of " << NUM_PROCESSES << " processes:\n";
    for (int i = 0; i < NUM_PROCESSES; i++) {
        cout << "Process " << i + 1 << " size: ";
        cin >> processes[i];
        allocation[i] = -1; // initially, no process is allocated
    }

    // First Fit Allocation
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_HOLES; j++) {
            // If hole j can fit process i
            if (remaining[j] >= processes[i]) {
                allocation[i] = j;         // assign this hole to the process
                remaining[j] -= processes[i]; // reduce remaining space of the hole
                break;                     // move to next process (First Fit)
            }
        }
    }

    // Output allocation result
    cout << "\nFirst Fit Allocation Result:\n";
    cout << left << setw(10) << "Process"
         << setw(10) << "P_Size"
         << setw(10) << "Hole"
         << "\n";

    for (int i = 0; i < NUM_PROCESSES; i++) {
        cout << left << setw(10) << ("P" + to_string(i + 1))
             << setw(10) << processes[i];

        if (allocation[i] != -1)
            cout << "H" << (allocation[i] + 1); // +1 to show hole number from 1–5
        else
            cout << "Not alloc";

        cout << "\n";
    }

    // Optional: show remaining space in each hole
    cout << "\nRemaining space in each hole after allocation:\n";
    for (int j = 0; j < NUM_HOLES; j++) {
        cout << "Hole " << j + 1 << " (Original: " << holes[j]
             << ") -> Remaining: " << remaining[j] << "\n";
    }

    return 0;
}