#define repeticoes 10
#include "lista.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(void) {
	lista l;
	clock_t tempo_ini, soma_tempos;
    elem buscado;

    for (int i = 1; pow(10, i) <= TAM; i++) {
        soma_tempos = 0;
        
        // cria a lista
        criar(&l);

        // insere elementos
        for (long k = 0; k < pow(10, i); k++)
            inserir(&l, rand() % TAM);
        
        // ordena a lista
        ordenar_nlogn(l);
        
        // imprime a lista ordenada
        //imprimir(l);

        for (int m = 0; m < repeticoes; m++) {
            // registra tempo inicial
            tempo_ini = clock();
            
            // busca um elemento
            buscado = rand() % TAM;
            buscar(l, buscado);
            //if (buscar(l, buscado))
            //    printf("Elemento %d encontrado\n", buscado);
            //else
            //    printf("Elemento %d NAO encontrado\n", buscado);
        
            // registra tempo decorrido
            soma_tempos += clock() - tempo_ini;
        }
        
        // destroi a lista
        destruir(&l);

        printf("%.0lf\t%.10lf\n", pow(10, i), ( ((double) soma_tempos) / repeticoes) / CLOCKS_PER_SEC);
    }
	return 0; // sucesso
}
