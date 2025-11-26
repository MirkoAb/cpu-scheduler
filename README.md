# CPU Scheduling Simulator (C Project)

This project is an Operating System CPU Scheduling Simulator written in C.

It implements four classic CPU scheduling algorithms:
- First-Come-First-Served (FCFS)
- Shortest Job First (SJF)
- Priority Scheduling
- Round Robin (RR, Time Quantum = 2)

The simulator demonstrates:
- Step-by-step CPU timeline
- Order of execution
- Burst time execution slices (RR)
- Completion time of each process
- Waiting time
- Turnaround time
- Summary results table for each algorithm

---

## How the Program Works

The user enters:
- Number of processes  
- Burst Time for each process  
- Priority (lower number = higher priority)

Then the program automatically runs all algorithms:
1. FCFS  
2. SJF  
3. Priority Scheduling  
4. Round Robin  

For each algorithm, the simulator prints:
- Timeline (example: Time 0 -> 3 : P1 running)
- Completion time of each process  
- Waiting time  
- Turnaround time  
- A formatted summary table

---

## How to Compile and Run

```bash
# Linux / macOS
gcc cpu_scheduler.c -o cpu_scheduler
./cpu_scheduler

# Windows (MinGW)
gcc cpu_scheduler.c -o cpu_scheduler.exe
cpu_scheduler.exe
```

---

## Project Files

| File | Description |
|------|-------------|
| cpu_scheduler.c | Main C implementation of all scheduling algorithms |
| README.md | Project description and run instructions |

---

## Example Output Table

```
PID   Burst   Priority   Waiting   Turnaround
P1      5        2          0           5
P2      3        1          5           8
P3      8        3          8          16
```

---



## Purpose

This project demonstrates CPU process scheduling in an operating system.  
It is intended for OS simulation:
- Scheduling algorithms  
- Process waiting time  
- CPU allocation  
- Turnaround time calculation  

---

## Author Mirjalol Abdujalilov
OS Simulation Coursework Project  
Implemented in C
