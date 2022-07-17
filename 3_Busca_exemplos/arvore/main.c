#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void em_ordem_recursivo(No *p) {
    if (p == NULL)
        return; // nada a processar
    em_ordem_recursivo(p->esq); // processa lado esquerdo
    printf(" %d ", p->info); // processa no corrente
    em_ordem_recursivo(p->dir); // processa lado direito
}

void em_ordem(Arvore a) {
    em_ordem_recursivo(a.raiz); // inicia recursividade
    printf("\n");
}

int inserir_recursivo(No **p, elem x) {
    // p   => No**
    // *p  => No*
    // **p => No
    
    if (*p == NULL) {
        // criar novo no
        *p = malloc(sizeof(No));
        // copiar informacao, e inicializa subarvores
        (*p)->info = x;
        (*p)->esq = (*p)->dir = NULL;
        // retornar sucesso
        return 0; // sucesso
    }
    if (x == (*p)->info)
        return 1; // erro, elemento repetido
    return (x < (*p)->info) ? inserir_recursivo(&((*p)->esq), x) : inserir_recursivo(&((*p)->dir), x); // insere na subarvore apropriada, e retorna
}

int inserir(Arvore *a, elem x) {
    return inserir_recursivo(&(a->raiz), x); // inicia recursividade
}

No *buscar_recursivo(No *p, elem x) {
    if (p == NULL || x == p->info)
        return p; // terminou, com sucesso ou nao
    return (x < p->info) ? buscar_recursivo(p->esq, x) : buscar_recursivo(p->dir, x); // continua a busca na subarvore apropriada, e retorna
}

No *buscar(Arvore a, elem x) {
    return buscar_recursivo(a.raiz, x); // inicia recursividade
}

int remover_recursivo(No **p, elem x) {
    // p   => No**
    // *p  => No*
    // **p => No
    int numfilhos = 0;
    No *aux;
    
    if (*p == NULL)
        return 1; // erro, elemento nao existe
    if (x == (*p)->info) {
        // elemento encontrado, e deve ser removido
        // conta filhos
        if ((*p)->esq != NULL)
            numfilhos++;
        if ((*p)->dir != NULL)
            numfilhos++;
        // identifica o caso da remocao
        switch (numfilhos) {
            case 0: // nenhum filho
                free(*p); // libera a memoria
                *p = NULL;
                break;
            case 1: // um filho
                aux = *p; // guarda ponteiro a remover
                *p = ((*p)->esq != NULL) ? (*p)->esq : (*p)->dir;
                free(aux);
                break;
            case 2: // dois filhos
                // achar substituto
                aux = (*p)->dir; // um passo aa direita
                while (aux->esq != NULL) // segue ate o fim aa esquerda
                    aux = aux->esq;
                // copia substituto
                (*p)->info = aux->info;
                // apaga substituto
                remover_recursivo(&((*p)->dir), aux->info); // remove substituto
        };
        return 0; // sucesso
    }
    return (x < (*p)->info) ? remover_recursivo(&((*p)->esq), x) : remover_recursivo(&((*p)->dir), x); // continua remocao na subarvore apropriada, e retorna
}

int remover(Arvore *a, elem x) {
    return remover_recursivo(&(a->raiz), x); // inicia recursividade
}

int main(void) {
    int n = 10;
    
    // inicializa seed de geracao de numeros aleatorios
    srand(clock());
    
    // cria uma arvore vazia
    Arvore a;
    criar(&a);
    
    // insere elementos aleatorios
    for (int i = 0; i < n; i++) {
        inserir(&a, rand() % n); // insere apenas se nao for repetido
        //while (inserir(&a, rand() % n) != 0); // forca a insercao de um valor
    }
    
    // imprime elementos em ordem
    em_ordem(a);
    
    // faz todas as buscas possiveis
    for (int i = 0; i < n; i++)
        if (buscar(a, i) != NULL)
            printf("Elemento %d encontrado\n", i);
        else
            printf("Elemento %d NAO encontrado\n", i);
    
    // remove elementos um a um
    for (int i = 0; i < n; i++)
        if (remover(&a, i) == 0)
            printf("Elemento %d removido\n", i);
        else
            printf("Elemento %d NAO removido\n", i);
    
    // destroi a arvore
    destruir(&a);
}
