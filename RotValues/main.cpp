#include <iostream>
#include <cmath>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
double func(int i,int j,int n)
{
    if (i == n - 1)
        return j + 1.0;
    else if (j == n - 1)
        return i + 1.0;
    else
        return (double)(i == j);
}
double * readMatrix(char * name,int & n)
{
    FILE * file = fopen(name,"r");
    if(!file)
    {
        perror("cannot open file");
        exit(EXIT_FAILURE);
    }
    if(!fscanf(file,"%d",&n))
    {
        perror("cannot read matrix size");
        exit(EXIT_FAILURE);
    }
    double * matrix = new double [n*n];
    for(int y = 0; y < n; y++)
    {
        for(int x = 0; x < n; x++)
        {
            if(!fscanf(file,"%lf",matrix + y*n + x))
            {
                perror("cannot read data");
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(file);
    return matrix;
}
void fillInMatrix(double * matrix,int n)
{
    for(int y = 0; y < n; y++)
    {
        for(int x = 0; x < n; x++)
        {
            matrix[y*n + x] = func(x,y,n);
        }
    }
}
int main()
{
    printf("Read matrix from file?[y/n]");
    char readFromFile(0);
    scanf("%c",&readFromFile);
     double eps = 1e-10;
     double * matrix = NULL;
     int n(0);
    if(readFromFile == 'y' || readFromFile == 'Y')
    {
        printf("Enter the name of the file \n");
        char * name = new char [1000];
        memset(name,0,sizeof(char)*1000);
        scanf("%s",name);
        matrix = readMatrix(name,n);\
        delete [] name;
    }
    else if(readFromFile == 'n' || readFromFile == 'N')
    {
        printf("Enter size of matrix:\n");
        scanf("%d",&n);
        matrix = new double [n*n];
        fillInMatrix(matrix,n);
    }
    else
    {
        perror("Invalid input");
        exit(EXIT_FAILURE);
    }
    printMatrix(matrix,n);
    double * values = new double[n];
    int amountOperations(0);\
    FindValues(n,matrix,values,eps,amountOperations);
    printf(" \n Values: \n");
    for(int i = 0;i < n; i++)
    {
        printf("%f ",values[i]);
    }
    printf("\n iterations - %d ",amountOperations);
    double inv1 = 0.0;
    double inv2 = 0.0;
    for (int i = 0;  i < n; ++i)
    {
        inv1 -= matrix[i * n + i];
        for (int j = 0; j < n; ++j)
            inv2 -= matrix[i * n + j] * matrix[j * n + i];
    }
    for (int i = 0; i < n; ++i)
    {
        inv1 += values[i];
        inv2 += values[i] * values[i];
    }
    printf("\n delta traces - %g \n",inv1);
    printf("x_i^2 - a_ij*a_ji - %g \n",inv2);
    delete [] matrix;
    delete [] values;
    return 0;
}
