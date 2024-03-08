#include <stdio.h>
#include <stdlib.h>

#define M 25

typedef struct {
    int codigo;
    char nome[50];
} Pessoa;

typedef struct no {
    Pessoa pessoa;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    int tam;
} Lista;


void inicializarHash(Lista *tabela[]) {
    for (int i = 0; i < M; i++) {
        tabela[i]->inicio = NULL;
        tabela[i]->tam = 0;
    }
}

int dobra(int chave) {
    int nbits = 10;
    int parte1 = chave >> nbits;
    int parte2 = chave & (M-1);
    return (parte1 ^ parte2);
}

Pessoa* busca(Lista *tabela[], int valor) {
    int id = dobra(valor);
    No *aux = tabela[id]->inicio;

    while (aux && aux->pessoa.codigo != valor)
        aux = aux->prox;
    
    if (aux)
        return &(aux->pessoa);
    else
        return NULL;
    
}



int main() {
    Lista *tabela[M];




    return 0;
}