#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

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
/*     DFS PARA MEDIR MAIOR CICLO     */
/**************************************/

int dfsMaiorCiclo(VERTICE *g, int atual, int pai, int profundidade, int *prof) {
    g[atual].flag = 1;
    prof[atual] = profundidade;

    int maior = 0;

    NO *p = g[atual].inicio;
    while (p) {
        if (g[p->adj].flag == 0) {
            int tam = dfsMaiorCiclo(g, p->adj, atual, profundidade + 1, prof);
            if (tam > maior) maior = tam;
        } else if (p->adj != pai) {
            int tam = abs(prof[atual] - prof[p->adj]) + 1;
            if (tam > maior) maior = tam;
        }
        p = p->prox;
    }

    g[atual].flag = 2;
    return maior;
}

int comprimentoMaiorCiclo(VERTICE *g) {
    int prof[V + 1];
    zerarFlags(g);

    int maior = 0;
    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0) {
            int ciclo = dfsMaiorCiclo(g, i, -1, 0, prof);
            if (ciclo > maior) maior = ciclo;
        }
    }

    return maior;
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    // Exemplo com ciclos
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 2, 3);
    inserirAresta(grafo, 2, 4);
    inserirAresta(grafo, 3, 5); 
    inserirAresta(grafo, 4, 5);
    inserirAresta(grafo, 5, 3);

    exibirGrafo(grafo);

    int maior = comprimentoMaiorCiclo(grafo);
    printf("\nComprimento do maior ciclo: %d\n", maior);  // Esperado: 5

    return 0;
}
