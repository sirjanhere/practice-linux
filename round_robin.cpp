#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid, arrival, burst, remaining, completion;
};

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "\nProcess " << p[i].pid << ":\n";
        cout << "Arrival Time: ";
        cin >> p[i].arrival;
        cout << "Burst Time: ";
        cin >> p[i].burst;
        p[i].remaining = p[i].burst;
        p[i].completion = 0;
    }

    cout << "\nEnter Time Quantum: ";
    cin >> quantum;

    // Sort by arrival for correct start
    sort(p.begin(), p.end(), [](auto &a, auto &b){ return a.arrival < b.arrival; });

    queue<int> q;
    int time = p[0].arrival;
    int completed = 0;
    int idx = 0;
    int N = n;

    // Insert all processes that arrive at the first arrival time
    while (idx < N && p[idx].arrival <= time) {
        q.push(idx);
        idx++;
    }

    while (completed < N) {

        if (q.empty()) {
            time = p[idx].arrival;
            q.push(idx);
            idx++;
            continue;
        }

        int i = q.front();
        q.pop();

        int exec = min(quantum, p[i].remaining);
        p[i].remaining -= exec;
        int oldTime = time;
        time += exec;

        // RULE 
        // Insert all newly arrived processes BEFORE reinserting current process
        while (idx < N && p[idx].arrival <= time) {
            q.push(idx);
            idx++;
        }

        if (p[i].remaining > 0) {
            q.push(i);        // reinsert AFTER arrivals
        } else {
            p[i].completion = time;
            completed++;
        }
    }

    // Sort back by PID to print properly
    sort(p.begin(), p.end(), [](auto &a, auto &b){ return a.pid < b.pid; });

    double totalTAT = 0, totalWT = 0;

    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (auto &x : p) {
        int tat = x.completion - x.arrival;
        int wt = tat - x.burst;

        totalTAT += tat;
        totalWT += wt;

        cout << "P" << x.pid << "\t" 
             << x.arrival << "\t"
             << x.burst << "\t"
             << x.completion << "\t\t"
             << tat << "\t\t"
             << wt << "\n";
    }

    cout << "\nAverage Turnaround Time = " << (totalTAT / n);
    cout << "\nAverage Waiting Time    = " << (totalWT / n) << endl;

    return 0;
}
