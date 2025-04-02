#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 7

/**************************************/
/*        ESTRUTURA DO GRAFO          */
/**************************************/

typedef struct no {
    int adj;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
    int flag;
} VERTICE;

/**************************************/
/*        FUNÇÕES AUXILIARES          */
/**************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
    }
}

void zerarFlags(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].flag = 0;
    }
}

void inserirAresta(VERTICE *g, int i, int j) {
    NO *novo1 = malloc(sizeof(NO));
    novo1->adj = j;
    novo1->prox = g[i].inicio;
    g[i].inicio = novo1;

    NO *novo2 = malloc(sizeof(NO));
    novo2->adj = i;
    novo2->prox = g[j].inicio;
    g[j].inicio = novo2;
}

void exibirGrafo(VERTICE *g) {
    printf("Grafo:\n");
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

/**************************************/
/*      DFS CONTANDO O CAMINHO        */
/**************************************/

bool existeCaminho(VERTICE *g, int origem, int destino, int *tamCaminho) {
    g[origem].flag = 1;

    if (origem == destino) {
        (*tamCaminho)++;
        return true;
    }

    NO *p = g[origem].inicio;
    while (p) {
        if (g[p->adj].flag == 0) {
            if (existeCaminho(g, p->adj, destino, tamCaminho)) {
                (*tamCaminho)++;
                return true;
            }
        }
        p = p->prox;
    }

    return false;
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    // Componentes:
    // 1 - 2 - 3 - 4 - 5
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 2, 3);
    inserirAresta(grafo, 3, 4);
    inserirAresta(grafo, 4, 5);

    // Vértices 6 e 7 isolados

    exibirGrafo(grafo);

    // Teste 1: caminho entre 1 e 5
    int tam = 0;
    zerarFlags(grafo);
    if (existeCaminho(grafo, 1, 5, &tam)) {
        printf("\nExiste caminho entre 1 e 5 com %d vértices.\n", tam);
    } else {
        printf("\nNão existe caminho entre 1 e 5.\n");
    }

    // Teste 2: caminho entre 1 e 6
    tam = 0;
    zerarFlags(grafo);
    if (existeCaminho(grafo, 1, 6, &tam)) {
        printf("Existe caminho entre 1 e 6 com %d vértices.\n", tam);
    } else {
        printf("Não existe caminho entre 1 e 6.\n");
    }

    return 0;
}

