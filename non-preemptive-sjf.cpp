#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct process {
    int pid;
    int arr_time;
    int burst_time;
    int original_burst;  
    int start_time;
    int finish_time;
    int waiting_time;
    int turnaround_time;

    process() {
        pid = arr_time = burst_time = original_burst = 0;
        start_time = finish_time = waiting_time = turnaround_time = 0;
    }
};

process* p;
int n;

void input() {
    cout << "Enter the number of processes: ";
    cin >> n;
    p = new process[n];

    for(int i = 0; i < n; i++) {
        cout << "\n** Process " << i+1 << " **\n";
        cout << "\tPID: ";
        cin >> p[i].pid;
        cout << "\tArrival Time: ";
        cin >> p[i].arr_time;
        cout << "\tBurst Time: ";
        cin >> p[i].burst_time;
        p[i].original_burst = p[i].burst_time;
    }
}

// Sort processes by arrival time
void sortByArrival() {
    for(int i = 1; i < n; i++) {
        for(int j = i; j > 0; j--) {
            if(p[j].arr_time < p[j-1].arr_time) {
                swap(p[j], p[j-1]);
            }
        }
    }
}

// Print: PID, Arrival, Burst, Turnaround, Waiting + averages
void printResults() {
    cout << "\n--- Non-Preemptive SJF (Format 2) ---\n";
    cout << left << setw(10) << "PID"
         << setw(15) << "Arrival"
         << setw(10) << "Burst"
         << setw(15) << "Turnaround"
         << setw(15) << "Waiting" << "\n";

    double total_turnaround = 0, total_waiting = 0;
    for(int i = 0; i < n; i++) {
        cout << setw(10) << p[i].pid
             << setw(15) << p[i].arr_time
             << setw(10) << p[i].original_burst
             << setw(15) << p[i].turnaround_time
             << setw(15) << p[i].waiting_time << "\n";

        total_turnaround += p[i].turnaround_time;
        total_waiting += p[i].waiting_time;
    }

    cout << "Average Turnaround Time: " << total_turnaround / n << "\n";
    cout << "Average Waiting Time: " << total_waiting / n << "\n";
}

// ---------------- Non-preemptive SJF only ----------------
void sjfNonPreemptive() {
    cout << "\n================ Non-Preemptive SJF ================\n";

    bool* done = new bool[n]{false};
    int completed = 0;
    int current_time = 0;

    cout << "--- Format 1 ---\n";
    cout << "PID\tStart\tFinish\n";

    while(completed < n) {
        int idx = -1;
        int min_burst = 1e9;

        for(int i = 0; i < n; i++) {
            if(!done[i] && p[i].arr_time <= current_time) {
                if(p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            current_time++;
            continue;
        }

        p[idx].start_time = current_time;
        p[idx].finish_time = current_time + p[idx].burst_time;
        cout << p[idx].pid << "\t" << p[idx].start_time << "\t" << p[idx].finish_time << "\n";

        p[idx].turnaround_time = p[idx].finish_time - p[idx].arr_time;
        p[idx].waiting_time = p[idx].start_time - p[idx].arr_time;

        done[idx] = true;
        completed++;
        current_time = p[idx].finish_time;
    }

    printResults();
    delete[] done;
}

int main() {
    input();
    sortByArrival();
    sjfNonPreemptive();
    delete[] p;
    return 0;
}
