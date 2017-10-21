#include "jordan.h"
#include <iostream>
double dabs(double a)
{
    return (a > 0) ? a : -a;
}
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
    printf("\n");
}
void swapStr(double * data, int y1, int y2, int n)
{
    double tmp(0.0);
    for(int x = 0; x < n + 1; x++)
    {
        tmp = data[y1*(n + 1) + x];
        data[y1*(n + 1) + x] = data[y2*(n + 1) + x];
        data[y2*(n + 1) + x] = tmp;
    }
}
void swapCol(double * data,int x1,int x2, int n)
{
    double tmp(0.0);
    for(int y = 0; y < n; y++)
    {
        tmp = data[y*(n + 1) + x1];
        data[y*(n + 1) + x1] = data[y*(n + 1) + x2];
        data[y*(n + 1) + x2] = tmp;
    }
}
void solveMatrix(double * data, int n, double * salvation, int * subs)
{
    for(int y = 0; y < n; y++)
    {
            int maxNum = 0;
            double maxEl = 0;
            for(int i = y; i < n; i++)
            {
                if(maxEl < dabs(data[y*(n + 1) + i]))
                {
                    maxEl = dabs(data[y*(n + 1) + i]);
                    maxNum = i;
                }
            }
            if(!maxEl)
            {
                perror("det Matrix is 0");
                exit(EXIT_FAILURE);
            }
            if(maxNum != y)
            {
                int tmp = subs[y];
                subs[y] = subs[maxNum];
                subs[maxNum] = tmp;
                swapCol(data,y,maxNum,n);
            }
            for(int i = n; i >= y; i--)
                data[y*(n + 1) + i] /= data[y*(n + 1) + y];
           for(int y1 = 0; y1 < n; y1++)
           {
                if(y1 != y)
                {
                    for(int x1 = n; x1 >= y; x1--)
                        data[y1*(n + 1) + x1] -= data[y*(n + 1) + x1]*data[y1*(n + 1) + y];
                }
            }
    }
    for(int i =0; i < n; i++)
        salvation[i] = data[subs[i]*(n + 1) + n];
    printMatrix(data,n);
    for(int i = 0; i < n; i++)
        salvation[subs[i]] = data[i*(n + 1) + n];
}
