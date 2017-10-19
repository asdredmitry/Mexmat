#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <cmath>
#include <stack>
void printMatrix(double * matrix,int n);
double norm(int n, double * matrix);
void rotationMatrix(int n, double * matrix);
int n_(int n, double* matrix, double lambda);
void FindValues(int n, double* matrix, double* values, double eps, int & iterations);
#endif // FUNC_H
