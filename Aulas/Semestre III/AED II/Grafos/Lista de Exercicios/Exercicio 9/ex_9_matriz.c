/************************************************************************************************/
/* Enunciado: Dados dois grafos g1 e g2 (mesmos vértices), retorne um grafo g3 cujas arestas    */
/* estão presentes em g1 mas não em g2. Representação por matriz de adjacência.                 */
/************************************************************************************************/

#include <stdio.h>

#define V 5

/**************************************/
/*       ESTRUTURA DO GRAFO           */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];  // 1 se existe aresta, 0 caso contrário
} GRAFO;

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(GRAFO *g) {
    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            g->matriz[i][j] = 0;
}

void inserirAresta(GRAFO *g, int i, int j) {
    g->matriz[i][j] = 1;
}

void exibirMatriz(GRAFO *g) {
    printf("    ");
    for (int j = 1; j <= V; j++)
        printf("%2d ", j);
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
/*    FUNÇÃO PRINCIPAL DO PROBLEMA    */
/**************************************/

// Diferença de arestas entre g1 e g2: g1 - g2
void diferencaG1eG2(GRAFO *g1, GRAFO *g2, GRAFO *g3) {
    inicializarGrafo(g3);

    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            if ((g1->matriz[i][j] == 1) && (g2->matriz[i][j] == 0)) {
                inserirAresta(g3, i, j);
            }
        }
    }
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO g1, g2, g3;

    inicializarGrafo(&g1);
    inicializarGrafo(&g2);

    // g1: 1→2, 1→3, 2→4, 3→5
    inserirAresta(&g1, 1, 2);
    inserirAresta(&g1, 1, 3);
    inserirAresta(&g1, 2, 4);
    inserirAresta(&g1, 3, 5);

    // g2: 1→3, 2→4
    inserirAresta(&g2, 1, 3);
    inserirAresta(&g2, 2, 4);

    // Calcula g3 = g1 - g2
    diferencaG1eG2(&g1, &g2, &g3);

    // Exibe os grafos
    printf("Grafo G1:\n");
    exibirMatriz(&g1);

    printf("\nGrafo G2:\n");
    exibirMatriz(&g2);

    printf("\nGrafo G3 (arestas em G1 mas não em G2):\n");
    exibirMatriz(&g3);

    return 0;
}
