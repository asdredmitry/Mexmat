#ifndef JORDAN_H
#define JORDAN_H
#include <stdio.h>
#include <stdlib.h>
double dabs(double a);
void printMatrix(double * data, int n);
void swapStr(double * data, int y1, int y2, int n);
void swapCol(double * data, int x1, int x2, int n);
void solveMatrix(double * data, int n, double * solvation,int * subs);
#endif // JORDAN_H
