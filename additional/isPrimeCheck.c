#include <stdio.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        if (is_prime(n))
            printf("%d is a prime number.\n", n);
        else{
            printf("%d is not a prime number.\n", n);
            break;
        }
        
    }
    printf("All good\n");
    return 0;
}

// ./plikwyj.out 100000 3 | ./verify_prime USAGE