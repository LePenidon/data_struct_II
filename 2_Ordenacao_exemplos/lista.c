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

void ordenar_bubble(lista l) {
    elem aux;
    int trocou = 1;
    for (long i = 0; trocou && i < l.tamanho - 1; i++) {  // iteracoes
        trocou = 0;
        for (long j = 1; j < l.tamanho - i; j++) {  // varre vetor
            if (l.dados[j - 1] > l.dados[j]) {
                // troca elementos
                trocou = 1;
                aux = l.dados[j];
                l.dados[j] = l.dados[j - 1];
                l.dados[j - 1] = aux;
            }
        }
    }
}

void ordenar_quick_sort_rec(lista l, long ini, long fim) {
    // particionamento de Lomuto
    // pivo sempre no fim

    long i, j;
    elem aux;

    if (ini >= fim)
        return;  // caso trivial

    // particionamento - coloca o pivo na posicao correta
    i = j = ini;
    for (; j < fim; j++)  // processa um novo elemento a cada rodada
        if (l.dados[j] < l.dados[fim]) {
            // troca l.dados[i] com l.dados[j]
            aux = l.dados[i];
            l.dados[i] = l.dados[j];
            l.dados[j] = aux;

            // incrementa i
            i++;  // achou novo elemento menor do que o pivo
        }

    // troca l.dados[i] com l.dados[j]
    aux = l.dados[i];
    l.dados[i] = l.dados[j];
    l.dados[j] = aux;

    // processa metades restandes recursivamente
    ordenar_quick_sort_rec(l, ini, i - 1);  // metade inferior
    ordenar_quick_sort_rec(l, i + 1, fim);  // metade superior
}

void ordenar_quick_sort(lista l) {
    ordenar_quick_sort_rec(l, 0, l.tamanho - 1);
}

void ordenar_insercao_simples(lista l) {
    long i, j;
    elem a_inserir;
    for (i = 1; i < l.tamanho; i++) {
        a_inserir = l.dados[i];  // elemento a ser inserido
        for (j = i - 1; j >= 0 && l.dados[j] > a_inserir; j--)
            l.dados[j + 1] = l.dados[j];
        l.dados[++j] = a_inserir;  // insere elemento
    }
}

// -------------------------------------------------------------------------------

void ordenar_n2_penido(lista l) {
    long i, j, menor, idMenor, aux;

    for (i = 0; i < l.tamanho; i++) {
        menor = l.dados[i];
        idMenor = i;
        for (j = i; j < l.tamanho; j++) {
            if (l.dados[j] < menor) {
                menor = l.dados[j];
                idMenor = j;
            }
        }
        aux = l.dados[i];
        l.dados[i] = menor;
        l.dados[idMenor] = aux;
    }
}

void ordenar_nlogn_penido_rec(lista l, long ini, long fim) {
    long lc, ls, li, meio;

    if (ini == fim) {
        return;
    }

    meio = (ini + fim) / 2;
    ordenar_nlogn_penido_rec(l, ini, meio);
    ordenar_nlogn_penido_rec(l, meio + 1, fim);

    li = lc = ini;
    ls = meio + 1;

    while (ls <= fim && li <= meio) {
        if (l.dados[li] < l.dados[ls]) {
            l.copia[lc] = l.dados[li];
            lc++;
            li++;
        } else {
            l.copia[lc] = l.dados[ls];
            lc++;
            ls++;
        }
    }

    while (li <= meio) {
        l.copia[lc++] = l.dados[li++];
    }

    while (ls <= fim) {
        l.copia[lc++] = l.dados[ls++];
    }

    for (lc = ini; lc <= fim; lc++) {
        l.dados[lc] = l.copia[lc];
    }
}

void ordenar_nlogn_penido(lista l) {
    if (l.tamanho > 0)
        ordenar_nlogn_penido_rec(l, 0, l.tamanho - 1);
}

void ordenar_bubble_penido(lista l) {
    long i, j, aux;
    int trocou = 1;

    for (i = 0; trocou && i < l.tamanho - 1; i++) {
        for (j = 1; j < l.tamanho - i; j++) {
            if (l.dados[j - 1] > l.dados[j]) {
                aux = l.dados[j - 1];
                l.dados[j - 1] = l.dados[j];
                l.dados[j] = aux;

                trocou = 1;
            }
        }
    }
}

void ordenar_quick_sort_penido_rec(lista l, long ini, long fim) {
    long i, j;
    elem aux;

    if (ini >= fim) {
        return;
    }

    i = j = ini;
    for (; j < fim; j++) {
        if (l.dados[j] < l.dados[fim]) {
            aux = l.dados[i];
            l.dados[i] = l.dados[j];
            l.dados[j] = aux;

            i++;
        }
    }

    aux = l.dados[fim];
    l.dados[fim] = l.dados[i];
    l.dados[i] = aux;

    ordenar_quick_sort_penido_rec(l, ini, i - 1);
    ordenar_quick_sort_penido_rec(l, i + 1, fim);
}

void ordenar_quick_sort_penido(lista l) {
    ordenar_quick_sort_penido_rec(l, 0, l.tamanho - 1);
}

void ordenar_insercao_simples_penido(lista l) {
    long i, j;
    elem a_inserir;

    for (i = 1; i < l.tamanho; i++) {
        a_inserir = l.dados[i];
        for (j = i - 1; j >= 0 && a_inserir < l.dados[j]; j--) {
            l.dados[j + 1] = l.dados[j];
        }
        l.dados[++j] = a_inserir;
    }
}
