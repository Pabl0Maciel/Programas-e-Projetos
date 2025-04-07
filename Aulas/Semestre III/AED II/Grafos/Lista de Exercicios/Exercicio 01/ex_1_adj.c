/*********************************************************************/
/* Enunciado: Escreva um algoritmo para contar a quantidade de laços */
/*            em um grafo representado por lista de adjacência.      */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*       ESTRUTURAS DE DADOS          */
/**************************************/

typedef struct s {
    struct s *prox;
    int adj;
} NO;

typedef struct {
    NO *inicio;
    int flag;
    int via;
} VERTICE;

/*********************************************/
/*        FUNÇÃO PRINCIPAL DO PROBLEMA       */
/*********************************************/

/* Conta e imprime a quantidade de laços (i -> i) em um grafo */
void contarLacos(VERTICE *g) {
    int num_lacos = 0;
    for (int i = 1; i <= V; i++) {
        NO *p = g[i].inicio;
        while (p) {
            if (p->adj == i) {
                num_lacos++;
            }
            p = p->prox;
        }
    }
    printf("Quantidade de laços: %d\n", num_lacos);
}

/*********************************************/
/*           FUNÇÕES AUXILIARES              */
/*********************************************/

/* Verifica se a aresta (i -> j) existe */
NO *arestaExiste(VERTICE *g, int i, int j, NO **ant) {
    *ant = NULL;
    NO *p = g[i].inicio;

    while (p) {
        if (p->adj == j) return p;
        *ant = p;
        p = p->prox;
    }
    return NULL;
}

/* Insere uma aresta (i -> j) se ainda não existir */
bool inserirAresta(VERTICE *g, int i, int j) {
    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);
    if (atual) return false; // já existe

    NO *novo = (NO *)malloc(sizeof(NO));
    novo->adj = j;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;
    return true;
}

/* Remove a aresta (i -> j), se existir */
bool excluirAresta(VERTICE *g, int i, int j) {
    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);
    if (!atual) return false; // não existe

    if (ant) ant->prox = atual->prox;
    else g[i].inicio = atual->prox;

    free(atual);
    return true;
}

/* Inicializa todos os vértices do grafo */
void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
        g[i].via = -1;
    }
}

/* Reseta apenas os flags dos vértices */
void zerarFlags(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].flag = 0;
    }
}

/* Exibe o grafo em formato de listas de adjacência */
void exibirGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        printf("%d: ", i);
        NO *p = g[i].inicio;
        while (p) {
            printf("%d -> ", p->adj);
            p = p->prox;
        }
        printf("NULL\n");
    }
}

/*********************************************/
/*                  MAIN                     */
/*********************************************/

int main() {
    VERTICE grafo[V + 1];

    /*************** TESTE 1: SEM LAÇOS ***************/
    inicializarGrafo(grafo);
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 2, 3);
    inserirAresta(grafo, 3, 4);
    inserirAresta(grafo, 4, 5);
    printf("Teste 1 (sem laços):\n");
    exibirGrafo(grafo);
    contarLacos(grafo);

    /*************** TESTE 2: COM 2 LAÇOS ***************/
    inicializarGrafo(grafo);
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 2, 2); // laço
    inserirAresta(grafo, 3, 4);
    inserirAresta(grafo, 4, 4); // laço
    printf("\nTeste 2 (com 2 laços):\n");
    exibirGrafo(grafo);
    contarLacos(grafo);

    /*************** TESTE 3: TODOS COM LAÇO ***************/
    inicializarGrafo(grafo);
    for (int i = 1; i <= V; i++) {
        inserirAresta(grafo, i, i);
    }
    printf("\nTeste 3 (todos com laço):\n");
    exibirGrafo(grafo);
    contarLacos(grafo);

    return 0;
}
