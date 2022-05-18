#define repeticoes 3
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista.h"

int main(void) {
    lista l;
    clock_t tempo_ini, soma_tempos;

    srand(clock());

    for (int i = 1; pow(10, i) <= TAM; i++) {
        soma_tempos = 0;
        for (int j = 0; j < repeticoes; j++) {
            // cria a lista
            criar(&l);

            // insere elementos
            for (long k = 0; k < pow(10, i); k++)
                inserir(&l, rand() % TAM);

            // imprime a lista original
            imprimir(l);

            // registra tempo inicial
            tempo_ini = clock();

            // ordena a lista
            // ordenar_n2(l);
            // ordenar_nlogn(l);
            // ordenar_bubble(l);
            // ordenar_quick_sort(l);
            // ordenar_insercao_simples(l);

            // ordenar_n2_penido(l);
            // ordenar_nlogn_penido(l);
            // ordenar_bubble_penido(l);
            ordenar_quick_sort_penido(l);
            // ordenar_insercao_simples_penido(l);

            // registra tempo decorrido
            soma_tempos += clock() - tempo_ini;

            // imprime a lista ordenada
            imprimir(l);
            printf("\n");

            // destroi a lista
            destruir(&l);
        }

        printf("%.0lf\t%.4lf\n", pow(10, i), (((double)soma_tempos) / repeticoes) / CLOCKS_PER_SEC);
    }
    return 0;  // sucesso
}
