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
    for (int i = 2; i * i * i * i <= n; i++)
    {
        if (primeArray[i] == true)
        {
            for (int j = i * i; j * j <= n; j += i)
            {
                primeArray[j] = false;
            }
        }
    }
    int k = sqrt(n);
#pragma omp parallel for schedule(dynamic)
    for (int i = 2; i <= k; i++)
    {
        if (primeArray[i])
        {
            int firstMultiple = (m / i);
            if (firstMultiple <= 1)
            {
                firstMultiple = i + i;
            }
            else if (m % i)
            {
                firstMultiple = (firstMultiple * i) + i;
            }
            else
            {
                firstMultiple = (firstMultiple * i);
            }
            for (int j = firstMultiple; j <= n; j += i)
            {
                if (result[j - m])
                    result[j - m] = false;
            }
        }
    }
}