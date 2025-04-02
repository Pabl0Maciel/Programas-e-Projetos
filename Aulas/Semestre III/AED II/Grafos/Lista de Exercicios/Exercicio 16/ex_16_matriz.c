#include <stdio.h>
#include <stdlib.h>

#define V 7

/**************************************/
/*        ESTRUTURA DO GRAFO          */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];
    int flag[V + 1];
} GRAFO;

typedef struct lista {
    int vertice;
    struct lista *prox;
} LISTA;

/**************************************/
/*        FUNÇÕES AUXILIARES          */
/**************************************/

void inicializarGrafo(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

void zerarFlags(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
    }
}

void inserirAresta(GRAFO *g, int i, int j) {
    g->matriz[i][j] = 1;
    g->matriz[j][i] = 1;
}

void exibirMatriz(GRAFO *g) {
    printf("Matriz de adjacência:\n    ");
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

void exibirLista(LISTA *l) {
    printf("Maior grupo: ");
    while (l) {
        printf("%d ", l->vertice);
        l = l->prox;
    }
    printf("\n");
}

void liberarLista(LISTA *l) {
    while (l) {
        LISTA *tmp = l;
        l = l->prox;
        free(tmp);
    }
}

/**************************************/
/*      DFS COLETANDO COMPONENTE      */
/**************************************/

int dfsColeta(GRAFO *g, int i, LISTA **grupo) {
    g->flag[i] = 1;

    LISTA *novo = malloc(sizeof(LISTA));
    novo->vertice = i;
    novo->prox = *grupo;
    *grupo = novo;

    int tam = 1;
    for (int j = 1; j <= V; j++) {
        if (g->matriz[i][j] && g->flag[j] == 0) {
            tam += dfsColeta(g, j, grupo);
        }
    }

    return tam;
}

/**************************************/
/*      MAIOR GRUPO DE VÉRTICES       */
/**************************************/

LISTA *maiorGrupo(GRAFO *g) {
    zerarFlags(g);
    LISTA *maior = NULL;
    int maiorTam = 0;

    for (int i = 1; i <= V; i++) {
        if (g->flag[i] == 0) {
            LISTA *grupoAtual = NULL;
            int tam = dfsColeta(g, i, &grupoAtual);

            if (tam > maiorTam) {
                liberarLista(maior);
                maior = grupoAtual;
                maiorTam = tam;
            } else {
                liberarLista(grupoAtual);
            }
        }
    }

    return maior;
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO grafo;
    inicializarGrafo(&grafo);

    // Grupo 1: 1-2-3-4
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);
    inserirAresta(&grafo, 3, 4);

    // Grupo 2: 5-6
    inserirAresta(&grafo, 5, 6);

    printf("==== Exercício 16 ====\n");
    exibirMatriz(&grafo);

    LISTA *maior = maiorGrupo(&grafo);
    printf("\n");
    exibirLista(maior);
    liberarLista(maior);

    return 0;
}

