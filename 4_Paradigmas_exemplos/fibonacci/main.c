#include <stdio.h>
#include <stdlib.h>

int fib_recursividade(int n) {
    //                         f(10)
    //             f(9)          +           f(8)
    //       f(8)   +    f(7)           f(7)   +   f(6)
    //    f(7) + f(6)  f(6) + f(5)   f(6) + f(5)  f(5) + f(4)
    //    ...    ...   ...    ...    ...    ...   ...    ...
    
    if (n == 0 || n == 1)
        return n; // caso trivial
    return fib_recursividade(n - 1) + fib_recursividade(n - 2);
}

int fib_prog_dinamica(int n) {
    int *v, resultado;
    v = malloc(sizeof(int) * (n + 1));
    
    v[0] = 0;
    v[1] = 1;
    for (int i = 2; i <= n; i++)
        v[i] = v[i - 1] + v[i - 2];
    
    resultado = v[n];
    free(v);
    return resultado;
}

int main(void) {
    int n = 10;
    //printf("O %d-esimo numero de Fibonacci eh %d\n", n, fib_recursividade(n));
    printf("O %d-esimo numero de Fibonacci eh %d\n", n, fib_prog_dinamica(n));
    return 0; // sucesso
}
