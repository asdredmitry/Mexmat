#include "func.h"
void printMatrix(double * matrix,int n)
{
    if(n > 10)
        n = 10;
    for(int y = 0; y < n; y++)
    {
        printf("\n");
        for(int  x = 0; x < n; x++)
        {
            printf("%lf ",matrix[y*n + x]);
        }
    }
}
double norm(int n, double * matrix)
{
    double res = 0.0;
    for(int y = 0; y < n; y++)
    {
        double tmp = 0.0;
        for(int x = 0; x < n; x++)
        {
            tmp += fabs(matrix[y*n + x]);
            if(res < tmp)
                res = tmp;
        }
    }
    return res;
}
void rotationMatrix(int n, double *matrix)
{
        for (int i = 1; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                double x = matrix[i * n + i - 1];
                double y = matrix[j * n + i - 1];
                if (fabs(y) < 1e-100)
                    continue;
                double r = sqrt(x * x + y * y);
                if (r < 1e-100)
                    continue;
                double cos = x / r;
                double sin = -y / r;
                matrix[i * n + i - 1] = matrix[(i - 1) * n + i] = r;
                matrix[j * n + i - 1] = matrix[(i - 1) * n + j] = 0.0;
                for (int k = i + 1; k < n; ++k)
                {
                    if (k == j)
                        continue;
                    x = matrix[i * n + k];
                    y = matrix[j * n + k];
                    matrix[k * n + i] = matrix[i * n + k] = x * cos - y * sin;
                    matrix[k * n + j] = matrix[j * n + k] = x * sin + y * cos;
                }
                x = matrix[i * n + i];
                y = matrix[j * n + j];
                r = matrix[i * n + j];
                double s = matrix[j * n + i];
                double a_ii = x * cos - s * sin;
                double a_ji = x * sin + s * cos;
                double a_ij = r * cos - y * sin;
                double a_jj = r * sin + y * cos;
                matrix[i * n + i] = a_ii * cos - a_ij * sin;
                matrix[j * n + i] = a_ii * sin + a_ij * cos;
                matrix[i * n + j] = matrix[j * n + i];
                matrix[j * n + j] = a_ji * sin + a_jj * cos;
            }
        }
}
int n_(int n, double* matrix, double lambda)
{
    double x = matrix[0 * n + 0] - lambda;
    double y = 1.0;
    int res = x < 0.0 ? 1 : 0;

    for (int i = 1; i < n; ++i)
    {
        double a_k = matrix[i * n + i] - lambda;
        double b_k1 = matrix[i * n + i - 1];

        double tmp = fabs(b_k1 * b_k1 * y);

        if (fabs(x) > tmp)
            tmp = fabs(x);

        if (tmp < 1e-50)
            tmp = 1e-15;

        double gamma = 1e15 / tmp;
        double u = gamma * (a_k * x - b_k1 * b_k1 * y);
        double v = gamma * x;

        if (u * x < 0.0)
            ++res;

        x = u;
        y = v;
    }
    return res;
}
void FindValues(int n, double* matrix, double * values, double eps, int & iterations)
{
    int j;
    int count;
    double currentMiddle;
    rotationMatrix(n, matrix);
    double right = norm(n, matrix) + 1e-10;
    double left = -right;
    int i = 0;
    double currentLeft = left;
    double currentRight = right;
    while (i < n)
    {
        while (currentRight - currentLeft > eps)
        {
            currentMiddle = 0.5 * (currentLeft + currentRight);
            if (n_(n, matrix, currentMiddle) < i + 1)
                currentLeft = currentMiddle;
            else
                currentRight = currentMiddle;
            ++iterations;
        }
        currentMiddle = 0.5 * (currentLeft + currentRight);
        count = n_(n, matrix, currentRight) - n_(n, matrix, currentLeft);
        for (j = 0; j < count; ++j)
            values[i + j] = currentMiddle;
        i += count;
        currentLeft = currentMiddle;
        currentRight = right;
    }
}
