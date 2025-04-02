#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 4  // número de vértices

/**************************************/
/*         ESTRUTURA DO GRAFO         */
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
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
    }
}

void inserirAresta(VERTICE *g, int i, int j) {
    // Insere j em i
    NO *novo1 = malloc(sizeof(NO));
    novo1->adj = j;
    novo1->prox = g[i].inicio;
    g[i].inicio = novo1;

    // Insere i em j (grafo não-dirigido)
    NO *novo2 = malloc(sizeof(NO));
    novo2->adj = i;
    novo2->prox = g[j].inicio;
    g[j].inicio = novo2;
}

bool arestaExiste(VERTICE *g, int i, int j) {
    NO *p = g[i].inicio;
    while (p) {
        if (p->adj == j) return true;
        p = p->prox;
    }
    return false;
}

bool ehCompleto(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        for (int j = i + 1; j <= V; j++) {
            if (!arestaExiste(g, i, j) || !arestaExiste(g, j, i)) {
                return false;
            }
        }
    }
    return true;
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
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];

    printf("==== Teste 1: Grafo completo ====\n");
    inicializarGrafo(grafo);
    // Cria K4: todas as conexões entre 4 vértices
    for (int i = 1; i <= V; i++) {
        for (int j = i + 1; j <= V; j++) {
            inserirAresta(grafo, i, j);
        }
    }
    exibirGrafo(grafo);
    printf("É completo? %s\n\n", ehCompleto(grafo) ? "Sim ✅" : "Não ❌");

    printf("==== Teste 2: Grafo incompleto ====\n");
    inicializarGrafo(grafo);
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 2, 3);
    inserirAresta(grafo, 3, 4);  // faltam várias conexões
    exibirGrafo(grafo);
    printf("É completo? %s\n", ehCompleto(grafo) ? "Sim ✅" : "Não ❌");

    return 0;
}
