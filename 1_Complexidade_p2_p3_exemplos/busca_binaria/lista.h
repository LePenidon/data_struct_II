#define TAM 10

typedef int elem;

typedef struct {
    elem *dados;
    elem *copia;
    long tamanho;
} lista;

void criar(lista *l);
void destruir(lista *l);
int inserir(lista *l, elem x);
void imprimir(lista l);
int buscar(lista l, elem x);
void ordenar_nlogn(lista l);
int buscar_recursivo_penido(lista l, elem x, long ini, long fim);
int buscar_penido(lista l, elem x);
