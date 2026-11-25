#include <stdio.h>

#define P 5
#define R 3

int available[R], maximum[P][R], allocation[P][R], need[P][R];

int isSafe(int safeSeq[]) {
    int work[R], finish[P] = {0}, count = 0;
    for (int j = 0; j < R; j++) work[j] = available[j];

    while (count < P) {
        int found = 0;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[i][j] > work[j]) break;
                if (j == R) {
                    for (int k = 0; k < R; k++) work[k] += allocation[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int main() {
    printf("Enter available resources of each type (%d types): ", R);
    for (int j = 0; j < R; j++) scanf("%d", &available[j]);

    printf("Enter Maximum matrix (%d processes x %d resources):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) scanf("%d", &maximum[i][j]);

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }

    int safeSeq[P];
    if (isSafe(safeSeq)) {
        printf("\nSystem is in a SAFE state.\nSafe sequence: ");
        for (int i = 0; i < P; i++) printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state.\n");
    }

    int pid, req[R];
    printf("\nEnter process number requesting resources: ");
    scanf("%d", &pid);
    printf("Enter request vector (%d values): ", R);
    for (int j = 0; j < R; j++) scanf("%d", &req[j]);

    for (int j = 0; j < R; j++) {
        if (req[j] > need[pid][j]) {
            printf("Error: process has exceeded its maximum claim.\n");
            return 0;
        }
        if (req[j] > available[j]) {
            printf("Request denied: not enough resources available.\n");
            return 0;
        }
    }

    for (int j = 0; j < R; j++) {
        available[j] -= req[j];
        allocation[pid][j] += req[j];
        need[pid][j] -= req[j];
    }

    if (isSafe(safeSeq)) printf("Request can be granted safely.\n");
    else {
        for (int j = 0; j < R; j++) {
            available[j] += req[j];
            allocation[pid][j] -= req[j];
            need[pid][j] += req[j];
        }
        printf("Request denied: would lead to an unsafe state.\n");
    }
    return 0;
}
