#ifndef JORDAN_H
#define JORDAN_H
#include <stdio.h>
void printMatrix(double * data, int n);
void swapStr(double * data, int y1, int y2, int n);
void swapCol(double * data, int x1, int x2, int n);
int solveMatrix(double * data, int n, double * solvation);
#endif // JORDAN_H
