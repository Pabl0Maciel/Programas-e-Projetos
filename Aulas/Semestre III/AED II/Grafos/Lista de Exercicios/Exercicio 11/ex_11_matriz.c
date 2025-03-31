/************************************************************************************************/
/* Enunciado: Considere um grafo dirigido representando chamadas entre unidades de uma empresa.*/
/* Cada vértice representa uma unidade, e cada aresta uma chamada efetuada.                    */
/* A matriz g->pais[i][j] armazena o país da unidade j (destino) se houver chamada de i para j.*/
/* Identifique a unidade que efetuou chamadas para o maior número de países distintos.         */
/************************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define V 5

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int pais[V + 1][V + 1];  // país[i][j] = país da unidade j, se i fez chamada para j
} GRAFO;

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(GRAFO *g) {
    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            g->pais[i][j] = 0;
}

void inserirChamada(GRAFO *g, int origem, int destino, int paisDestino) {
    g->pais[origem][destino] = paisDestino;
}

void exibirMatriz(GRAFO *g) {
    printf("Matriz de chamadas (país de destino):\n");
    printf("    ");
    for (int j = 1; j <= V; j++)
        printf("%3d", j);
    printf("\n");

    for (int i = 1; i <= V; i++) {
        printf("%3d:", i);
        for (int j = 1; j <= V; j++) {
            printf("%3d", g->pais[i][j]);
        }
        printf("\n");
    }
}

bool paisJaContado(int *vet, int tam, int valor) {
    for (int i = 0; i < tam; i++) {
        if (vet[i] == valor) return true;
    }
    return false;
}

/**************************************/
/*    FUNÇÃO PRINCIPAL DO PROBLEMA    */
/**************************************/

void unidadeMaisChamadas(GRAFO *g) {
    int maxPaises = -1;
    int unidadeResp = -1;

    for (int i = 1; i <= V; i++) {
        int paises[V + 1];
        int count = 0;

        for (int j = 1; j <= V; j++) {
            if (g->pais[i][j] != 0 && !paisJaContado(paises, count, g->pais[i][j])) {
                paises[count++] = g->pais[i][j];
            }
        }

        if (count > maxPaises) {
            maxPaises = count;
            unidadeResp = i;
        }
    }

    printf("Unidade que ligou para o maior número de países: %d, com %d países\n",
           unidadeResp, maxPaises);
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO grafo;
    inicializarGrafo(&grafo);

    // Exemplo: unidades em diferentes países
    // Chamada: origem → destino (país do destino)

    inserirChamada(&grafo, 1, 2, 1);   // 1 → 2 (EUA)
    inserirChamada(&grafo, 1, 3, 44);  // 1 → 3 (UK)
    inserirChamada(&grafo, 1, 4, 55);  // 1 → 4 (Brasil)
    inserirChamada(&grafo, 2, 3, 44);  // 2 → 3 (UK)
    inserirChamada(&grafo, 3, 5, 49);  // 3 → 5 (Alemanha)
    inserirChamada(&grafo, 4, 5, 49);  // 4 → 5 (Alemanha)

    exibirMatriz(&grafo);
    unidadeMaisChamadas(&grafo);

    return 0;
}
