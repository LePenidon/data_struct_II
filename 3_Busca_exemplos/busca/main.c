#include <stdio.h>
#include <stdlib.h>

typedef int elem;

typedef struct {
    elem kindex;
    int posicao;
} elem_i;

int busca_sequencial(elem tabela[], int n, elem e) {
    int i;
    for (i = 0; i < n; i++)
        if (tabela[i] == e)
            break;            // encontrou
    return (i < n) ? i : -1;  // retorna posicao do elemento encontrado, ou posicao invalida quando o elemento nao existe
}

int busca_sequencial_sentinela(elem tabela[], int n, elem e) {
    int i;
    // copia valor buscado no final do vetor, i.e., sentinela
    tabela[n] = e;
    // faz a busca
    for (i = 0; tabela[i] != e; i++)
        ;
    return (i < n) ? i : -1;  // retorna posicao do elemento encontrado, ou posicao invalida quando o elemento nao existe
}

int busca_sequencial_ordenada(elem tabela[], int n, elem e) {
    int i;
    for (i = 0; i < n; i++)
        if (tabela[i] >= e)
            break;  // encontrou ou ja sabe que nao vai encontrar
    return (i < n && tabela[i] == e) ? i : -1;
}

int busca_sequencial_indexada(elem tabela[], int n, elem e, elem_i tabind[], int t) {
    int i, j;
    for (i = 0; i < t && tabind[i].kindex < e; i++)
        ;  // busca na tabela de inidice
    if (i == 0)
        return (tabela[0] == e) ? 0 : -1;  // elemento buscado eh o primeiro, ou eh menor do que o primeiro
    for (j = tabind[i - 1].posicao; j < n && tabela[j] < e; j++)
        ;  // busca na tabela de dados
    return (j < n && tabela[j] == e) ? j : -1;
}

int busca_binaria(elem tabela[], int n, elem e) {
    int ini = 0, fim = n - 1, meio;

    while (ini <= fim) {
        meio = ini + (fim - ini) / 2;
        if (e == tabela[meio])
            return meio;  // achou
        if (e < tabela[meio])
            fim = meio - 1;  // busca continua na metade inferior: altera o fim
        else
            ini = meio + 1;  // busca continua na metade superior: altera o ini
    }

    return -1;  // nao achou
}

int main(void) {
    int retorno, n = 10, t = 3;
    elem tabela[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, -1};  // tabela de dados
    elem_i *tabind;                                            // tabela de indice primario
    elem e = 20;

    // controi tabela de indice
    tabind = malloc(sizeof(elem_i) * t);
    for (int i = 0; i < t; i++) {
        tabind[i].posicao = i * n / t;                 // posicao da chave indexada
        tabind[i].kindex = tabela[tabind[i].posicao];  // chave indexada
    }

    // faz a busca
    // retorno = busca_sequencial(tabela, n, e);
    // retorno = busca_sequencial_sentinela(tabela, n, e);
    // retorno = busca_sequencial_ordenada(tabela, n, e);
    // retorno = busca_sequencial_indexada(tabela, n, e, tabind, t);
    retorno = busca_binaria(tabela, n, e);

    if (retorno != -1)
        printf("Elemento %d encontrado na posicao %d.\n", e, retorno);
    else
        printf("Elemento %d NAO encontrado.\n", e);

    // apaga tabela de indice
    free(tabind);

    return 0;  // sucesso
}
