#include <iostream>
#include <iomanip>
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
        pid = arr_time = burst_time = start_time = finish_time = waiting_time = turnaround_time = 0;
        original_burst = 0;
    }
};

process* p;
int n;

void input() {
    cout << "Enter the number of processes: ";
    cin >> n;

    p = new process[n];

    for (int i = 0; i < n; i++) {
        cout << "\n** Process " << i + 1 << " **\n";
        cout << "\tPID: ";
        cin >> p[i].pid;
        cout << "\tArrival Time: ";
        cin >> p[i].arr_time;
        cout << "\tBurst Time: ";
        cin >> p[i].burst_time;
        p[i].original_burst = p[i].burst_time;
    }
}

void sortByArrival() {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (p[j].arr_time < p[j - 1].arr_time) {
                swap(p[j], p[j - 1]);
            }
        }
    }
}

void printFormat2(const string& title) {
    cout << "\n--- " << title << " (Format 2) ---\n";
    cout << left << setw(10) << "PID"
         << setw(15) << "Arrival"
         << setw(10) << "Burst"
         << setw(15) << "Turnaround"
         << setw(15) << "Waiting" << "\n";

    double total_turnaround = 0, total_waiting = 0;

    for (int i = 0; i < n; i++) {
        cout << setw(10) << p[i].pid
             << setw(15) << p[i].arr_time
             << setw(10) << p[i].original_burst
             << setw(15) << p[i].turnaround_time
             << setw(15) << p[i].waiting_time << "\n";

        total_turnaround += p[i].turnaround_time;
        total_waiting += p[i].waiting_time;
    }

    cout << "\nAverage Turnaround Time: " << total_turnaround / n << endl;
    cout << "Average Waiting Time: " << total_waiting / n << endl;
}

// ------------------- FCFS ONLY -------------------
void fcfs() {
    cout << "\n==================== FCFS ====================\n";

    int current_time = 0;

    cout << "--- Format 1 ---\n";
    cout << "PID\tStart\tFinish\n";

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arr_time)
            current_time = p[i].arr_time;

        p[i].start_time = current_time;
        p[i].finish_time = current_time + p[i].burst_time;

        cout << p[i].pid << "\t" << p[i].start_time << "\t" << p[i].finish_time << "\n";

        current_time = p[i].finish_time;

        p[i].turnaround_time = p[i].finish_time - p[i].arr_time;
        p[i].waiting_time = p[i].start_time - p[i].arr_time;
    }

    printFormat2("FCFS Scheduling");
}

int main() {
    input();
    sortByArrival();
    fcfs();

    delete[] p;
    return 0;
}
