#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

void criar(lista *l) {
    l->tamanho = 0;
    l->dados = malloc(TAM * sizeof(elem));
    l->copia = malloc(TAM * sizeof(elem));
}

void destruir(lista *l) {
    l->tamanho = 0;
    free(l->dados);
    free(l->copia);
}

int inserir(lista *l, elem x) {
    if (l->tamanho == TAM)
        return 1;  // erro, lista cheia
    l->dados[l->tamanho] = x;
    l->tamanho++;
    return 0;  // sucesso
}

void imprimir(lista l) {
    printf("(");
    for (long i = 0; i < l.tamanho; i++)
        printf("%d, ", l.dados[i]);
    if (l.tamanho > 0)
        printf("\b\b");
    printf(")\n");
}

// bubbleSort
void ordenar_n2(lista l) {
    elem menor, aux;
    long idMenor;

    for (long i = 0; i < l.tamanho - 1; i++) {
        // descobre o menor a partir da posicao i
        menor = l.dados[i];
        idMenor = i;
        for (long j = i + 1; j < l.tamanho; j++)
            if (menor > l.dados[j]) {
                menor = l.dados[j];
                idMenor = j;
            }
        // colocar menor na posicao i
        aux = l.dados[i];
        l.dados[i] = menor;
        l.dados[idMenor] = aux;
    }
}

void ordenar_nlogn_recursivo(lista l, long ini, long fim) {
    long meio, li, ls, lc;

    // verifica se esta no caso trivial de vetor unitario
    if (ini == fim)
        return;  // sim, caso trivial; ja esta ordenado

    // ordena metades em separado
    meio = (fim - ini) / 2 + ini;               // (ini + fim) / 2
    ordenar_nlogn_recursivo(l, ini, meio);      // ordena metade inferior
    ordenar_nlogn_recursivo(l, meio + 1, fim);  // ordena metade superior

    // une ambas as metades em uma copia
    li = lc = ini;
    ls = meio + 1;
    // varre listas em paralelo
    while (li <= meio && ls <= fim)
        l.copia[lc++] = (l.dados[li] < l.dados[ls]) ? l.dados[li++] : l.dados[ls++];
    /*if (l.dados[li] < l.dados[ls]) {
        l.copia[lc] = l.dados[li];
        lc++;
        li++;
    } else {
        l.copia[lc] = l.dados[ls];
        lc++;
        ls++;
    }*/
    // varre a lista que faltou terminar
    while (li <= meio)
        l.copia[lc++] = l.dados[li++];
    while (ls <= fim)
        l.copia[lc++] = l.dados[ls++];

    // sobrescreve o vetor original com a copia
    for (lc = ini; lc <= fim; lc++)
        l.dados[lc] = l.copia[lc];
}

void ordenar_nlogn(lista l) {
    if (l.tamanho > 0)
        ordenar_nlogn_recursivo(l, 0, l.tamanho - 1);
}
