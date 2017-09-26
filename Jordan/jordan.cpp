#include "jordan.h"
void printMatrix(double * data, int n)
{
    printf("\n");
    for(int y = 0; y < n; y++)
    {
        for(int x = 0; x < n + 1; x++)
        {
            if(x == n)
                printf("    ");
            printf("%lf ",data[y*(n + 1) + x]);
        }
        printf("\n");
    }
}
