#include <stdio.h>
#include <stdbool.h>

#define V 6  // Número de vértices (a, b, c, d, e, f)

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];
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
    g->matriz[j][i] = 1;
}

void exibirMatriz(GRAFO *g) {
    printf("    ");
    for (int j = 1; j <= V; j++) printf("%2d ", j);
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
/*         GERA O COMPLEMENTO         */
/**************************************/

void grafoComplementar(GRAFO *g, GRAFO *complemento) {
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            if (i == j)
                complemento->matriz[i][j] = 0;  // sem laço
            else
                complemento->matriz[i][j] = (g->matriz[i][j] == 0) ? 1 : 0;
        }
    }
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO g, gc;
    inicializarGrafo(&g);
    inicializarGrafo(&gc);

    // Grafo da imagem do exercício (exemplo com 6 vértices: a-f → 1-6)
    inserirAresta(&g, 1, 2); // a-b
    inserirAresta(&g, 1, 6); // a-f
    inserirAresta(&g, 2, 3); // b-c
    inserirAresta(&g, 2, 6); // b-f
    inserirAresta(&g, 2, 5); // b-e
    inserirAresta(&g, 3, 4); // c-d
    inserirAresta(&g, 3, 5); // c-e
    inserirAresta(&g, 4, 5); // d-e

    printf("🔷 Grafo original:\n");
    exibirMatriz(&g);

    grafoComplementar(&g, &gc);

    printf("\n🔁 Complemento do grafo:\n");
    exibirMatriz(&gc);

    return 0;
}
