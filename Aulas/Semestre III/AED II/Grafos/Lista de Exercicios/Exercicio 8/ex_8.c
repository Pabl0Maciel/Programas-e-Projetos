/************************************************************************************************/
/* Enunciado: Sejam dois grafos g1 e g2 contendo exatamente os mesmos vértices.                 */
/* Verifique se g2 é um subgrafo de g1, retornando true/false conforme o caso.                  */
/* Observação: g1 é representado por listas de adjacência e g2 por matriz de adjacência.        */
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
    int custo;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
} VERTICE;

typedef struct {
    int matriz[V + 1][V + 1];  // matriz[i][j] = 1 se há aresta i → j, 0 caso contrário
} GRAFO;

/**************************************/
/*  FUNÇÃO PRINCIPAL DO PROBLEMA      */
/**************************************/

/*
 * Verifica se o grafo g2 (matriz) é subgrafo de g1 (lista).
 * Retorna true se todas as arestas existentes em g2 também estão em g1.
 */
bool ehSubGrafo(VERTICE *g1, GRAFO *g2) {
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            if (g2->matriz[i][j] != 0) {  // existe aresta i → j em g2
                bool achou = false;
                NO *p = g1[i].inicio;

                while (p) {
                    if (p->adj == j) {
                        achou = true;
                        break;
                    }
                    p = p->prox;
                }

                if (!achou) return false;  // aresta de g2 não existe em g1
            }
        }
    }
    return true;
}

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarLista(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
    }
}

bool inserirArestaLista(VERTICE *g, int i, int j) {
    NO *novo = malloc(sizeof(NO));
    novo->adj = j;
    novo->custo = 0;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;
    return true;
}

void inicializarMatriz(GRAFO *g) {
    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            g->matriz[i][j] = 0;
}

void inserirArestaMatriz(GRAFO *g, int i, int j) {
    g->matriz[i][j] = 1;
}

void exibirLista(VERTICE *g) {
    printf("Grafo em lista (g1):\n");
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

void exibirMatriz(GRAFO *g) {
    printf("Grafo em matriz (g2):\n");
    printf("    ");
    for (int j = 1; j <= V; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 1; i <= V; i++) {
        printf("%2d: ", i);
        for (int j = 1; j <= V; j++) {
            printf("%2d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE g1[V + 1];
    GRAFO g2;

    // Inicializa os grafos
    inicializarLista(g1);
    inicializarMatriz(&g2);

    // Grafo g1 (em lista): 1 → 2, 1 → 3, 2 → 4
    inserirArestaLista(g1, 1, 2);
    inserirArestaLista(g1, 1, 3);
    inserirArestaLista(g1, 2, 4);

    // TESTE 1: g2 é subgrafo de g1
    inserirArestaMatriz(&g2, 1, 2);
    inserirArestaMatriz(&g2, 2, 4);

    printf("=== TESTE 1: g2 É subgrafo de g1 ===\n");
    exibirLista(g1);
    exibirMatriz(&g2);
    printf("Resultado: %s\n", ehSubGrafo(g1, &g2) ? "true" : "false");

    // TESTE 2: g2 NÃO é subgrafo (contém 3 → 4 que não existe em g1)
    inicializarMatriz(&g2);
    inserirArestaMatriz(&g2, 1, 2);
    inserirArestaMatriz(&g2, 3, 4);  // esta aresta não está em g1

    printf("\n=== TESTE 2: g2 NÃO é subgrafo de g1 ===\n");
    exibirLista(g1);
    exibirMatriz(&g2);
    printf("Resultado: %s\n", ehSubGrafo(g1, &g2) ? "true" : "false");

    return 0;
}
