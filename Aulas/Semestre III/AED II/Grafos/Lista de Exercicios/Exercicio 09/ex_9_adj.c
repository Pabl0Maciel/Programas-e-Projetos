/************************************************************************************************/
/* Enunciado: Dados dois grafos g1 e g2 (representados por listas de adjacência),               */
/* escreva um algoritmo que retorne um terceiro grafo g3, cujas arestas estão presentes         */
/* em g1 mas não em g2.                                                                          */
/************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*       ESTRUTURAS DE DADOS          */
/**************************************/

typedef struct no {
    int adj;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
} VERTICE;

/**************************************/
/*       PROTÓTIPOS DAS FUNÇÕES       */
/**************************************/
void inicializarGrafo(VERTICE *g);
bool inserirAresta(VERTICE *g, int i, int j);
bool arestaExiste(VERTICE *g, int i, int j);
void exibirGrafo(VERTICE *g);
void diferencaG1eG2(VERTICE *g1, VERTICE *g2, VERTICE *g3);

/**************************************/
/*    FUNÇÃO PRINCIPAL DO PROBLEMA    */
/**************************************/

void diferencaG1eG2(VERTICE *g1, VERTICE *g2, VERTICE *g3) {
    inicializarGrafo(g3);

    for (int i = 1; i <= V; i++) {
        NO *p = g1[i].inicio;
        while (p) {
            if (!arestaExiste(g2, i, p->adj)) {
                inserirAresta(g3, i, p->adj);
            }
            p = p->prox;
        }
    }
}

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
    }
}

bool inserirAresta(VERTICE *g, int i, int j) {
    if (arestaExiste(g, i, j)) return false;

    NO *novo = malloc(sizeof(NO));
    novo->adj = j;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;

    return true;
}

bool arestaExiste(VERTICE *g, int i, int j) {
    NO *p = g[i].inicio;
    while (p) {
        if (p->adj == j) return true;
        p = p->prox;
    }
    return false;
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

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE g1[V + 1], g2[V + 1], g3[V + 1];

    // Inicializa os grafos
    inicializarGrafo(g1);
    inicializarGrafo(g2);

    // g1: 1→2, 1→3, 2→4, 3→5
    inserirAresta(g1, 1, 2);
    inserirAresta(g1, 1, 3);
    inserirAresta(g1, 2, 4);
    inserirAresta(g1, 3, 5);

    // g2: 1→3, 2→4 (subconjunto de g1)
    inserirAresta(g2, 1, 3);
    inserirAresta(g2, 2, 4);

    // Calcula g3 = g1 - g2
    diferencaG1eG2(g1, g2, g3);

    // Exibe resultados
    printf("Grafo G1:\n");
    exibirGrafo(g1);

    printf("\nGrafo G2:\n");
    exibirGrafo(g2);

    printf("\nGrafo G3 (arestas em G1 mas não em G2):\n");
    exibirGrafo(g3);

    return 0;
}
