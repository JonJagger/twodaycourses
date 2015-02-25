#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

int func(void * arg)
{
    int i = *(int*)arg;
    printf("%d\n", i);
    return i;
}

int main(void)
{
    size_t n_threads = 20;
    struct { thrd_t t; int n; int r; } threads[n_threads];

    for (size_t i = 0; i < n_threads; i++) {
        threads[i].n = i;
        if (thrd_create(&threads[i].t, func, &threads[i].n) != thrd_success) {
            perror("Failed to create thread");
            exit(-1);
        }
    }

    for (size_t i = 0; i < n_threads; i++) {
        if (thrd_join(threads[i].t, &threads[i].r) != thrd_success) {
            perror("Failed to join thread");
            exit(-1);
        }
        printf("i = %zu, n = %zu, r = %d\n", i, threads[i].n, threads[i].r);
    }
}
