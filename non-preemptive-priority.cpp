#include <stdio.h>

struct process {
    int pid;        // Process ID
    int burst_time; // Burst Time
    int arrival_time; // Arrival Time
    int priority;   // Priority Number (Lower = Higher Priority)
    int done;       // Completion Flag
    int start_time;
    int finish_time;
    int turnaround_time;
    int waiting_time;
};

int n;
struct process p[50];

void input() {
    int i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details in the following table format:\n");
    printf("---------------------------------------------------------------\n");
    printf("PID\tArrival_Time\tBurst_Time\tPriority_Number\n");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        scanf("%d%d%d%d", &p[i].pid, &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].done = 0;
    }
}

// Sort by arrival time (ascending)
void sortByArrival() {
    int i, j;
    struct process temp;
    for (i = 1; i < n; i++) {
        temp = p[i];
        j = i - 1;
        while (j >= 0 && p[j].arrival_time > temp.arrival_time) {
            p[j + 1] = p[j];
            j--;
        }
        p[j + 1] = temp;
    }
}

// Find process with highest priority (lowest priority number)
int find_next_process(int current_time) {
    int i, index = -1, best_priority = 9999;
    for (i = 0; i < n; i++) {
        if (p[i].done == 0 && p[i].arrival_time <= current_time) {
            if (p[i].priority < best_priority) {
                best_priority = p[i].priority;
                index = i;
            }
        }
    }
    return index;
}

void priorityScheduling() {
    int completed = 0, current_time = 0;
    float total_turnaround = 0, total_waiting = 0;
    sortByArrival();

    printf("\n================== FORMAT 1 ==================\n");
    printf("Process_ID\tStarting_Time\tFinishing_Time\n");
    printf("==============================================\n");

    while (completed < n) {
        int index = find_next_process(current_time);
        if (index != -1) {
            p[index].start_time = current_time;
            p[index].finish_time = current_time + p[index].burst_time;
            p[index].turnaround_time = p[index].finish_time - p[index].arrival_time;
            p[index].waiting_time = p[index].turnaround_time - p[index].burst_time;
            p[index].done = 1;
            completed++;
            current_time = p[index].finish_time;

            total_turnaround += p[index].turnaround_time;
            total_waiting += p[index].waiting_time;

            printf("%d\t\t%d\t\t%d\n", p[index].pid, p[index].start_time, p[index].finish_time);
        } else {
            current_time++;
        }
    }

    printf("\n================== FORMAT 2 ==================\n");
    printf("Process_ID\tArrival_Time\tBurst_Time\tPriority_Number\tTurnaround_Time\tWaiting_Time\n");
    printf("=====================================================================================\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].priority, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("=====================================================================================\n");
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
}

int main() {
    input();
    priorityScheduling();
    return 0;
}