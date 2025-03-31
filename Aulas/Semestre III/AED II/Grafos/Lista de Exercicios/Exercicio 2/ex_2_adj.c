/**********************************************************************/
/* Enunciado: Escreva um algoritmo para remover todos os laços        */
/*            (arestas que ligam um vértice a ele mesmo) de um grafo.*/
/**********************************************************************/

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
/*       FUNÇÃO PRINCIPAL DO PROBLEMA        */
/*********************************************/

/* Remove todas as arestas do tipo (i -> i), ou seja, laços */
void removeLacos(VERTICE *grafo) {
    for (int i = 1; i <= V; i++) {
        NO *ant = NULL;
        NO *p = grafo[i].inicio;

        while (p) {
            if (p->adj == i) {  // Laço encontrado
                NO *excluir = p;
                if (ant == NULL) {
                    grafo[i].inicio = p->prox;
                } else {
                    ant->prox = p->prox;
                }
                p = p->prox;
                free(excluir);
            } else {
                ant = p;
                p = p->prox;
            }
        }
    }
}

/*********************************************/
/*             FUNÇÕES AUXILIARES            */
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

/* Insere uma aresta (i -> j), se ainda não existir */
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

/* Inicializa todos os vértices */
void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
        g[i].via = -1;
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

    /*************** TESTE 1: GRAFO COM 3 LAÇOS ***************/
    inicializarGrafo(grafo);
    inserirAresta(grafo, 1, 1); // laço
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 3, 3); // laço
    inserirAresta(grafo, 4, 5);
    inserirAresta(grafo, 5, 5); // laço

    printf("Teste 1 (com laços):\nAntes:\n");
    exibirGrafo(grafo);
    removeLacos(grafo);
    printf("Depois:\n");
    exibirGrafo(grafo);

    /*************** TESTE 2: GRAFO SEM NENHUM LAÇO ***************/
    inicializarGrafo(grafo);
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 2, 3);
    inserirAresta(grafo, 3, 4);
    inserirAresta(grafo, 4, 5);

    printf("\nTeste 2 (sem laços):\nAntes:\n");
    exibirGrafo(grafo);
    removeLacos(grafo);
    printf("Depois:\n");
    exibirGrafo(grafo);

    /*************** TESTE 3: TODOS OS VÉRTICES COM LAÇO ***************/
    inicializarGrafo(grafo);
    for (int i = 1; i <= V; i++) {
        inserirAresta(grafo, i, i); // todos com laço
    }

    printf("\nTeste 3 (todos com laço):\nAntes:\n");
    exibirGrafo(grafo);
    removeLacos(grafo);
    printf("Depois:\n");
    exibirGrafo(grafo);

    return 0;
}
