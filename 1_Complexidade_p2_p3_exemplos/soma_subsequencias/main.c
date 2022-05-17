#define TAM 10
#define repeticoes 3
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

long soma_subsequencias_nlogn_rec(int v[], long ini, long fim) {
    long meio, soma;
    long maior_inf, maior_sup, maior_term_meio, maior_comeca_meio_mais_um, maior_ambos;
    if (ini == fim)
        return (v[ini] > 0) ? v[ini] : 0;  // caso trivial, vetor unitario

    // divide o problema em dois
    meio = ini + (fim - ini) / 2;
    maior_inf = soma_subsequencias_nlogn_rec(v, ini, meio);
    maior_sup = soma_subsequencias_nlogn_rec(v, meio + 1, fim);

    // descrobrir a maior subsequencia terminada em meio
    maior_term_meio = soma = 0;
    for (long i = meio; i >= ini; i--) {
        soma += v[i];
        if (soma > maior_term_meio)
            maior_term_meio = soma;
    }

    // descobrir a maior subsequencia iniciada em meio + 1
    maior_comeca_meio_mais_um = soma = 0;
    for (long i = meio + 1; i <= fim; i++) {
        soma += v[i];
        if (soma > maior_comeca_meio_mais_um)
            maior_comeca_meio_mais_um = soma;
    }

    // descobre a maior subsequencia que envolve ambos os lados
    maior_ambos = maior_term_meio + maior_comeca_meio_mais_um;

    // descobre o maior global
    if (maior_inf > maior_sup)
        return (maior_inf > maior_ambos) ? maior_inf : maior_ambos;
    else
        return (maior_sup > maior_ambos) ? maior_sup : maior_ambos;
}

long soma_subsequencias_nlogn(int v[], long n) {
    return soma_subsequencias_nlogn_rec(v, 0, n - 1);  // inicia recursividade
}

long soma_subsequencias_n(int v[], long n) {
    long maior = 0, soma = 0;
    for (long i = 0; i < n; i++) {
        soma += v[i];
        if (soma > maior)
            maior = soma;
        else if (soma < 0)
            soma = 0;
    }
    return maior;
}

int main(void) {
    clock_t tempo_ini, soma_tempo = 0;

    srand(clock());  // reinicio a seed de geracao de numeros aleatorios

    // int v[] = {-2, 11, -4, 13, -5, -2};
    // printf("A maior soma eh: %ld\n", soma_subsequencias_n(v, 6));
    int *v;

    for (int i = 1; pow(10, i) <= TAM; i++) {
        for (int r = 0; r < repeticoes; r++) {
            // cria vetor
            v = malloc(pow(10, i) * sizeof(int));

            // insere e imprime valores
            for (long j = 0; j < pow(10, i); j++) {
                v[j] = rand() % TAM;
                if (v[j] % 2 == 0)
                    v[j] *= -1;  // pares sao transformados em negativos

                printf("%d ", v[j]);
            }
            printf("\n");

            tempo_ini = clock();

            // descobre maior subsequencia
            // soma_subsequencias_n3(v, (long) pow(10, i));
            // soma_subsequencias_n2(v, (long) pow(10, i));
            // soma_subsequencias_nlogn(v, (long) pow(10, i));
            // soma_subsequencias_n(v, (long)pow(10, i));

            soma_tempo += clock() - tempo_ini;

            // descobre e imprime a maior soma de subsequencias
            printf("A maior soma (n3) eh: %ld\n\n", soma_subsequencias_n3(v, (long)pow(10, i)));
            // printf("A maior soma (n2) eh: %ld\n", soma_subsequencias_n2(v, (long) pow(10, i)));
            // printf("A maior soma (nlong) eh: %ld\n", soma_subsequencias_nlogn(v, (long) pow(10, i)));
            // printf("A maior soma (n) eh: %ld\n", soma_subsequencias_n(v, (long) pow(10, i)));

            // destroi vetor
            free(v);
        }

        printf("Tempo: %.0lf, %.10lf\n", pow(10, i), (soma_tempo / (double)repeticoes) / CLOCKS_PER_SEC);
    }

    return 0;  // sucesso
}
