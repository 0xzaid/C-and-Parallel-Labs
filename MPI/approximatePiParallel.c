#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

static long N = 100000000;
int main(int argc, char *argv[])
{
    int i, rank, p, val;
    double sum = 0.0;
    double piVal;
    struct timespec start, end;
    double time_taken;

    // initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (rank == 0)
    {
        printf("Enter N: ");
        fflush(stdout);
        scanf("%d", &val);
    }
     MPI_Bcast(&val, 1, MPI_INT, 0, MPI_COMM_WORLD);
     printf("processors: %d, Received value: %d\n ", rank, val);
    fflush(stdout);
    // Get current clock time.
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (i = 0; i < N; i++)
    {
        sum += 4.0 / (1 + pow((2.0 * i + 1.0) / (2.0 * N), 2));
    }
    piVal = sum / (double)N;

    float global_res;
    MPI_Reduce(&piVal, &global_res, 1, MPI_FLOAT, MPI_SUM, (p-1),
               MPI_COMM_WORLD);

    // Get the clock current time again
    // Subtract end from start to get the CPU time used.

    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) *
                 1e-9;
    printf("Calculated Pi value (Parallel-AlgoI) = %12.9f\n",
           piVal);
    printf("Overall time (s): %lf\n", time_taken); // ts
    fflush(stdout);
    MPI_Finalize();
    return 0;
}
