#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "jordan.h"
double func(int x, int y)
{
    return x*y;
}
double * readMatrix(char * name, int & n)
{
    FILE * file = fopen(name,"r");
    if(!file)
    {
        perror("cannot open file");
        exit(EXIT_FAILURE);
    }
    int res = fscanf(file,"%d",&n);
    if(!res || res == EOF)
    {
        perror("error during reading file");
        exit(EXIT_FAILURE);
    }
    double * data = new double[n*(n + 1)];
    for(int y = 0; y < n; y++)
    {
        for(int x = 0; x < n + 1; x++)
        {
            res = fscanf(file,"%lf",data + y*(n + 1) + x);
            if(!res || res == EOF)
            {
                perror("error during reading file");
                fclose(file);
                delete [] data;
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(file);
    return data;
}
int main(int argc, char ** argv)
{
    double * matrix;
    int n;
    if(argc == 1)
    {
        scanf("%d",&n);
        matrix = new double [n*(n + 1)];
        memset(matrix,0,sizeof(double)*n*(n+ 1));
        for(int y = 0; y < n; y++)
        {
            for(int x = 0; x < n; x++)
            {
                matrix[y*(n + 1) + x] = func(x,y);
                if(!(x%2))
                    matrix[y*(n + 1) + n]+= matrix[y*(n + 1) + x];
            }
        }
    }
    else if(argc == 2)
        matrix = readMatrix(argv[1],n);
    printMatrix(matrix,n);
    return 0;
}
