#include <stdio.h>
#include <stdlib.h>

typedef int elem;

typedef struct no {
    elem info;
    struct no *esq, *dir;
} No;

typedef struct {
    No *raiz;
} Arvore;

void criar(Arvore *a) {
    a->raiz = NULL;
}

void destruir_recursivo(No *p) {
    if (p == NULL)
        return; // nada a destruir: subarvore nula
    destruir_recursivo(p->esq); // destroi subarvore esquerda
    destruir_recursivo(p->dir); // destroi subarvore direita
    free(p); // apaga o no corrente
}

void destruir(Arvore *a) {
    destruir_recursivo(a->raiz);
    criar(a); // reinicializa raiz
}
