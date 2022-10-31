#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STEPSIZE 0.0001

double definiteIntegral(double x, double y);

int main(int argc, char *argv[])
{

    // initialize variables
    double x, y, total;
    int rank, size;

    // initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double range = 1.0 / size;
    double start = rank * range;
    double end = start + range;
    double subtotal = 0;

    for (x = start; x < end; x += STEPSIZE)
    {
        for (y = 0; y < 1; y += STEPSIZE)
        {
            subtotal += STEPSIZE * STEPSIZE * definiteIntegral(x + 0.5 * STEPSIZE, y + 0.5 * STEPSIZE);
        }
    }

    MPI_Reduce(&subtotal, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Total volume = %f\n", total);
        MPI_Finalize();
        return 0;
    }
}

// compute the definite integral
double definiteIntegral(double x, double y)
{
    return pow(x + y, 2) / (2 * y + 0.1);
}