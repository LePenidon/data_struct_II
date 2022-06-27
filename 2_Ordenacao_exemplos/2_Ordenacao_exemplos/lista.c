#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

void criar(lista *l) {
	l->tamanho = 0;
	l->dados = malloc(TAM * sizeof(elem));
    l->copia = malloc(TAM * sizeof(elem));
    l->contagens = malloc(TAM * sizeof(long));
}

void destruir(lista *l) {
	l->tamanho = 0;
	free(l->dados);
    free(l->copia);
    free(l->contagens);
}

int inserir(lista *l, elem x) {
	if (l->tamanho == TAM)
		return 1; // erro, lista cheia
	l->dados[l->tamanho] = x;
	l->tamanho++;
	return 0; // sucesso 
}

void imprimir(lista l) {
	printf("(");
	for (long i = 0; i < l.tamanho; i++)
		printf("%d, ", l.dados[i]);
	if (l.tamanho > 0)
		printf("\b\b");
	printf(")\n");
}

void ordenar_selecao_simples(lista l) {
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
        return; // sim, caso trivial; ja esta ordenado
    
    // ordena metades em separado
    meio = (fim - ini) / 2 + ini; // (ini + fim) / 2
    ordenar_nlogn_recursivo(l, ini, meio); // ordena metade inferior
    ordenar_nlogn_recursivo(l, meio + 1, fim); // ordena metade superior
    
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
        ordenar_nlogn_recursivo(l, 0, l.tamanho-1);
}

void ordenar_bubble(lista l) {
    elem aux;
    int trocou = 1;
    for (long i = 0; trocou && i < l.tamanho - 1; i++) { // iteracoes
        trocou = 0;
        for (long j = 1; j < l.tamanho - i; j++) { // varre vetor
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
        return; // caso trivial
    
    // particionamento - coloca o pivo na posicao correta
    i = j = ini;
    for (; j < fim; j++) // processa um novo elemento a cada rodada
        if (l.dados[j] < l.dados[fim]) {
            // troca l.dados[i] com l.dados[j]
            aux = l.dados[i];
            l.dados[i] = l.dados[j];
            l.dados[j] = aux;
            
            // incrementa i
            i++; // achou novo elemento menor do que o pivo
        }
    
    // troca l.dados[i] com l.dados[j]
    aux = l.dados[i];
    l.dados[i] = l.dados[j];
    l.dados[j] = aux;
    
    // processa metades restandes recursivamente
    ordenar_quick_sort_rec(l, ini, i - 1); // metade inferior
    ordenar_quick_sort_rec(l, i + 1, fim); // metade superior
}

void ordenar_quick_sort(lista l) {
    ordenar_quick_sort_rec(l, 0, l.tamanho - 1);
}

void ordenar_insercao_simples(lista l) {
    long i, j;
    elem a_inserir;
    for (i = 1; i < l.tamanho; i++) {
        a_inserir = l.dados[i]; // elemento a ser inserido
        for (j = i - 1; j >= 0 && l.dados[j] > a_inserir; j--)
            l.dados[j + 1] = l.dados[j];
        l.dados[++j] = a_inserir; // insere elemento
    }
}

void ordenar_shell(lista l) {
    long ninc = 0, h, i, j, k, m;
    elem a_inserir;
    
    // define incrementos h
    long *inc = malloc(sizeof(long));
    inc[ninc] = 1; // ultimo incremento eh sempre 1
    while (l.tamanho > inc[ninc]) {
        ninc++; // novo incremento
        inc = realloc(inc, sizeof(long) * (ninc + 1));
        inc[ninc] = 3 * inc[ninc - 1] + 1; // valor do novo incremento segundo Knuth
    }
    ninc--; // ignora maior incremento, pois ele eh inutil; gera apenas sublistas unitaria
    
    for (; ninc >= 0; ninc--) { // varre vetor de incrementos, usando-os um a um
        h = inc[ninc]; // define h desta iteracao
        
        i = 0; // primeiro elemento da primeira lista
        for (j = 0; j < h; j++) { // faz insertion sort em uma lista por vez
            for (k = h + i; k < l.tamanho; k += h) {
                a_inserir = l.dados[k]; // elemento a ser inserido
                for (m = k - h; m >= 0 && l.dados[m] > a_inserir; m -= h)
                    l.dados[m + h] = l.dados[m];
                l.dados[m + h] = a_inserir; // insere elemento
            }
            i++; // passa para a próxima lista
        }
    }
    
    free(inc); // libera memoria
}

void rearranjar_heap(lista l, long i, long tam_heap) {
    // custo total: c * altura da heap = c * log_2 n = O(log n)
    
    long fe, fd, mf;
    elem aux;
    
    // descobre filhos
    fe = (2 * i + 1 < tam_heap) ? 2 * i + 1 : -1; // filho esquerdo
    fd = (2 * i + 2 < tam_heap) ? 2 * i + 2 : -1; // filho direito
    
    // verifica se i eh folha
    if (fe == -1)
        return; // heap ok, pois i eh folha
    
    // descobre maior filho
    mf = (fd == -1 || l.dados[fe] > l.dados[fd]) ? fe : fd;
    
    // verifica se o elemento da posicao i eh maior ou igual ao maior filho
    if (l.dados[i] >= l.dados[mf])
        return; // heap ok, pois atende a propriedade de ordem
    
    // troca elementos das posicoes i e mf
    aux = l.dados[i];
    l.dados[i] = l.dados[mf];
    l.dados[mf] = aux;
    
    // rearranja a partir da posicao mf
    rearranjar_heap(l, mf, tam_heap);
}

void construir_heap(lista l) {
    // custo total: n / 2 * O(log n) = O(n log n)
    
    for (long i = l.tamanho / 2 - 1; i >= 0; i--)
        rearranjar_heap(l, i, l.tamanho); // rearranja em ordem ascencente dos nos interiores
}

void ordenar_heap(lista l) {
    //custo total = O(n log n) + (n - 1) * ( c + O(log n)) = O(n log n)
    
    long tam_heap;
    elem aux;
    
    // construir heap
    construir_heap(l);
    
    // coloca um a um os maiores elementos no final
    tam_heap = l.tamanho;
    for (long i = 0; i < l.tamanho - 1; i++) {
        // trocar raiz por ultimo elemento
        aux = l.dados[0];
        l.dados[0] = l.dados[tam_heap - 1];
        l.dados[tam_heap - 1] = aux;
        
        // diminuir heap
        tam_heap--;
        
        // rearranjar heap
        rearranjar_heap(l, 0, tam_heap);
    }
}

void ordenar_contagem_menores(lista l) {
    long i, j;
    
    // inicializar vetor de contagens
    for (i = 0; i < l.tamanho; i++)
        l.contagens[i] = 0;
    
    // contar menores
    for (i = 1; i < l.tamanho; i++)
        for (j = 0; j < i; j++)
            if (l.dados[i] < l.dados[j])
                l.contagens[j]++;
            else
                l.contagens[i]++; // empates sao sempre contados aqui
    
    // montar vetor ordenado na copia
    for (i = 0; i < l.tamanho; i++)
        l.copia[l.contagens[i]] = l.dados[i];
    
    // sobrescrever copia ao vetor original
    for (i = 0; i < l.tamanho; i++)
        l.dados[i] = l.copia[i];
}

void ordenar_contagem_tipos(lista l) { // counting sort
    elem menor, maior;
    int num_tipos;
    long *contagens;
    long i; // indice do vetor de dados
    int j; // indice do vetor de contagens
    
    // encontrar menor e maior
    menor = maior = l.dados[0];
    for (i = 1; i < l.tamanho; i++) {
        if (l.dados[i] > maior)
            maior = l.dados[i];
        if (l.dados[i] < menor)
            menor = l.dados[i];
    }
    
    // criar vetor de contagens
    num_tipos = maior - menor + 1;
    contagens = malloc(num_tipos * sizeof(long));
    
    // zerar contagens
    for (j = 0; j < num_tipos; j++)
        contagens[j] = 0;
    
    // fazer contagens
    for (i = 0; i < l.tamanho; i++)
        contagens[l.dados[i] - menor]++;
    
    // montar vetor ordenado
    i = 0;
    for (j = 0; j < num_tipos; j++)
        while (contagens[j] > 0) {
            l.dados[i++] = menor + j; // obtem valor a partir da posicao em contagens
            contagens[j]--;
        }
    
    // limpar a memoria
    free(contagens);
}

int contar_digitos(elem x) {
    int contagem = 1;
    while (x >= 10) {
        x /= 10; // divide x por 10, removendo um digito por vez
        contagem++;
    }
    return contagem;
}

int retornar_digito(elem x, int i) {
    while (i > 0) {
        x /= 10;
        i--;
    }
    return x % 10;
}

void ordenar_raizes(lista l) {
    int fila, digitos_maior, j;
    long i, k;
    elem *filas[10], maior;
    long tam_filas[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    // instanciar filas
    for (fila = 0; fila < 10; fila++)
        filas[fila] = malloc(sizeof(elem) * TAM);
    
    // encontrar maior
    maior = l.dados[0];
    for (i = 1; i < l.tamanho; i++)
        if (l.dados[i] > maior)
            maior = l.dados[i];
    
    // descobrir numero de digitos do maior
    digitos_maior = contar_digitos(maior);
    
    // faz digitos_maior iteracoes
    for (j = 0; j < digitos_maior; j++) { // uma iteracao por vez
        // inserir nas filas
        for (i = 0; i < l.tamanho; i++) {
            fila = retornar_digito(l.dados[i], j); // descrobrir fila a inserir
            filas[fila][tam_filas[fila]++] = l.dados[i]; // inserir l.dados[i] na fila
        }
        
        // remover das filas
        i = 0;
        for (fila = 0; fila < 10; fila++) {
            for (k = 0; k < tam_filas[fila]; k++) // varre fila, removendo um a um
                l.dados[i++] = filas[fila][k];
            tam_filas[fila] = 0;
        }
    }
    
    // apagar filas
    for (fila = 0; fila < 10; fila++)
        free(filas[fila]);
}
