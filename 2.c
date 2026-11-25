#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

typedef struct {
    int start, end;
    long sum;
} PartialSum;

void *sumArray(void *arg) {
    PartialSum *p = (PartialSum *)arg;
    p->sum = 0;
    for (int i = p->start; i < p->end; i++) p->sum += i;
    printf("Thread %ld: sum[%d..%d) = %ld\n",
           pthread_self() % 100000, p->start, p->end, p->sum);
    pthread_exit(NULL);
}

int main() {
    pthread_t th[NUM_THREADS];
    PartialSum d[NUM_THREADS];
    int n = 1000000, chunk = n / NUM_THREADS;
    long total = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        d[i].start = i * chunk;
        d[i].end = (i == NUM_THREADS - 1) ? n : (i + 1) * chunk;
        pthread_create(&th[i], NULL, sumArray, &d[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(th[i], NULL);
        total += d[i].sum;
    }
    printf("Total sum (0 to %d) computed using %d threads = %ld\n",
           n - 1, NUM_THREADS, total);
    return 0;
}
