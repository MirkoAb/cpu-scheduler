#include <stdio.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2

typedef struct {
    int pid;
    int burst;
    int priority;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
} Process;

// ===================================================
// Utility functions
// ===================================================
void copy(Process src[], Process dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
        dest[i].remaining = src[i].burst;
    }
}

void computeTimes(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].completion;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
}

void printTable(Process p[], int n, const char *title) {
    printf("\n================ %s ================\n", title);
    printf("PID\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].burst, p[i].priority,
               p[i].waiting, p[i].turnaround);
    }
    printf("=====================================================\n");
}

// ===================================================
// FCFS Scheduling
// ===================================================
void fcfs(Process processes[], int n) {
    Process p[MAX_PROCESSES];
    copy(processes, p, n);

    int time = 0;

    printf("\n\n========== FCFS Scheduling ==========\n");
    for (int i = 0; i < n; i++) {
        printf("Time %d -> %d : P%d running\n",
               time, time + p[i].burst, p[i].pid);

        time += p[i].burst;
        p[i].completion = time;
    }

    computeTimes(p, n);
    printTable(p, n, "FCFS");
}

// ===================================================
// Priority Scheduling (non-preemptive)
// ===================================================
void priorityScheduling(Process processes[], int n) {
    Process p[MAX_PROCESSES];
    int finished[MAX_PROCESSES] = {0};

    copy(processes, p, n);

    int time = 0;
    int done = 0;

    printf("\n\n========== Priority Scheduling ==========\n");

    while (done < n) {
        int idx = -1;
        int best = 9999;

        for (int i = 0; i < n; i++) {
            if (!finished[i] && p[i].priority < best) {
                best = p[i].priority;
                idx = i;
            }
        }

        printf("Time %d -> %d : P%d running (priority %d)\n",
               time, time + p[idx].burst, p[idx].pid, p[idx].priority);

        time += p[idx].burst;
        p[idx].completion = time;
        finished[idx] = 1;
        done++;
    }

    computeTimes(p, n);
    printTable(p, n, "Priority Scheduling");
}

// ===================================================
// SJF Scheduling (non-preemptive)
// ===================================================
void sjf(Process processes[], int n) {
    Process p[MAX_PROCESSES];
    int finished[MAX_PROCESSES] = {0};

    copy(processes, p, n);

    int time = 0;
    int done = 0;

    printf("\n\n========== SJF Scheduling ==========\n");

    while (done < n) {
        int idx = -1;
        int bestBurst = 9999;

        for (int i = 0; i < n; i++) {
            if (!finished[i] && p[i].burst < bestBurst) {
                bestBurst = p[i].burst;
                idx = i;
            }
        }

        printf("Time %d -> %d : P%d running (burst %d)\n",
               time, time + p[idx].burst, p[idx].pid, p[idx].burst);

        time += p[idx].burst;
        p[idx].completion = time;
        finished[idx] = 1;
        done++;
    }

    computeTimes(p, n);
    printTable(p, n, "Shortest Job First");
}

// ===================================================
// Round Robin
// ===================================================
void roundRobin(Process processes[], int n) {
    Process p[MAX_PROCESSES];
    copy(processes, p, n);

    int time = 0;
    int done = 0;

    printf("\n\n========== Round Robin (Q = %d) ==========\n", TIME_QUANTUM);

    while (done < n) {
        int progress = 0;

        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                progress = 1;

                int exec = (p[i].remaining > TIME_QUANTUM)
                           ? TIME_QUANTUM : p[i].remaining;

                printf("Time %d -> %d : P%d running (slice = %d)\n",
                       time, time + exec, p[i].pid, exec);

                p[i].remaining -= exec;
                time += exec;

                if (p[i].remaining == 0) {
                    p[i].completion = time;
                    done++;
                }
            }
        }

        if (!progress) break;
    }

    computeTimes(p, n);
    printTable(p, n, "Round Robin");
}

// ===================================================
// Main
// ===================================================
int main() {
    int n;

    Process processes[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter Burst Time and Priority for each process:\n");

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nProcess P%d:\n", i + 1);

        printf("  Burst Time: ");
        scanf("%d", &processes[i].burst);

        printf("  Priority (lower = higher priority): ");
        scanf("%d", &processes[i].priority);
    }

    fcfs(processes, n);
    sjf(processes, n);
    priorityScheduling(processes, n);
    roundRobin(processes, n);

    return 0;
}