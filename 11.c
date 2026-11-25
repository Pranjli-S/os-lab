#include <stdio.h>

#define MAXBLOCKS 30

int main() {
    int choice, nf, disk[MAXBLOCKS] = {0};

    printf("Menu:\n1. Contiguous Allocation\n2. Linked Allocation\n3. Indexed Allocation\nEnter choice: ");
    scanf("%d", &choice);
    printf("Enter number of files: ");
    scanf("%d", &nf);

    if (choice == 1) {
        printf("\n--- Contiguous Allocation ---\n");
        for (int f = 0; f < nf; f++) {
            int start, len, ok = 1;
            printf("File %d - starting block, length: ", f + 1);
            scanf("%d %d", &start, &len);
            if (start < 0 || start + len > MAXBLOCKS) ok = 0;
            for (int i = start; ok && i < start + len; i++) {
                if (disk[i]) { ok = 0; break; }
            }
            if (!ok) {
                printf("Allocation failed: blocks not free/out of range.\n");
                continue;
            }
            for (int i = start; i < start + len; i++) disk[i] = 1;
            printf("File %d allocated blocks %d to %d\n", f + 1, start, start + len - 1);
        }
    } else if (choice == 2) {
        printf("\n--- Linked Allocation ---\n");
        for (int f = 0; f < nf; f++) {
            int len, count = 0;
            printf("File %d - number of blocks: ", f + 1);
            scanf("%d", &len);
            printf("File %d allocated blocks: ", f + 1);
            for (int i = 0; i < MAXBLOCKS && count < len; i++) {
                if (!disk[i]) {
                    disk[i] = 1;
                    printf("%d -> ", i);
                    count++;
                }
            }
            printf("(NULL)\n");
            if (count < len) printf("Warning: disk full, could not allocate all blocks.\n");
        }
    } else if (choice == 3) {
        printf("\n--- Indexed Allocation ---\n");
        for (int f = 0; f < nf; f++) {
            int len, idx = -1, count = 0;
            printf("File %d - number of data blocks needed: ", f + 1);
            scanf("%d", &len);
            for (int i = 0; i < MAXBLOCKS; i++) {
                if (!disk[i]) { idx = i; disk[i] = 1; break; }
            }
            printf("File %d - Index block: %d, Data blocks: ", f + 1, idx);
            for (int i = 0; i < MAXBLOCKS && count < len; i++) {
                if (!disk[i]) {
                    disk[i] = 1;
                    printf("%d ", i);
                    count++;
                }
            }
            printf("\n");
        }
    } else {
        printf("Invalid choice\n");
    }
    return 0;
}
