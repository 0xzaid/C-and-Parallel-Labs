#include <stdio.h>
#include "mpi.h"

// Compile with: mpicc hello.c –o hello-mp
// Execute with: mpirun -np 2 hello-mp
int main(int argc, char *argv[])
{
    int numprocs, rank, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    // initializes MPI execution environment 
    MPI_Init(&argc, &argv);
    // Determines the number of processes in the group associated with a communicator
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    // Determines the rank of the calling process within the communicator. 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // returns the processor name. Also returns the length of the name
    MPI_Get_processor_name(processor_name, &namelen);
    // Print
    printf("Process %d on %s out of %d\n", rank, processor_name, numprocs);
    // Terminates MPI execution environment
    MPI_Finalize();
}