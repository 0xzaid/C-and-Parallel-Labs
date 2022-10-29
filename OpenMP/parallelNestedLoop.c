#include <stdio.h>
#define N 5
#define M 4


int main()
{
    int a[M][N] =
        {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}};
    int b[M][N] =
        {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}};
    int c[M][N] = {0};
    int i, j;
#pragma omp parallel for shared(a,b,c) private (j)
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            c[i][j] = a[i][j] * b[i][j];
        }
    }

    printf("Values of C:\n");
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}