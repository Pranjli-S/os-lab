#include <stdio.h>

#define MAX 20

void runFit(const char *title, int mode, int bsize[], int bn, int psize[], int pn) {
    int block[MAX], alloc[MAX];
    for (int i = 0; i < bn; i++) block[i] = bsize[i];

    for (int i = 0; i < pn; i++) {
        alloc[i] = -1;
        int chosen = -1;
        for (int j = 0; j < bn; j++) {
            if (block[j] >= psize[i]) {
                if (mode == 0) { chosen = j; break; }
                if (chosen == -1 ||
                    (mode == 1 && block[j] < block[chosen]) ||
                    (mode == 2 && block[j] > block[chosen])) {
                    chosen = j;
                }
            }
        }
        if (chosen != -1) {
            alloc[i] = chosen;
            block[chosen] -= psize[i];
        }
    }

    printf("\n--- %s ---\n", title);
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < pn; i++) {
        printf("P%d\t\t%d\t\t", i + 1, psize[i]);
        if (alloc[i] != -1) printf("B%d\n", alloc[i] + 1);
        else printf("Not Allocated\n");
    }
}

int main() {
    int bn, pn, bsize[MAX], psize[MAX];

    printf("Enter number of memory blocks: ");
    scanf("%d", &bn);
    printf("Enter sizes of blocks: ");
    for (int i = 0; i < bn; i++) scanf("%d", &bsize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &pn);
    printf("Enter sizes of processes: ");
    for (int i = 0; i < pn; i++) scanf("%d", &psize[i]);

    runFit("First Fit", 0, bsize, bn, psize, pn);
    runFit("Best Fit", 1, bsize, bn, psize, pn);
    runFit("Worst Fit", 2, bsize, bn, psize, pn);
    return 0;
}
