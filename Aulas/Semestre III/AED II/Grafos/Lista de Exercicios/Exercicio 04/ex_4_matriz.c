/**********************************************************************/
/* Enunciado: Escreva um algoritmo para retornar o grafo transposto  */
/*            de um grafo dirigido. Representação: matriz de adjacência. */
/**********************************************************************/

#include <stdio.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*       ESTRUTURA DO GRAFO           */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];
} GRAFO;

/*********************************************/
/*       FUNÇÃO PRINCIPAL DO PROBLEMA        */
/*********************************************/

/* Transpõe o grafo g e salva o resultado em gT */
void grafoTransposto(GRAFO *g, GRAFO *gT) {
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            gT->matriz[i][j] = g->matriz[j][i];
        }
    }
}

/*********************************************/
/*             FUNÇÕES AUXILIARES            */
/*********************************************/

void inicializar(GRAFO *g) {
    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            g->matriz[i][j] = 0;
}

bool inserirAresta(GRAFO *g, int i, int j) {
    if (g->matriz[i][j]) return false;
    g->matriz[i][j] = 1;
    return true;
}

void exibirGrafo(GRAFO *g) {
    printf("   ");
    for (int j = 1; j <= V; j++) printf("%d ", j);
    printf("\n");

    for (int i = 1; i <= V; i++) {
        printf("%d: ", i);
        for (int j = 1; j <= V; j++) {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

/*********************************************/
/*                  MAIN                     */
/*********************************************/

int main() {
    GRAFO grafo, transposto;

    inicializar(&grafo);

    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 1, 3);
    inserirAresta(&grafo, 2, 4);
    inserirAresta(&grafo, 3, 4);
    inserirAresta(&grafo, 4, 5);

    printf("Grafo original:\n");
    exibirGrafo(&grafo);

    grafoTransposto(&grafo, &transposto);

    printf("\nGrafo transposto:\n");
    exibirGrafo(&transposto);

    return 0;
}
