#include <stdio.h>
#include <omp.h>
// must have -openmp flag to compile
void main()
{
#pragma omp parallel
    {
        int i;
        printf("Hello World\n");
#pragma omp for
        for (i = 0; i < 6; i++)
            printf("Iter:%d\n", i);
    }
    printf("GoodBye World\n");
}
