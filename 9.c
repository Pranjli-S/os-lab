#include <stdio.h>

#define MAXFRAMES 10
#define MAXPAGES 50

int isPresent(int frames[], int nf, int page) {
    for (int i = 0; i < nf; i++)
        if (frames[i] == page) return 1;
    return 0;
}

int main() {
    int ref[MAXPAGES], n, nf, frames[MAXFRAMES];

    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &ref[i]);
    printf("Enter number of frames: ");
    scanf("%d", &nf);

    // 1. FIFO
    int ptr = 0, fifo = 0;
    for (int i = 0; i < nf; i++) frames[i] = -1;
    for (int i = 0; i < n; i++) {
        if (!isPresent(frames, nf, ref[i])) {
            frames[ptr] = ref[i];
            ptr = (ptr + 1) % nf;
            fifo++;
        }
    }

    // 2. LRU
    int lastUsed[MAXFRAMES], lru = 0;
    for (int i = 0; i < nf; i++) { frames[i] = -1; lastUsed[i] = -1; }
    for (int i = 0; i < n; i++) {
        int pos = -1;
        for (int j = 0; j < nf; j++)
            if (frames[j] == ref[i]) { pos = j; break; }
        if (pos != -1) {
            lastUsed[pos] = i;
        } else {
            int idx = 0;
            for (int j = 1; j < nf; j++)
                if (lastUsed[j] < lastUsed[idx]) idx = j;
            frames[idx] = ref[i];
            lastUsed[idx] = i;
            lru++;
        }
    }

    // 3. Optimal
    int opt = 0;
    for (int i = 0; i < nf; i++) frames[i] = -1;
    for (int i = 0; i < n; i++) {
        if (isPresent(frames, nf, ref[i])) continue;
        opt++;
        int empty = -1;
        for (int j = 0; j < nf; j++)
            if (frames[j] == -1) { empty = j; break; }
        if (empty != -1) { frames[empty] = ref[i]; continue; }

        int replaceIdx = 0, farthest = -1;
        for (int j = 0; j < nf; j++) {
            int k = i + 1;
            while (k < n && ref[k] != frames[j]) k++;
            if (k > farthest) { farthest = k; replaceIdx = j; }
        }
        frames[replaceIdx] = ref[i];
    }

    printf("\nFIFO Page Faults    = %d\n", fifo);
    printf("LRU Page Faults     = %d\n", lru);
    printf("Optimal Page Faults = %d\n", opt);
    return 0;
}
