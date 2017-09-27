#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "jordan.h"
double func(int x, int y)
{
    return x+y;
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
double * fillInMatrix(int  n)
{
    double * matrix = new double [n*(n + 1)];
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
    return matrix;
}
int main()
{
    double * matrix(NULL);
    int n(0);
    char yes;
    printf("Read matrix from file?(y/n): ");
    if(!scanf("%c",&yes))
    {
        perror("unexpected input");
        exit(EXIT_FAILURE);
    }
    if(yes == 'y' || yes == 'Y')
    {
        char * name = new char[100];
        memset(name,0, sizeof(char)*100);
        printf("Insert name of file: ");
        scanf("%s",name);
        matrix = readMatrix(name,n);
        delete [] name;
    }
    else if(yes == 'n' || yes == 'N')
    {
        printf("Enter the size of matrix: \n");
        scanf("%d",&n);
        matrix = fillInMatrix(n);
    }
    else
    {
        perror("Unexpected input");
        exit(EXIT_FAILURE);
    }
    printMatrix(matrix,n);
    delete [] matrix;
    return 0;
}
