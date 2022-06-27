#define TAM 10

typedef int elem;

typedef struct {
    elem *dados;
    elem *copia;
    long *contagens;
    long tamanho;
} lista;

void criar(lista *l);
void destruir(lista *l);
int inserir(lista *l, elem x);
void imprimir(lista l);
void ordenar_selecao_simples(lista l);
void ordenar_nlogn(lista l);
void ordenar_bubble(lista l);
void ordenar_quick_sort(lista l);
void ordenar_insercao_simples(lista l);
void ordenar_shell(lista l);
void ordenar_heap(lista l);
void ordenar_contagem_menores(lista l);
void ordenar_contagem_tipos(lista l);
void ordenar_raizes(lista l);
