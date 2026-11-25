#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int abs_diff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, head, diskSize, req[MAX];

    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size (max cylinder + 1): ");
    scanf("%d", &diskSize);

    // 1. FCFS
    int fcfs = 0, cur = head;
    for (int i = 0; i < n; i++) {
        fcfs += abs_diff(cur, req[i]);
        cur = req[i];
    }

    // 2. SSTF
    int sstf = 0, visited[MAX] = {0};
    cur = head;
    for (int count = 0; count < n; count++) {
        int idx = -1, best = 1e9;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && abs_diff(cur, req[i]) < best) {
                best = abs_diff(cur, req[i]);
                idx = i;
            }
        }
        visited[idx] = 1;
        sstf += best;
        cur = req[idx];
    }

    // Sort requests with head for SCAN & C-SCAN
    int arr[MAX + 2];
    for (int i = 0; i < n; i++) arr[i] = req[i];
    arr[n] = head;
    qsort(arr, n + 1, sizeof(int), cmp);

    int pos = 0;
    for (int i = 0; i <= n; i++) {
        if (arr[i] == head) { pos = i; break; }
    }

    // 3. SCAN (moving towards higher cylinders first)
    int scan = 0;
    cur = head;
    for (int i = pos + 1; i <= n; i++) {
        scan += abs_diff(cur, arr[i]);
        cur = arr[i];
    }
    scan += abs_diff(cur, diskSize - 1);
    cur = diskSize - 1;
    for (int i = pos - 1; i >= 0; i--) {
        scan += abs_diff(cur, arr[i]);
        cur = arr[i];
    }

    // 4. C-SCAN (moving towards higher cylinders, then jumping to 0)
    int cscan = 0;
    cur = head;
    for (int i = pos + 1; i <= n; i++) {
        cscan += abs_diff(cur, arr[i]);
        cur = arr[i];
    }
    cscan += abs_diff(cur, diskSize - 1);
    cscan += (diskSize - 1);
    cur = 0;
    for (int i = 0; i < pos; i++) {
        cscan += abs_diff(cur, arr[i]);
        cur = arr[i];
    }

    printf("\nFCFS   total head movement = %d\n", fcfs);
    printf("SSTF   total head movement = %d\n", sstf);
    printf("SCAN   total head movement = %d\n", scan);
    printf("C-SCAN total head movement = %d\n", cscan);
    return 0;
}
