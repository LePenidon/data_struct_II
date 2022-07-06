#include <stdio.h>

#define B 10
#define h(k,i) (k + i) % B

typedef int elem;
typedef struct {
    elem dados[B];
} hash;

void inicializar(hash *tabela) {
    for (int i = 0; i < B; i++)
        tabela->dados[i] = -1; // -1: posicao vazia, nunca utilizada
}

int inserir(hash *tabela, elem k) {
    int pos;
    for (int i = 0; i < B; i++) { // faz no maximo B tentantivas
        pos = h(k,i); // calcula endereco / valor hash
        if (tabela->dados[pos] == -1 || tabela->dados[pos] == -2) {
            // posicao vazia(-1: nunca utilizada; -2: ja utilizada); insere com sucesso
            tabela->dados[pos] = k; // guarda elemento
            return 0; // sucesso
        }
        if (tabela->dados[pos] == k)
            return 1; // erro, elemento ja existe
    }
    return 1; // erro, tabela cheia
}

int remover(hash *tabela, elem k) {
    int pos;
    for (int i = 0; i < B; i++) { // faz no maximo B tentantivas
        pos = h(k,i); // calcula endereco / valor hash
        if (tabela->dados[pos] == k) {
            // elemento encontrado / remove
            tabela->dados[pos] = -2; // posicao vazia, porem ja utilizada anteriormente
            return 0; // sucesso
        }
        if (tabela->dados[pos] == -1)
            return 1; // erro, elemento nao existe; esta posicao sempre esteve vazia
    }
    return 1; // erro, elemento nao existe; tabela cheia
}

int buscar(hash *tabela, elem k) {
    int pos;
    for (int i = 0; i < B; i++) { // faz no maximo B tentantivas
        pos = h(k,i); // calcula endereco / valor hash
        if (tabela->dados[pos] == k) {
            // elemento encontrado
            return pos; // sucesso
        }
        if (tabela->dados[pos] == -1)
            return -1; // erro, elemento nao existe; esta posicao sempre esteve vazia
    }
    return -1; // erro, elemento nao existe; tabela cheia
}

int main(void) {
    hash tabela;
    elem k;
    int opcao, pos;
    
    inicializar(&tabela);
    
    do {
        printf("Escolha uma das opcoes abaixo\n");
        printf("\t(1) Inserir\n");
        printf("\t(2) Remover\n");
        printf("\t(3) Buscar\n");
        printf("\t(4) Sair\n");
        scanf("%d", &opcao);
        
        if (opcao != 4) {
            printf("Digite a chave k:\n");
            scanf("%d", &k);
        }
           
        switch (opcao) {
            case 1: // inserir
                if (inserir(&tabela, k) == 0)
                    printf("Elemento %d inserido com sucesso\n", k);
                else
                    printf("Elemento %d NAO inserido\n", k);
                break;
            case 2: // remover
                if (remover(&tabela, k) == 0)
                    printf("Elemento %d removido com sucesso\n", k);
                else
                    printf("Elemento %d NAO removido\n", k);
                break;
            case 3: // buscar
                pos = buscar(&tabela, k);
                if (pos != -1)
                    printf("Elemento %d encontrado na posicao %d\n", k, pos);
                else
                    printf("Elemento %d NAO encontrado\n", k);
                break;
            case 4:
                printf("Ate logo.\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
        
    } while(opcao != 4);
    
    
    return 0; // sucesso
}
