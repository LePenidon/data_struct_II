#define TAM 10000000

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
void ordenar_n2(lista l);
void ordenar_nlogn(lista l);
