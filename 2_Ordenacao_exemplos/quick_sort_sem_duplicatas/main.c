#include <stdio.h>

void quick_sort_original_rec(int v[], long ini, long fim) {
    long i, j, meio;
    int pivo, aux;
    
    if (ini >= fim)
        return; // caso trivial
    
    // define o pivo
    meio = ini + (fim - ini) / 2;
    pivo = v[meio];
    
    // faz uma iteracao - particionamento
    i = ini;
    j = fim;
    while (1) {
        // i anda para a direita
        for (; v[i] < pivo; i++);
        
        // j anda para a esquerda
        for (; v[j] > pivo; j--);
        
        if (i == j)
            break; // i e j se encontraram; fim da iteracao
        
        // troca elementos das posicoes i e j
        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
    
    // processa metades restandes recursivamente
    quick_sort_original_rec(v, ini, i - 1); // metade inferior
    quick_sort_original_rec(v, i + 1, fim); // metade superior
}

void quick_sort_original(int v[], long n) {
    return quick_sort_original_rec(v, 0, n - 1); // inicia recursividade
}

int main(void) {
    int v[] = {25, 57, 35, 37, 12, 86, 92, 33};
    
    // imprime vetor original
    printf("Vetor original: ");
    for (long i = 0; i < 8; i++)
        printf("%d, ", v[i]);
    printf("\n");
    
    // ordena vetor
    quick_sort_original(v, 8);

    // imprime vetor ordenado
    printf("Vetor ordenado: ");
    for (long i = 0; i < 8; i++)
        printf("%d, ", v[i]);
    printf("\n");
}
