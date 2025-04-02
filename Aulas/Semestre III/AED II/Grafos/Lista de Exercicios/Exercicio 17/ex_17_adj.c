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
/*     DFS PARA VERIFICAR CAMINHO     */
/**************************************/

bool existeCaminho(VERTICE *g, int origem, int destino) {
    g[origem].flag = 1;

    if (origem == destino) {
        return true;
    }

    NO *p = g[origem].inicio;
    while (p) {
        if (g[p->adj].flag == 0) {
            if (existeCaminho(g, p->adj, destino)) {
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

    // Conectando 1-2-3 e 4-5. Vértices 6 e 7 isolados.
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 2, 3);
    inserirAresta(grafo, 4, 5);

    exibirGrafo(grafo);

    // Teste 1: há caminho de 1 a 3
    zerarFlags(grafo);
    printf("\nExiste caminho entre 1 e 3? %s\n",
        existeCaminho(grafo, 1, 3) ? "Sim" : "Não");

    // Teste 2: não há caminho entre 1 e 5
    zerarFlags(grafo);
    printf("Existe caminho entre 1 e 5? %s\n",
        existeCaminho(grafo, 1, 5) ? "Sim" : "Não");

    // Teste 3: não há caminho entre 1 e 6 (6 é isolado)
    zerarFlags(grafo);
    printf("Existe caminho entre 1 e 6? %s\n",
        existeCaminho(grafo, 1, 6) ? "Sim" : "Não");

    return 0;
}
