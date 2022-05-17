#include <stdio.h>

long exponenciacao_n(long m, long n) {
    long res = 1;
    for (long i = 0; i < n; i++)
        res *= m;
    return res;
}

long exponenciacao_logn(long m, long n) {
    // m^n = (m * m)^(n/2) , se n eh par
    // m^n = ((m * M)^(n/2)) * m, se n eh impar

    // Recorrencia
    // T(0) = c
    // T(n) = c + T(n / 2), para n > 0

    if (n == 0)
        return 1;  // caso trivial
    if (n % 2 == 0)
        return exponenciacao_logn(m * m, n / 2);  // n eh par
    return exponenciacao_logn(m * m, n / 2) * m;  // n em impar
}

int main(void) {
    long m = 2, n = 5;

    printf("%ld elevado a %ld eh: %ld\n", m, n, exponenciacao_logn(m, n));
    return 0;
}
