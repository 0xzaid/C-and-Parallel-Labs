#include <mpi.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define COORDINATOR 0

int main(int argc, char* argv[]) {
    double start_time = MPI_Wtime();
    double time = 0.;
    double start_request = 0.;
    double round_trip_time = 0.;
    double time_buffer = 0.;
    int numtasks, rank, rc; 
    int send_buffer = 1; 
    int receive_buffer;
    int mutex_request = 1;
    int mutex_reply = 2;
    int mutex_release = 3;
    int *request_queue;
    int queue_length = 0;
    int num_completed_requests = 0;
    bool mutex_avail = true;

    // Initialise MPI environment
    MPI_Status stat;

    MPI_Init(&argc,
             &argv);
    MPI_Comm_size(MPI_COMM_WORLD,
                  &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,
                  &rank);

    // Dynamically allocate request queue, based on number of tasks
    request_queue = (int*) malloc(numtasks * sizeof(int));

    // Coordinator rank
    if(rank == COORDINATOR) {
        // Listen for requests until all remaining tasks have
        // asked for access to the critical section
        while(num_completed_requests < numtasks - 1) {
            rc = MPI_Recv(&receive_buffer,
                          1,
                          MPI_INT,
                          MPI_ANY_SOURCE,
                          MPI_ANY_TAG,
                          MPI_COMM_WORLD,
                          &stat);

            // If a request has been made and the critical section is
            // available
            if(stat.MPI_TAG == mutex_request && mutex_avail) {
                rc = MPI_Send(&send_buffer,
                              1,
                              MPI_INT,
                              stat.MPI_SOURCE,
                              mutex_reply,
                              MPI_COMM_WORLD);
                mutex_avail = false;
            }
            // If a request has been made but the critical sections is
            // not available
            else if(stat.MPI_TAG == mutex_request && !mutex_avail) {
                queue_length += 1;
                request_queue[queue_length-1] = stat.MPI_SOURCE;
                printf("Rank %i is waiting....\n", stat.MPI_SOURCE);
            }
            // If a process has finished with the critical section
            else if(stat.MPI_TAG == mutex_release) {
                mutex_avail = true;
                queue_length -= 1;
                num_completed_requests += 1;
                for(int process=0; process<queue_length; process++) {
                    request_queue[process] = request_queue[process+1];
                }
            }

            // If there are processes waiting in the queue
            // release the critical section to the next in line
            if(queue_length > 0) {
                rc = MPI_Send(&send_buffer,
                              1,
                              MPI_INT,
                              request_queue[0],
                              mutex_reply,
                              MPI_COMM_WORLD);
                mutex_avail = false;
            }
        }
    } 
    else {
        // Request access to the critical section
        rc = MPI_Send(&send_buffer,
                      1,
                      MPI_INT,
                      COORDINATOR,
                      mutex_request,
                      MPI_COMM_WORLD);
        // Block until we have received access to the
        // critical section
        rc = MPI_Recv(&receive_buffer,
                      1,
                      MPI_INT,
                      COORDINATOR,
                      mutex_reply,
                      MPI_COMM_WORLD,
                      &stat);

        // You might actually do something with the critical
        // section here
        printf("Yay rank %i finally gets a turn\n", rank);

        // Let the coordinator know we have finished with the
        // critical section
        rc = MPI_Send(&send_buffer,
                      1,
                      MPI_INT,
                      COORDINATOR,
                      mutex_release,
                      MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
