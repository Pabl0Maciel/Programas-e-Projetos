/************************************************************************************************/
/* Enunciado: Considere um grafo dirigido representando chamadas entre unidades de uma empresa.*/
/* Cada vértice representa uma unidade, e cada aresta uma chamada efetuada.                    */
/* Cada unidade está em um país (campo `pais` no vértice).                                     */
/* Identifique a unidade que efetuou chamadas para o MAIOR NÚMERO DE PAÍSES DISTINTOS.         */
/************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct no {
    int adj;           // destino da chamada
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
    int pais;          // país da unidade
} VERTICE;

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].pais = -1;
    }
}

void inserirAresta(VERTICE *g, int origem, int destino) {
    NO *novo = malloc(sizeof(NO));
    novo->adj = destino;
    novo->prox = g[origem].inicio;
    g[origem].inicio = novo;
}

void exibirGrafo(VERTICE *g) {
    printf("Grafo de chamadas (por unidade):\n");
    for (int i = 1; i <= V; i++) {
        printf("Unidade %d (país %d): ", i, g[i].pais);
        NO *p = g[i].inicio;
        while (p) {
            printf("-> %d(pais %d) ", p->adj, g[p->adj].pais);
            p = p->prox;
        }
        printf("NULL\n");
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

void unidadeMaisChamadas(VERTICE *g) {
    int maxPaises = -1;
    int unidadeResp = -1;

    for (int i = 1; i <= V; i++) {
        int paises[V + 1]; // vetor auxiliar para países diferentes
        int count = 0;

        NO *p = g[i].inicio;
        while (p) {
            int paisDestino = g[p->adj].pais;

            if (!paisJaContado(paises, count, paisDestino)) {
                paises[count++] = paisDestino;
            }
            p = p->prox;
        }

        if (count > maxPaises) {
            maxPaises = count;
            unidadeResp = i;
        }
    }

    printf("\nUnidade que ligou para o maior número de países: %d\n", unidadeResp);
    printf("Quantidade de países distintos: %d\n", maxPaises);
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];

    inicializarGrafo(grafo);

    // Definição dos países por unidade
    grafo[1].pais = 55;  // Brasil
    grafo[2].pais = 1;   // EUA
    grafo[3].pais = 44;  // Reino Unido
    grafo[4].pais = 55;  // Brasil
    grafo[5].pais = 49;  // Alemanha

    // Inserção de chamadas (arestas dirigidas)
    inserirAresta(grafo, 1, 2); // Brasil → EUA
    inserirAresta(grafo, 1, 3); // Brasil → UK
    inserirAresta(grafo, 1, 4); // Brasil → Brasil
    inserirAresta(grafo, 2, 3); // EUA → UK
    inserirAresta(grafo, 3, 5); // UK → Alemanha
    inserirAresta(grafo, 3, 4); // UK → Brasil
    inserirAresta(grafo, 5, 1); // Alemanha → Brasil

    exibirGrafo(grafo);
    unidadeMaisChamadas(grafo);

    return 0;
}
