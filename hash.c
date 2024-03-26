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
    No *aux = tabela[id]->inicio;
    while (aux) {
        if (aux->produto.codigo == novoProduto.codigo) {
            printf("\nCodigo de produto ja utilizado. Produto nao cadastrado\n");
            return;
        }
        aux = aux->prox;
    }
    
    novoNo->prox = tabela[id]->inicio;
    tabela[id]->inicio = novoNo;
    tabela[id]->tam++;
}

int remover(Lista *tabela[], int cod) {
    int id = dobra(cod);

    No *aux = tabela[id]->inicio;

    if (aux && aux->produto.codigo == cod) {
        tabela[id]->inicio = aux->prox;
        tabela[id]->tam--;
        free(aux);
        printf("Produto removido\n");
        return 1;
    }
    else {
        while (aux && aux->prox) {
            if (aux->prox->produto.codigo == cod) {
                No *del = aux->prox;
                aux->prox = aux->prox->prox;
                tabela[id]->tam--;
                free(del);
                return 1;
            }
            aux = aux->prox;
        }
    }
    return 0;
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
    printf("\nTabela <= R$200,00\n");
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
//2
void incializarHash2(Produto *tabela[]) {
    for (int i = 0; i < M; i++)
        tabela[i] = NULL;
}

int divisao(int cod) {
    return cod % M;
}

int hash2(int cod) {
    return 23 - (cod % 23);
}

void inserir2(Produto *tabela[], Produto produto) {
    int id = divisao(produto.codigo);
    int h2 = hash2(produto.codigo);
    int contador = 0;

    while (tabela[id] != NULL && contador <= M) {
        if (tabela[id]->codigo == produto.codigo) {
            printf("Codigo de produto ja utilizado. Produto nao cadastrado\n");
            return;
        }
        id = (id + contador * h2) % M;
        contador++;
    }
    
    if (contador > M) 
        printf("\nTabela Hash de Encadeamento Aberto cheia.\n");
    else {
        Produto *novoProduto = (Produto *)malloc(sizeof(Produto));
        *novoProduto = produto; 
        tabela[id] = novoProduto;
    }
}

Produto *busca2(Produto *tabela[], int cod) {
    int id = divisao(cod);
    int h2 = hash2(cod);
    int contador = 0;

    while (tabela[id] != NULL && contador <= M) {
        if (tabela[id]->codigo == cod)
            return tabela[id];
        
        id = (id + contador * h2) % M;
        contador++;
    }
    return NULL;
}

void remover2(Produto *tabela[], int cod) {
    int id = divisao(cod);
    int h2 = hash2(cod);
    int contador = 0;

    while (tabela[id] != NULL && contador <= M) {
        if (tabela[id]->codigo == cod) {
            free(tabela[id]);
            tabela[id] = NULL;
            printf("Produto removido\n");
            return;
        }
        id = (id + contador * h2) % M;
        contador++;
    }
    printf("Produto nao encontrado\n");
}

void imprimir2(Produto *tabela[]) {
    printf("\n\nTabela > R$200,00\n");
    for (int i = 0; i < M; i++) {
        if (tabela[i] == NULL )
            printf("%d - NULL\n", i);
        else
            printf("%d - [%d]\n", i, tabela[i]->codigo);
    }
}


int main() {
    Lista *tabela[M];
    inicializarHash(tabela);
    Produto *tabela2[M];
    incializarHash2(tabela2);
    int cod = 0;
    Produto novoProduto;
    int op;

    do {
        printf("\n[1]Inserir\n[2]Remover\n[3]Buscar\n[4]Imprimir\n[0]Sair\nOpcao: ");
        scanf("%d",&op);
        switch (op) {
        case 1:
            novoProduto = criarProduto();
            if (novoProduto.preco <= 200) {
                if (busca2(tabela2, novoProduto.codigo) == NULL)
                    inserir(tabela, novoProduto);
                else
                    printf("\nCodigo ja utilizado. Produto nao cadastrado.\n");
            }
            else if(busca(tabela, novoProduto.codigo) == NULL)
                inserir2(tabela2, novoProduto);
            else
                printf("\nCodigo ja utilizado. Produto nao cadastrado.\n");
            break;
        case 2:
            printf("\nCodigo: ");
            scanf("%d", &cod);
            if(remover(tabela, cod) == 0) 
                remover2(tabela2, cod);
            break;
        case 3:
            printf("\nCodigo: ");
            scanf("%d", &cod);
            Produto *produtoBusca = busca(tabela, cod);
            if (produtoBusca == NULL)
                produtoBusca = busca2(tabela2, cod);
            
               
            if (produtoBusca != NULL)
                printf("%s\nR$%.2lf\n",produtoBusca->descricao, produtoBusca->preco);
            else
                printf("Produto nao encontrado\n");
            break;
        case 4:
            imprimir(tabela);
            imprimir2(tabela2);
            break;
        case 0:
            destruirTabela(tabela);
            incializarHash2(tabela2);
            printf("\nSaindo\n");
            break;
        
        default:
            printf("\nOpcao invalida\n");
            break;
        }

    } while (op != 0);
    
    



    return 0;
}