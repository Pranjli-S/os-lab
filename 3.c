#include <stdio.h>

#define MAX 20

typedef struct {
    int pid, at, bt, pr, ct, tat, wt, rem;
} Process;

void printResult(Process p[], int n) {
    float w = 0, t = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        w += p[i].wt; t += p[i].tat;
    }
    printf("Average Waiting Time    = %.2f\n", w / n);
    printf("Average Turnaround Time = %.2f\n", t / n);
}

int main() {
    int n, ch, q;
    Process p[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d - Arrival Time, Burst Time, Priority: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rem = p[i].bt;
        p[i].ct = 0;
    }

    printf("\nMenu:\n1. FCFS\n2. SJF (Non-preemptive)\n3. Priority (Non-preemptive)\n4. Round Robin\nEnter choice: ");
    scanf("%d", &ch);

    if (ch == 1) {
        int time = 0;
        for (int i = 0; i < n; i++) {
            if (time < p[i].at) time = p[i].at;
            time += p[i].bt;
            p[i].ct = time; p[i].tat = p[i].ct - p[i].at; p[i].wt = p[i].tat - p[i].bt;
        }
    } else if (ch == 2 || ch == 3) {
        int time = 0, done = 0, vis[MAX] = {0};
        while (done < n) {
            int idx = -1, best = 1e9;
            for (int i = 0; i < n; i++) if (!vis[i] && p[i].at <= time) {
                int val = (ch == 2) ? p[i].bt : p[i].pr;
                if (val < best) { best = val; idx = i; }
            }
            if (idx == -1) { time++; continue; }
            time += p[idx].bt;
            p[idx].ct = time; p[idx].tat = p[idx].ct - p[idx].at; p[idx].wt = p[idx].tat - p[idx].bt;
            vis[idx] = 1; done++;
        }
    } else if (ch == 4) {
        int time = 0, done = 0, qu[500], f = 0, r = 0, inq[MAX] = {0};
        printf("Enter time quantum: ");
        scanf("%d", &q);
        for (int i = 0; i < n; i++) if (p[i].at <= time) { qu[r++] = i; inq[i] = 1; }
        while (done < n) {
            if (f == r) {
                time++;
                for (int i = 0; i < n; i++) if (!inq[i] && p[i].rem > 0 && p[i].at <= time) {
                    qu[r++] = i; inq[i] = 1;
                }
                continue;
            }
            int idx = qu[f++];
            int slice = (p[idx].rem < q) ? p[idx].rem : q;
            time += slice;
            p[idx].rem -= slice;
            for (int i = 0; i < n; i++) if (!inq[i] && p[i].rem > 0 && p[i].at <= time && i != idx) {
                qu[r++] = i; inq[i] = 1;
            }
            if (p[idx].rem > 0) {
                qu[r++] = idx;
            } else {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                done++;
                inq[idx] = 0;
            }
        }
    } else {
        printf("Invalid choice\n");
        return 0;
    }

    printResult(p, n);
    return 0;
}
