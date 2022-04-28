#define TAM 10
#define repeticoes 1
#include <math.h>    // pow
#include <stdio.h>   // printf
#include <stdlib.h>  // random
#include <time.h>    // t_clock, clock(), ...

long soma_subsequencias_n3(int v[], long n) {
    long maior = 0, soma;
    for (long ini = 0; ini < n; ini++)  // ini: inicio da subsequencia
        for (long fim = ini; fim < n; fim++) {
            soma = 0;
            for (long i = ini; i <= fim; i++)  // varre a subsequencia
                soma += v[i];
            if (soma > maior)
                maior = soma;
        }
    return maior;
}

long soma_subsequencias_n2(int v[], long n) {
    long maior = 0, soma;
    for (long ini = 0; ini < n; ini++) {  // ini: inicio da subsequencia
        soma = 0;
        for (long fim = ini; fim < n; fim++) {  // fim: final da subsequencia
            soma += v[fim];
            if (soma > maior)
                maior = soma;
        }
    }
    return maior;
}

int main(void) {
    // int v[] = {-2, 11, -4, 13, -5, -2};

    int *v;
    for (int i = 1; pow(10, i) <= TAM; i++) {
        // cria vetor
        v = malloc(pow(10, i) * sizeof(int));

        // insere e imprime valores
        for (long j = 0; j < pow(10, i); j++) {
            v[j] = random() % TAM;
            if (v[j] % 2 == 0)
                v[j] *= -1;  // pares sao transformados em negativos

            printf("%d ", v[j]);
        }
        printf("\n");

        // descobre e imprime a maior soma de subsequencias
        printf("A maior soma eh: %ld\n", soma_subsequencias_n2(v, (long)pow(10, i)));

        // destroi vetor
        free(v);
    }

    return 0;  // sucesso
}
