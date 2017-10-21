#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "jordan.h"
#include <time.h>
#include <cmath>
double func(int x, int y)
{
    return rand()%100000;
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
double norm(double * vector,int n)
{
    double max(0.0);
    for(int i = 0; i < n; i++)
        max = (max > dabs(vector[i])) ? max : dabs(vector[i]);
    return max;
}
double normFunc(double * matrix, double * answer,int n)
{
    double * delta = new double [n];
    memset(delta,0,n*sizeof(double));
    for(int y = 0; y < n; y++)
    {
        for(int x = 0; x < n; x++)
            delta[y] += answer[x] * matrix[y*(n + 1) + x];
    }
    for(int y = 0; y < n; y++)
        delta[y] -= matrix[y*(n + 1) + n];
    double norma = norm(delta,n);
    delete [] delta;
    return norma;
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
    srand(time(0));
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
        double * salvation = new double [n];
        memset(salvation,0,sizeof(double) *n);
        int * subs = new int[n];
       // printMatrix(matrix,n);
        for(int i = 0; i < n; i++)
            subs[i] = i;
        solveMatrix(matrix,n,salvation,subs);
        printf("answer = (");
        for(int i = 0; i < n; i++)
            printf("%lf " , salvation[i]);
        printf(")\n");
        delete [] matrix;
        matrix = readMatrix(name,n);
        printf(" norma = %lf ", normFunc(matrix,salvation,n));
        delete [] name;
        delete [] salvation;
        delete [] matrix;
        delete [] subs;
    }
    else if(yes == 'n' || yes == 'N')
    {
        printf("Enter the size of matrix: \n");
        scanf("%d",&n);
        matrix = fillInMatrix(n);
        double * salvation = new double [n];
        memset(salvation,0,sizeof(double) *n);
        int * subs = new int[n];
        for(int i = 0; i < n; i++)
            subs[i] = i;
        //printMatrix(matrix,n);
	timespec  begin, end;
	clock_gettime(CLOCK_REALTIME,&begin);
        solveMatrix(matrix,n,salvation,subs);
	clock_gettime(CLOCK_REALTIME, &end);
        printf("answer = (");
        for(int i = 0; i < n; i++)
            printf(" %lf ",salvation[i]);
        printf(")\n");
    printf(" time - %lf  \n" , end.tv_sec - begin.tv_sec + (end.tv_nsec - begin.tv_nsec)/1000000000.0);
        for(int i = 0; i < n; i++)
            salvation[i] -= !(i%2);
        printf("norma = %lf \n" , norm(salvation,n));
        delete [] salvation;
        delete [] matrix;
        delete [] subs;
    }
    else
    {
        perror("Unexpected input");
        exit(EXIT_FAILURE);
    }
    printf("\n");
    return 0;
}
