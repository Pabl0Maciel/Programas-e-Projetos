/**********************************************************************/
/* Enunciado: Escreva um algoritmo para retornar o grafo transposto  */
/*            de um grafo dirigido. Representação: lista de adjacência. */
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
/*       PROTÓTIPOS DAS FUNÇÕES AUXILIARES   */
/*********************************************/

bool inserirAresta(VERTICE *g, int i, int j);
void inicializarGrafo(VERTICE *g);
void exibirGrafo(VERTICE *g);
NO *arestaExiste(VERTICE *g, int i, int j, NO **ant);

/*********************************************/
/*       FUNÇÃO PRINCIPAL DO PROBLEMA        */
/*********************************************/

/* Gera o grafo transposto de g em gT */
void grafoTransposto(VERTICE *g, VERTICE *gT) {
    // Inicializa o grafo transposto
    for (int i = 1; i <= V; i++) {
        gT[i].inicio = NULL;
        gT[i].flag = 0;
        gT[i].via = -1;
    }

    // Percorre todas as arestas de g
    for (int i = 1; i <= V; i++) {
        NO *p = g[i].inicio;
        while (p) {
            // Inverte a direção: se tem (i → j), insere (j → i) em gT
            inserirAresta(gT, p->adj, i);
            p = p->prox;
        }
    }
}


/*********************************************/
/*             FUNÇÕES AUXILIARES            */
/*********************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
        g[i].via = -1;
    }
}

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

bool inserirAresta(VERTICE *g, int i, int j) {
    NO *ant;
    if (arestaExiste(g, i, j, &ant)) return false;

    NO *novo = (NO *)malloc(sizeof(NO));
    novo->adj = j;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;
    return true;
}

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
    VERTICE grafo[V + 1], transposto[V + 1];

    inicializarGrafo(grafo);

    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 2, 4);
    inserirAresta(grafo, 3, 4);
    inserirAresta(grafo, 4, 5);

    printf("Grafo original:\n");
    exibirGrafo(grafo);

    grafoTransposto(grafo, transposto);

    printf("\nGrafo transposto:\n");
    exibirGrafo(transposto);

    return 0;
}
