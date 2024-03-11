#include <stdio.h>
#include <stdlib.h>

#define M 25

typedef struct {
    int codigo;
    char descricao[100];
    double preco;
} Produto;

typedef struct no {
    Produto produto;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    int tam;
} Lista;


void inicializarHash(Lista *tabela[]) {
    for (int i = 0; i < M; i++) {
        tabela[i]= (Lista*)malloc(sizeof(Lista));
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

Produto criarProduto() {
    Produto novoProduto;

    printf("\nCodigo: ");
    scanf("%d", &novoProduto.codigo);
    fflush(stdin);
    printf("Descricao: ");
    gets(novoProduto.descricao);
    fflush(stdin);
    printf("Preco: ");
    scanf("%lf", &novoProduto.preco);
    fflush(stdin);

    return novoProduto;
}

Produto* busca(Lista *tabela[], int valor) {
    int id = dobra(valor);
    No *aux = tabela[id]->inicio;

    while (aux && aux->produto.codigo != valor)
        aux = aux->prox;
    
    if (aux)
        return &(aux->produto);
    else
        return NULL;
    
}

void inserir(Lista *tabela[], Produto novoProduto) {
    int id = dobra(novoProduto.codigo);

    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->produto = novoProduto;
    novoNo->prox = tabela[id]->inicio;
    tabela[id]->inicio = novoNo;
    tabela[id]->tam++;
}

void remover(Lista *tabela[], int cod) {
    int id = dobra(cod);

    No *aux = tabela[id]->inicio;

    if (aux->produto.codigo == cod) {
        tabela[id]->inicio = aux->prox;
        tabela[id]->tam--;
        free(aux);
        return;
    }
    else {
        while (aux->prox) {
            if (aux->prox->produto.codigo == cod) {
                No *del = aux->prox;
                aux->prox = aux->prox->prox;
                tabela[id]->tam--;
                free(del);
                return;
            }
            aux = aux->prox;
        }
    }
    printf("\nProduto nao encontrado\n");
}

void destruirTabela(Lista *tabela[]){
    for (int i = 0; i < M; i++) {
        No *aux = tabela[i]->inicio;
        while (aux) {
            No *del = aux;
            aux = aux->prox;
            free(del);
        }
    }
}

void imprimir(Lista *tabela[]) {
    for (int i = 0; i < M; i++) {
        No *aux = tabela[i]->inicio;
        printf("[%d]->", i);
        while (aux) {
            printf("(%d)->",aux->produto.codigo);
            aux = aux->prox;
        }
        printf("NULL\n");
    }
}


int main() {
    Lista *tabela[M];
    inicializarHash(tabela);
    int cod = 0;
    Produto novoProduto;
    int op;

    do {
        printf("\n[1]Inserir\n[2]Remover\n[3]Buscar\n[4]Imprimir\n[0]Sair\nOpcao: ");
        scanf("%d",&op);
        switch (op) {
        case 1:
            novoProduto = criarProduto();
            inserir(tabela, novoProduto);
            break;
        case 2:
            printf("\nCodigo: ");
            scanf("%d", &cod);
            remover(tabela, cod);
            break;
        case 3:
            printf("\nCodigo: ");
            scanf("%d", &cod);
            Produto *produtoBusca = busca(tabela, cod);
            printf("%s\nR$%.2lf",produtoBusca->descricao, produtoBusca->preco);
            break;
        case 4:
            imprimir(tabela);
            break;
        case 0:
            destruirTabela(tabela);
            printf("\nSaindo\n");
            break;
        
        default:
            printf("\nOpcao invalida\n");
            break;
        }

    } while (op != 0);
    
    



    return 0;
}