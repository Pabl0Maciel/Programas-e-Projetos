/**********************************************************************/
/* Enunciado: Escreva um algoritmo para destruir todas as arestas de */
/*            um grafo, deixando-o vazio (sem liberar os vértices).  */
/*            Representação: matriz de adjacência.                    */
/**********************************************************************/

#include <stdio.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*       ESTRUTURA DO GRAFO           */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1]; // índices de 1 até V
} GRAFO;

/*********************************************/
/*       FUNÇÃO PRINCIPAL DO PROBLEMA        */
/*********************************************/

/* Zera todas as posições da matriz de adjacência (remove todas as arestas) */
// OBS: Nesse caso, bastaria chamar a funcao de inicializar
void excluiTodasArestas(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

/*********************************************/
/*             FUNÇÕES AUXILIARES            */
/*********************************************/

/* Inicializa a matriz com zeros */
void inicializar(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

/* Insere uma aresta (i -> j), se ainda não existir */
bool inserirAresta(GRAFO *g, int i, int j) {
    if (g->matriz[i][j] == 1) return false;
    g->matriz[i][j] = 1;
    return true;
}

/* Exibe o grafo no formato de matriz */
void exibirGrafo(GRAFO *g) {
    printf("   ");
    for (int j = 1; j <= V; j++) {
        printf("%d ", j);
    }
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
    GRAFO grafo;

    /*************** TESTE 1: GRAFO COM VÁRIAS ARESTAS ***************/
    inicializar(&grafo);
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);
    inserirAresta(&grafo, 3, 4);
    inserirAresta(&grafo, 4, 1);
    inserirAresta(&grafo, 5, 5); // laço

    printf("Teste 1 (grafo com arestas):\nAntes:\n");
    exibirGrafo(&grafo);
    excluiTodasArestas(&grafo);
    printf("Depois:\n");
    exibirGrafo(&grafo);

    /*************** TESTE 2: GRAFO JÁ VAZIO ***************/
    inicializar(&grafo); // já garante que não há arestas

    printf("\nTeste 2 (grafo vazio):\nAntes:\n");
    exibirGrafo(&grafo);
    excluiTodasArestas(&grafo);
    printf("Depois:\n");
    exibirGrafo(&grafo);

    return 0;
}
