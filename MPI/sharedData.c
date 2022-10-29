#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, p;

    // initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    int val = -1;

    do
    {
        if (rank == 0)
        {
            printf("Enter a number > 0: ");
            fflush(stdout);
            scanf("%d", &val);
        }
        // broadcast val to all processes
        MPI_Bcast(&val, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("processors: %d, Received value: %d\n ", rank, val);
        fflush(stdout);
    } while (val > 0);
        MPI_Finalize();
    return 0;
}
