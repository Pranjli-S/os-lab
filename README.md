# Operating Systems Lab (CEC301 / CSC301)

**Submitted by:** Pranjli Singh  
**Roll No.:** 2472116

C implementations of 11 Operating Systems lab experiments covering process management, POSIX threads, CPU scheduling, process synchronization, deadlock avoidance, memory management, page replacement, disk scheduling, and file allocation.

## List of Programs

| File | Experiment |
| :--- | :--- |
| `01.c` | Introduction to Linux System Calls (`fork()`, `exec()`, `wait()`) |
| `02.c` | Thread Creation and Management using POSIX Threads (`pthreads`) |
| `03.c` | CPU Scheduling Algorithms (FCFS, SJF, Priority, Round Robin) |
| `04.c` | Producer-Consumer Problem using Semaphores |
| `05.c` | Readers-Writers Problem using Semaphores |
| `06.c` | Dining Philosophers Problem using Semaphores |
| `07.c` | Deadlock Avoidance using Banker's Algorithm |
| `08.c` | Contiguous Memory Allocation (First Fit, Best Fit, Worst Fit) |
| `09.c` | Page Replacement Algorithms (FIFO, LRU, Optimal) |
| `10.c` | Disk Scheduling Algorithms (FCFS, SSTF, SCAN, C-SCAN) |
| `11.c` | File Allocation Methods (Contiguous, Linked, Indexed) |

## Compilation & Execution (Linux / WSL)

For standard programs (`01.c`, `03.c`, `07.c`–`11.c`):
```bash
gcc 01.c -o prog1
./prog1
