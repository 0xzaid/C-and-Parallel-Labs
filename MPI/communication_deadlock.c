#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int numtasks, rank, rc; 
    int send_buffer = 1; 
    int receive_buffer;
    int message_tag = 1;
    int destination = -1;
    int source = -1;

    // Initialise MPI environment
    MPI_Status stat;

    MPI_Init(&argc,
             &argv);
    MPI_Comm_size(MPI_COMM_WORLD,
                  &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,
                  &rank);

    // Send message to the next process
    destination = (rank + 1) % numtasks;
    // Receive message from the previous process
    source = (rank - 1) % numtasks;
    if(source < 0) source += numtasks;

    // Block until we receive a message from 
    // neighbour process
    printf("Rank %i is waiting for a message from %i\n", rank, source);
    rc = MPI_Recv(&receive_buffer,
                  1,
                  MPI_INT,
                  source,
                  message_tag,
                  MPI_COMM_WORLD,
                  &stat);
    printf("Yay! Rank %i received a message from %i\n", rank, source);
    rc = MPI_Send(&send_buffer,
                  1,
                  MPI_INT,
                  destination,
                  message_tag,
                  MPI_COMM_WORLD);

    MPI_Finalize();

    return 0;
}