#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    bool *result = (bool *)malloc((n - m + 1) * sizeof(bool));
    memset(result, true, (n - m + 1) * sizeof(bool));
    bool *primeArray = (bool *)malloc((sqrt(n) + 1) * sizeof(bool));
    memset(primeArray, true, (sqrt(n) + 1) * sizeof(bool));
    for (int i = 2; i * i <= n; i++)
    {
        for (int j = 2; j * j <= i; j++)
        {
            if (primeArray[j] == true && i % j == 0)
            {
                primeArray[i] = false;
                break;
            }
        }
    }
    for (int i = m; i <= n; i++)
    {
        for (int j = 2; j * j <= i; j++)
        {
            if (primeArray[j] == true && i % j == 0)
            {
                result[i - m] = false;
                break;
            }
        }
    }
}