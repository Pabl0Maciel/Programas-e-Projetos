/**********************************************************************/
/* Enunciado: Escreva um algoritmo para destruir todas as arestas de */
/*            um grafo, deixando-o vazio (sem liberar os vértices).  */
/*            Representação: lista de adjacência.                     */
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

/* Remove todas as arestas do grafo, liberando a memória */
void excluirTodasArestas(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        NO *p = g[i].inicio;
        while (p) {
            NO *temp = p;
            p = p->prox;
            free(temp);
        }
        g[i].inicio = NULL;
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
    if (atual) return false;

    NO *novo = (NO *)malloc(sizeof(NO));
    novo->adj = j;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;
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

    /*************** TESTE 1: GRAFO COM VÁRIAS ARESTAS ***************/
    inicializarGrafo(grafo);
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 2, 3);
    inserirAresta(grafo, 3, 4);
    inserirAresta(grafo, 4, 1);
    inserirAresta(grafo, 5, 5); // laço

    printf("Teste 1 (grafo com arestas):\nAntes:\n");
    exibirGrafo(grafo);
    excluirTodasArestas(grafo);
    printf("Depois:\n");
    exibirGrafo(grafo);

    /*************** TESTE 2: GRAFO JÁ VAZIO ***************/
    inicializarGrafo(grafo); // já garante que não há arestas

    printf("\nTeste 2 (grafo vazio):\nAntes:\n");
    exibirGrafo(grafo);
    excluirTodasArestas(grafo);
    printf("Depois:\n");
    exibirGrafo(grafo);

    return 0;
}
