#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    FILE *pInfile;
    float a_coeff, b_coeff, c_coeff, x1, x2, disc;
    float x1r, x1i, x2r, x2i;
    int fileElementCount = 0, constNeg = -1;
    
    int my_rank;
    int p;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (my_rank == 0)
    {
        pInfile = fopen("quad.txt", "r");
        fscanf(pInfile, "%d", &fileElementCount);
    }

    // Broadcast counter
    MPI_Bcast(&fileElementCount, 1, MPI_INT, 0, MPI_COMM_WORLD);
    switch (my_rank) {
        case 0: {

            // read a,b,c before quadratic values
			char a,b,c;
			fscanf(pInfile, "%s %s %s", &a,&b,&c);

            // read file
            for (int i = 0; i < fileElementCount; i++)
            {
                fscanf(pInfile, "%f%f%f", &a_coeff, &b_coeff, &c_coeff);
                disc = pow(b_coeff,2) - (4 * a_coeff * c_coeff);

                
                MPI_Send(&a_coeff, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
                MPI_Send(&b_coeff, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
                MPI_Send(&disc, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
            }
            fclose(pInfile);
            break;
    }
    case 1:
    {
        for (int i = 0; i < fileElementCount; i++)
        {

            // send discrimnant & coefficient to next
            MPI_Recv(&a_coeff, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD,&status);
            MPI_Recv(&b_coeff, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD,&status);
            MPI_Recv(&disc, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD,&status);
            MPI_Send(&disc, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD);
            if (disc >= 0)
            {
                // 1 or 2 roots
                x1 = ((b_coeff * constNeg) + sqrt(disc)) / (2 * a_coeff);
                x2 = ((b_coeff * constNeg) - sqrt(disc)) / (2 *a_coeff);
                MPI_Send(&x1, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD);
                MPI_Send(&x2, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD);
            }
            else
            {
                // no roots
                x1r = (b_coeff * constNeg) / (2 * a_coeff);
                x1i = sqrt(abs(disc)) / (2 * a_coeff);
                x2r = x1r;
                x2i = x1i;
                MPI_Send(&x1r, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD);
                MPI_Send(&x1i, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD);
                MPI_Send(&x2r, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD);
                MPI_Send(&x2i, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD);
            }
        }
        break;
    }

    case 2:
    {
        // output
        FILE *pOutFile = fopen("roots.txt", "w");
        // first line of roots file
        fprintf(pOutFile, "%d\n", fileElementCount);

        // second line of roots file
        fprintf(pOutFile, "x1\tx2\tx1_real\tx1_img\tx2_real\tx2_img\n");

        for (int i = 0; i < fileElementCount; i++)
        {
            MPI_Recv(&disc, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &status);
            if (disc >= 0)
            {
                MPI_Recv(&x1, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(&x2, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &status);
                fprintf(pOutFile, "%.1f\t%.1f\n", x1, x2);
            }
            else
            {
                MPI_Recv(&x1r, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(&x1i, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(&x2r, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(&x2i, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &status);
                fprintf(pOutFile,"\t\t\t%.1f\t%.1f\t%.1f\t%.1f\n", x1r, x1i, x2r,x2i);
            }
        }
        fclose(pOutFile);
        break;
    }
    }
    MPI_Finalize();
    return 0;
}