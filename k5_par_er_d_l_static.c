#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <omp.h>
// todo: guess the size
#define X 64

int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    bool *result = (bool *)malloc((n - m + 1) * sizeof(bool));
    memset(result, true, (n - m + 1) * sizeof(bool));
    bool *primeArray = (bool *)malloc((sqrt(n) + 1) * sizeof(bool));
    memset(primeArray, true, (sqrt(n) + 1) * sizeof(bool));
    int blockSize = X;
    int numberOfBlocks = (n - m) / blockSize;
    if ((n - m) % blockSize != 0)
    {
        numberOfBlocks++;
    }
#pragma omp parallel for schedule(static, 1024*8)
    for (int i = 0; i < numberOfBlocks; i++)
    {
        int low = m + i * blockSize;
        int high = m + i * blockSize + blockSize;
        if (high > n)
        {
            high = n;
        }
        for (int j = 2; j * j <= high; j++)
        {
            if (primeArray[j])
            {
                int firstMultiple = (low / j);
                if (firstMultiple <= 1)
                {
                    firstMultiple = j + j;
                }
                else if (low % j)
                {
                    firstMultiple = (firstMultiple * j) + j;
                }
                else
                {
                    firstMultiple = (firstMultiple * j);
                }
                for (int k = firstMultiple; k <= high; k += j)
                {
                    result[k - m] = false;
                }
            }
        }
    }
}